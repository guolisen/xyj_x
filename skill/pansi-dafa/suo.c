// by firefox 11/21/2009

inherit F_CLEAN_UP;

#include <ansi.h>
#include <xyj_x.h>

#define ID				"suoshen"
#define NAME			HIB"����"NOR
#define DURATION		7
#define CD				15

#define MSG0			"$N����һ˲��������С��ͬһֻ�ɳ棬����$n���У�\n"
#define MSG1			HIC"$n����֮������һ������ȴ��Ҳ�Ҳ���$N��\n"NOR
#define MSG2			HIC"$n��æ��Ϣ�տڣ�$N����϶�ɳ�ֻ�ûָ����Ρ�\n"NOR

/*
������/����

��ئ������󷨡�(����ţħ�����ǣ���ţħ������)��Ƭ�ㆬ���࣬����㵲��ͬ���
������ѽ��
ţħ����ԭ����ǡ�(�������Լ�����)���ţ�������ٲ�(yai)������ѽ��

���𱦣���֪����ʵ�����������л��ɣ�����ҿ��Ԕ{���ĳ�������������֪�҃ӽ���
�׾����������׆���(���������������������ڡ�)

�����Ǹ����ܾ��˵Ĵ򷨣�����Ҫ��ʨ�ӵ���ͳһ���ǣ�
��Ҫ�ȽϷ���/�����������ʳ��б���(��damage)����ռһ�����ơ�

*/

//����
int swallow(object eater, object food, int duration, int thr);

int cast(object me, object target)
{
	int thr = 100;
	int mana = 100;
	mapping req = ([
		"skill1"	: ([ "pansi-dafa"	: 80 ]),
		"prop"		: ([ "mana"			: mana ]),
	]);
	mapping cmp_parm = ([
		"prop"		: ([ DEXP : 1, "sen" : 1, "max_sen" : -1 ]),
		"skill"		: ([ "spells" : 3]),
		"temp"		: ([ "no_cast" : -1, "no_move" : -1]),
	]);

	target = BTL->get_victim(me, target);
	if(!target) return notify_ok("��Ҫ����˭�ĸ��У�");
	if(!BTL->require(me, NAME, req)) return 1;

	if(!cd_start(me, ID, CD)) return notify_ok("����ʱ����ʹ�á�"NAME"����\n");

	BTL->pay(me, req["prop"]);

	msv(MSG0, me, target);

	if(target->is_busy()) thr -= 20;

	if(BTL->cmp_random20(me, target, cmp_parm) > thr) {
		msvx(MSG1, me, target);
		swallow(target, me, DURATION, 110);

		SKILL_D("pansi-dafa")->random_level_up(me);
	} else {
		msv(MSG2, me, target);
	}
	BTL->fight_enemy(target, me);
	return 2;
}


/*****************************���ʺ���*****************************/

mapping _food_cmp = ([
	"prop"		: ([ DEXP : 1, "sen" : 1, "max_sen" : -1, "max_mana" : 3 ]),
	"skill"		: ([ "spells" : 2]),
	"temp"		: ([ "no_cast" : -1]),
]);


private int food_damage(object food)
{
	return food->query_str() / 2 + food->query_temp("apply/damage") * 2;
}

private int food_timer(mapping buff)
{	
	object food = buff["me"];
	object eater = buff["_eater"];
	object env;
	
	int damage;

	if(environment(food) != buff["_env"]) return 0;
	if(!eater || BTL->in_safy(eater)) return 0;

	if(BTL->cmp_random20(eater, food, _food_cmp) > buff["_thr"]) {
		
		string msg = CYN"$N����һ���á�";
		object weapon = food->query_temp("weapon");	
		damage = eater->query("mana_factor") * 2;
		
		eater->add("food", 1 + damage / 10);
		
		if(weapon && random(2)) {
			msv(CYN"һ�ɼ���ӿ����$N���б����ѳֲ�ס�������ˡ�\n"NOR, food);
			weapon->unequip();
			if(weapon->move(environment(eater)))
				msg += "�³�һ" + weapon->query("unit") + weapon->name() + CYN"��";
		} else {
			trace("damage:" + damage);
			msv(CYN"$N���ϵ���Һ���뼡����������ʹ���̡�\n"NOR, food);
			food->receive_wound("kee", damage, eater);
		}
		msv(msg + "\n"NOR, eater);
				
	} else {
		msv(CYN"�ڰ���$N�Ĵ���ͱ�Ҵ�ֻ��������ҽ�һ����һ����\n"NOR, food);

		tell_object(eater, HIR"�㸹��һ�������ʹ���ķΣ�\n"NOR);
		msv(CYN"$Nʹ�����ش����һ�����ҽС�\n"NOR, eater);

		damage = food_damage(food);
		
		trace("damage:" + damage);
		
		if(damage < eater->query("kee"))
			eater->receive_wound("kee", damage, food);
		if(!eater->is_busy()) eater->start_busy(1);
	}
	return 1;
}

//ʳ���뿪������
private int food_out(mapping buff)
{
	object food = buff["me"];
	object eater = buff["_eater"];
	object env = load_object("/d/city/recycle");
	
	if(eater) {
		int damage = food_damage(food) * 2;
		int ratio = BTL->cmp_random20(eater, food, _food_cmp);

		env = environment(eater);
	
		if(!BTL->in_safy(eater) && ratio < buff["_thr"] - 10 
			&& damage < food->query("force")) 
		{
			food->add("force", -damage);

			msv(CYN"$N�þ�ȫ����ǽ��˺��һ�����ӣ����˳�ȥ��\n"NOR, food);
			msv(HIR"$N������Ѫ�Ľ���$n�Ʊ�������\n"NOR, eater, food);
			food->move(env);

			eater->receive_wound("kee", damage, food);
			return 1;
		} else {
			msv(CYN"$NͻȻ����θһ��������������������ء�\n"NOR, eater);
		}
	}
	
	msv(CYN"һ����������ɳ���£�$N���ɼ��������ˡ�\n"NOR, food);
	food->move(env);
	msv(HIC"$Nͷ����Ҷ������׺����ӵ���һԾ����\n"NOR, food);
	return 1;
}

object load_stomach(object who)
{
	string sid = who->query("id") + "'s stomach";
	string sname = RED + who->query("name") + "�ĸ���"NOR;

	object room = load_object("/d/wiz/sleeveroom");		
	object stomach = present(sid, room);

	if(!stomach) {
		stomach = new(X_DIR"obj/fabao/stomach");
			
		stomach->set_name(sname, ({sid, "sleeve"}));
		stomach->set("short", sname);

		stomach->move(room);
	}
	return stomach;
}

//����Ŀ��
int swallow(object eater, object food, int duration, int thr)
{
	object stomach = load_stomach(eater);

	mapping buff = ([
		"id"		: "food",
		"name"		: HIY"ʳ��"NOR,
		"comment"	: "���Ե��ˡ�",
		"duration"	: duration,
		"interval"	: 2,
		"timer_act"	: (: food_timer :),
		"post_act"	: (: food_out :),
		"_eater"	: eater,
		"_thr"		: thr,
		"_env"		: stomach,
	]);

	if(BUFF->add(food, buff)) {
		food->move(stomach);
	}
	return 1;
}
