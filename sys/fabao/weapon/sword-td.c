// by firefox 11/21/2009

/*
法宝——导弹剑

精确制导武器，出处如下：

1.苦竹真君传吕岩日月交拜之法，火龙真人传天遁剑法。
2.吕岩诗，传闻吕洞宾飞剑取人头，应该来自此诗。看全唐诗，这小子太多产了。

《赠剑客》

先生先生貌獰惡，拔劍當空氣雲錯。
連喝三回急急去，欻然空裏人頭落。

亦或此《绝句》：

劍起星奔萬里誅，風雷時逐雨聲粗。
人頭攜處非人在，何事高吟過五湖。

又有：《潭州鶴會》

這回相見不無緣，滿院風光小洞天。
一劍當空又飛去，洞庭驚起老龍眠。 

看这气魄：《絕句》

天下都遊半日功，不須跨鳳與乘龍。
偶因博戲飛神劍，摧卻終南第一峰。 

東山東畔忽相逢，握手丁甯語似鐘。
劍術已成君把去，有蛟龍處斬蛟龍。

宝剑需同人方可赠与：

朝泛蒼梧暮卻還，洞中日月我為天。
匣中寶劍時時吼，不遇同人誓不傳。

不吹剑了，改吹岁数了：《題鳳翔府天慶觀》

得道年來八百秋，不曾飛劍取人頭。
玉皇未有天符至，且貨烏金混世流。


磨剑吹牛两不误：《化江南簡寂觀道士侯用晦磨劍》

欲整鋒鋩敢憚勞，淩晨開匣玉龍嗥。手中氣概冰三尺，
石上精神蛇一條。奸血默隨流水盡，凶豪今逐漬痕消。
削平浮世不平事，與爾相將上九霄。 

《題全州道士蔣暉壁》，这个金丹什么作用？

醉舞高歌海上山，天瓢承露結金丹。
夜深鶴透秋空碧，萬里西風一劍寒。 

我以前只会背这首：《警世》

二八佳人體似酥，腰間仗劍斬凡夫。
雖然不見人頭落，暗裏教君骨髓枯。 


色名满天下，豪情万丈，牛皮冲天！
谁是MUD西游记中最可爱的人？当然是呂岩！
尽管他和唐僧差二百年，延续XYJ2000的文盲传统，就当不知道。

全唐诗：http://www.xysa.com/quantangshi/t-858.htm
*/

#include <weapon.h>
#include "_base.h"

inherit SWORD;

void create()
{
	set_name("导弹剑", ({"sword"}));
	set_weight(400);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("material", "steel");
		set("wield_msg", "$一声低吼如虎啸龙吟，$N手中多了一把$n。\n");
	}

	init_sword(1);
	setup();
}

#define CD_ID				"dance"

void init_var()
{
	_subs = ([
		"天遁剑"		: ([
			"ids"			: ({"tiandun jian", "jian", "sword"}),
			"long"			: "一柄寒光闪闪的宝剑。",
			"color"			: HIW,
			"unit"			: "柄",
		]),
		"玉龙嗥"		: ([
			"ids"			: ({"yulong hao", "hao", "sword"}),
			"long"			: "隐隐听见一声声低沉的嗥叫。",
			"color"			: HIW,
			"unit"			: "柄",
		]),
	]);

	
	//特征，法术/内功，
	_trais = ([

		//按百分比加成的属性
		"prop_x"	: ([
			"spells"		: 10,
		]),

		"prop_x"	: ([
			"damage"		: 40,		//1M 5点？
		]),
	]);

	_act = ([
		"exp_x"			: 50,					//50%的经验分配给法宝

		"cd_id"			: CD_ID,				//共CD的ID，多种法宝可能共CD
		"cd"			: 30,

		"target"		: ([ "need_enemy" : 1, "need_living" : 1, "can_fight" : 1]),

		"req"			: ([
			"cd"			: ([ CD_ID			: 1 ]),
			"skill1"		: ([ "spells"		: 100]),
			"prop"			: ([ "mana"			: 100,	"sen"	: 20 ]),
		]),
		"cmp"			: ([
			"prop"			: ([ "sen" : 1, "max_sen" : -1, "mana_factor" : 1, DEXP : 1 ]),
			"temp"			: ([ "no_cast" : -2 ]),
			"skill"			: ([ "spells" : 2]),
		]),
		"threshold"		: 60,
		"msg_start"		: "$N连喝三声『去！去！去』，随着一声龙嗥%s腾空而去。",
		"msg_success"	: HIW"一道白虹从天而降，直直射向$N，还未及抵挡便被钉在地上。",
		"msg_fail"		: HIW"一道白虹从天而降，直直射向$N，结果被法力荡开，没如土中。",
		"msg_back1"		: "$N自行拔出，称风而去。\n",
		"msg_back2"		: HIW"一道白虹从天而降，陡然收于$N的剑鞘中。",
		"msg_head"		: "『扑通』一声，一个重物掉落$N脚边，滚来滚去。",
	]);
}


//法宝目标 敌人，双方，环境
int ji(string tid)
{
	int fabao_exp = _act["exp_x"] * _exp / 100;
	object who = _player;
	object target = tid ? present(tid, environment(who)) : 0;

	if(target) return notify_fail("目标近在眼前，上去砍吧。\n");

	target = find_player(tid);
	if(!target) find_living(tid);

	if(!target) return notify_fail("必须指定一个目标。\n");

	if(!BTL->require(who, NAME, _act["req"])) return 1;
	if(!cd_start(me, ID, CD)) return notify_fail("你暂时还不能使用"NAME"。\n");

	BTL->pay(me, _act["req"]["prop"]);


	MSG->vision(_act["msg_start"] + NOR"\n", who, target, _this->name());

	{
		object env = environment(target);
		mapping cmp = ([ ({fabao_exp, target->query(DEXP)/FABAO_EXP_X }) : 5 ]);
		cmp += _act["cmp"];

		if(BTL->random_cmp(who, target, cmp_parm) >= _act["threshold"]) {
			int damage = 1000;
			MSG->vision(_act["msg_success"] + NOR"\n", target, 0, _this->name());
			//伤害，下kill
			if(query("equipped")) unwield();
			_this->move(env);
		
			target->receive_damage("kee", damage, me);
			target->receive_wound("kee", damage, me);
			
			call_out("cut_head", 3, target->query("name"), env, who);
		} else {
			MSG->vision(_act["msg_fail"] + NOR"\n", target, 0, _this->name());
		}
	}
	return 1;
}

//等几秒，如果死了就『喀嚓』
void cut_head(string name, object env, object killer)
{
	object corpse = present_name(name + "的尸体", env);

	if(!killer) return;
	msv(_act["msg_back1"] + NOR"\n", _this);
	msv(_act["msg_back2"] + NOR"\n", killer);
	_this->move(killer);

	if(corpse) {
		object head = new ("/d/qujing/jilei/obj/head");
		head->set_name(name + "的头", ({"tou"}));
		head->set("long", "一只头颅，血迹未干。\n");
		if(head->move(environment(killer)))
			msv(_act["msg_head"] + NOR"\n", killer);

		corpse->set("name", "无头尸体");
	}
}
