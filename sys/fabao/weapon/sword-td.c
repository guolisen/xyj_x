// by firefox 11/21/2009

/*
��������������

��ȷ�Ƶ��������������£�

1.����������������½���֮�����������˴���ݽ�����
2.����ʫ�������������ɽ�ȡ��ͷ��Ӧ�����Դ�ʫ����ȫ��ʫ����С��̫����ˡ�

�������͡�

��������ò�������΄����՚���e��
�B�����ؼ���ȥ���HȻ���Y���^�䡣

���ˡ����䡷��

�����Ǳ��f���D���L�וr�����֡�
���^�y̎�����ڣ����¸����^�����

���У���̶���Q����

�@����Ҋ���o�����MԺ�L��С���졣
һ���������wȥ����ͥ�@�������ߡ� 

�������ǣ����^�䡷

���¶��[���չ�����횿��P�c������
ż�򲩑��w�񄦣��݅s�K�ϵ�һ�塣 

�|ɽ�|�Ϻ���꣬���ֶ���Z��犡�
���g�ѳɾ���ȥ��������̎��������

������ͬ�˷������룺

�����n��ĺ�s߀�����������Ҟ��졣
ϻ�Ќ����r�r�𣬲���ͬ���Ĳ�����

�������ˣ��Ĵ������ˣ����}�P�踮��c�^��

�õ����˰�������w��ȡ���^��
���δ�����������؛�����������


ĥ����ţ�����󣺡������Ϻ����^��ʿ���û�ĥ����

�����h䀸ґ��ڣ��R���_ϻ�����ơ����К�ű����ߣ�
ʯ�Ͼ�����һ�l����ѪĬ�S��ˮ�M���׺�����n������
��ƽ������ƽ�£��c�������Ͼ����� 

���}ȫ�ݵ�ʿ�Y���ڡ��������ʲô���ã�

����߸躣��ɽ����ư��¶�Y�𵤡�
ҹ���Q͸��ձ̣��f�����Lһ������ 

����ǰֻ�ᱳ���ף���������

���˼����w���֣����g�̄��ط���
�mȻ��Ҋ���^�䣬���Y�̾�����ݡ� 


ɫ�������£��������ɣ�ţƤ���죡
˭��MUD���μ�����ɰ����ˣ���Ȼ�ǅ��ң�
����������ɮ������꣬����XYJ2000����ä��ͳ���͵���֪����

ȫ��ʫ��http://www.xysa.com/quantangshi/t-858.htm
*/

#include <weapon.h>
#include "_base.h"

inherit SWORD;

void create()
{
	set_name("������", ({"sword"}));
	set_weight(400);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("material", "steel");
		set("wield_msg", "$һ���ͺ��绢Х������$N���ж���һ��$n��\n");
	}

	init_sword(1);
	setup();
}

#define CD_ID				"dance"

void init_var()
{
	_subs = ([
		"��ݽ�"		: ([
			"ids"			: ({"tiandun jian", "jian", "sword"}),
			"long"			: "һ�����������ı�����",
			"color"			: HIW,
			"unit"			: "��",
		]),
		"������"		: ([
			"ids"			: ({"yulong hao", "hao", "sword"}),
			"long"			: "��������һ�����ͳ����ƽС�",
			"color"			: HIW,
			"unit"			: "��",
		]),
	]);

	
	//����������/�ڹ���
	_trais = ([

		//���ٷֱȼӳɵ�����
		"prop_x"	: ([
			"spells"		: 10,
		]),

		"prop_x"	: ([
			"damage"		: 40,		//1M 5�㣿
		]),
	]);

	_act = ([
		"exp_x"			: 50,					//50%�ľ�����������

		"cd_id"			: CD_ID,				//��CD��ID�����ַ������ܹ�CD
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
		"msg_start"		: "$N����������ȥ��ȥ��ȥ��������һ������%s�ڿն�ȥ��",
		"msg_success"	: HIW"һ���׺���������ֱֱ����$N����δ���ֵ��㱻���ڵ��ϡ�",
		"msg_fail"		: HIW"һ���׺���������ֱֱ����$N�����������������û�����С�",
		"msg_back1"		: "$N���аγ����Ʒ��ȥ��\n",
		"msg_back2"		: HIW"һ���׺�����������Ȼ����$N�Ľ����С�",
		"msg_head"		: "����ͨ��һ����һ���������$N�űߣ�������ȥ��",
	]);
}


//����Ŀ�� ���ˣ�˫��������
int ji(string tid)
{
	int fabao_exp = _act["exp_x"] * _exp / 100;
	object who = _player;
	object target = tid ? present(tid, environment(who)) : 0;

	if(target) return notify_fail("Ŀ�������ǰ����ȥ���ɡ�\n");

	target = find_player(tid);
	if(!target) find_living(tid);

	if(!target) return notify_fail("����ָ��һ��Ŀ�ꡣ\n");

	if(!BTL->require(who, NAME, _act["req"])) return 1;
	if(!cd_start(me, ID, CD)) return notify_fail("����ʱ������ʹ��"NAME"��\n");

	BTL->pay(me, _act["req"]["prop"]);


	MSG->vision(_act["msg_start"] + NOR"\n", who, target, _this->name());

	{
		object env = environment(target);
		mapping cmp = ([ ({fabao_exp, target->query(DEXP)/FABAO_EXP_X }) : 5 ]);
		cmp += _act["cmp"];

		if(BTL->random_cmp(who, target, cmp_parm) >= _act["threshold"]) {
			int damage = 1000;
			MSG->vision(_act["msg_success"] + NOR"\n", target, 0, _this->name());
			//�˺�����kill
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

//�ȼ��룬������˾͡����꡻
void cut_head(string name, object env, object killer)
{
	object corpse = present_name(name + "��ʬ��", env);

	if(!killer) return;
	msv(_act["msg_back1"] + NOR"\n", _this);
	msv(_act["msg_back2"] + NOR"\n", killer);
	_this->move(killer);

	if(corpse) {
		object head = new ("/d/qujing/jilei/obj/head");
		head->set_name(name + "��ͷ", ({"tou"}));
		head->set("long", "һֻͷ­��Ѫ��δ�ɡ�\n");
		if(head->move(environment(killer)))
			msv(_act["msg_head"] + NOR"\n", killer);

		corpse->set("name", "��ͷʬ��");
	}
}
