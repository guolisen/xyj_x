
#include <xyj_x.h>
#include <ansi.h>

inherit F_CLEAN_UP;

#define PROP						"sitting"
#define DURATION					120			//单次时间
#define DX_GAIN						1100		//200 buddhism，1.0年/小时，24年/天
#define	NORM_RATIO					100

int main(object me, string arg)
{
	object env = environment(me);
	int level = me->query_skill("buddhism") * 2;
	int dx_gain = DURATION * DX_GAIN * level / 3600 / 200;

	if(!env->query("jingzuo_room"))
		return notify_fail("此处不宜静坐修练！\n");

	if(level < 20 ) 
		return notify_fail("你的大乘佛法修为太低，不能行功修炼！\n");

	if(me->is_busy() || me->query_temp(PROP) || me->is_fighting())
		return notify_fail("你现在正忙着呢。\n");

	if(me->query("sen") < 100 ||  me->query("kee") < 100)
		return notify_fail("你现在状态不佳，再炼恐怕要走火入魔！\n");

	if(me->query("water") < 10 )
		return notify_fail("你现在口干舌燥，还是歇歇吧。\n");

	if( me->query("mana") < 50 )
		return notify_fail("你现在法力太低，再炼恐怕要走火入魔！\n");

	message_vision(HIY "$N席地而坐，双目微闭，口中轻声诵起了经文。\n" NOR, me);

	me->start_busy(DURATION / 2 + 1);
	me->set_temp(PROP, 1);
	call_out("finish", DURATION, me, dx_gain);
	return 1;
}

string* msg = ({
	"多欲为苦，生死疲劳，从贪欲起；少欲无为，身心自在。",
	"懈怠坠落，常行精进，破烦恼恶，摧伏四魔，出阴界狱。",
	"愚痴生死，菩萨常念，广学多闻，增长智慧，成就辩才，教化一切，悉以大乐。",
	"贫苦多怨，横结恶缘，菩萨布施，等念怨亲，不念旧恶，不憎恶人。",
	"生死炽燃，苦恼无量，发大乘心，普济一切。",
	"愿代众生，受无量苦，令诸众生，毕竟大乐。",
	"愿以此功德，庄严佛净土，上报四重恩，下济三途苦。",
	"若有见闻者，悉发菩提心，常行菩萨道，广度诸有情。",
});

void finish(object me, int dx)
{
	int ratio = 100;
	mapping gains;
	
	if(!me) return;
	me->delete_temp(PROP);

	if(me->query("family/family_name") != "南海普陀山") ratio -= 30;
	if(me->query("class") != "bonze") ratio -= 30;
	if(me->query("betray/count")) ratio -= 30;

	dx = dx * ratio / 100;
	gains = ([ DEXP : dx, PEXP : dx / 4 ]);

	message_vision(HIY"$N轻声念道：" + msg[random(sizeof(msg))] + "\n"NOR, me);
	message_vision(HIY"$N缓缓睁开眼睛，长舒一口气站了起来。\n"NOR, me);

	//检查配额
	if(TASK_EXC->do_reward(me, "自己", "诵经", gains, NORM_RATIO)) {
		int point = dx / 2 * 20;
		me->add("daoxing", dx);
		me->add("potential", dx / 2);
		me->add("learned_points", dx / 2);
		me->improve_skill("buddhism", point, 1);
		
		tell_object(me, HIC"你的道行增加了" + chinese_number(dx*3) + "时辰！\n"NOR);
		//tell_object(me, HIC"你的潜能增加了" + chinese_number(dx/4) + "点！\n"NOR);		
		tell_object(me, HIC"你的大乘佛法增加了" + chinese_number(point)+ "点！\n"NOR);

		me->add("mana", -20);
		me->add("water", -20);
		me->receive_damage("sen", 20);
		me->receive_damage("kee", 20);
	}
}

int help(object me)
{
	write(@HELP
指令格式 : chanting

诵经修炼以提高道行。
HELP
	   );
	return 1;
}


int test()
{
	main(this_player(), 0);
}

