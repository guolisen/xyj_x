// by firefox 11/21/2009

#include "race.h"
/*
��ţ


ţ��������Ц��һЦ���ֳ�ԭ��һֻ���ţ��ͷ����룬�������⣬
��ֻ���������������������С�
��ͷ��β����ǧ���ɳ��̣������������а˰��ɸ���

��ţ������������������ʮ��ϣ��ֵв�ס���������������ߡ�
������̨ɽ��ħ����ͨ����÷������ס������ţħ����������ȥ���ҵ�������Ĳ�����������������޵�������������Ҳ����
��˵�䣬����д�ʥ���˽䡢���������
��ħ����ת�������ߣ���ײ�Ŷ�üɽ��������������ʤ����յ�ס�ȵ���������ּ�ڴˣ���Ҫ��ס��Ҳ����ţ���ĻŽ����������������ߣ�ȴ��������ɽĦ������¬ɳ�Ŵ������ӭס����������ţ���������������������������Ҳ����ţ�����Ȼ���ˣ��������ߣ�����������ɽ��ϼ�벻��������ס��յ�ס�ȵ����������ֽ����ߣ���������������·������ԣ��ڴ˰ѽأ�˭����Ҳ��������ţ�ľ���ս����֮������


��ʹն������������һ�ӣ������ðѸ�ţͷն�¡������յ���ȴ�������������
��ţ��ǻ���������һ��ͷ�������º������۷Ž�⡣����߸�ֿ�һ����ͷ�䴦�������һ��ͷ����

��߸ȡ�����ֶ���������ţ�Ľ��ϣ��㴵��������棬��ţ���յ��ſ�����ҡͷ��β����Ҫ�仯�����ֱ�������������������ס�������ǲ������޼�������ֻ�С�Ī����������Ը��˳���Ҳ������߸��������ϧ�������������ӳ�������ţ����������������ɽ�޴�����������

��߸��˵�����������ӽ��£��������Ǿ����ϣ�һ����ס��ͷ���������ڱǿ������ǣ����






*/

mapping _arrive = ([
	"place"	: "/d/gao/daotian1",
	"sb."	: "/d/gao/npc/bull",
	"msg"	: "����ͨһ�����ڵ��ϣ������˹�����",
]);

//����
int arrive(object who)
{
	string name = random1(keys(_names));


	if(who->move(_arrive["place"])) {
		object env = environment(who);
		object sb = new(_arrive["sb."]);
		sb->move(env);
		msv(_arrive["msg"], who, sb);		
	}
}


string _long = @LONG

һͷţ��ͷ����룬�������⣬��ֻ���������������������С�
��ͷ��β����ǧ���ɳ��̣������������а˰��ɸ��¡�

LONG;

string _limbs = ({ "ͷ��", "����", "ǰצ", "β��", "��Ƥ", "��צ"});

//��������
mapping _names = ([
	"��ţ"	: ([
		"ids"			: ({"bai niu", "niu", "cattle"}),
		"long"			: _long,
		"color"			: HIW,
		"unit"			: "ͷ",
		"limbs"			: _limbs,
	]),
	"��ţ"	: ([
		"ids"			: ({"qing niu", "niu", "cattle"}),
		"long"			: _long,
		"color"			: HIC,
		"unit"			: "ͷ",
		"limbs"			: _limbs,
	]),
]);

//�õ��������
string random_name()
{
	return random1(keys(_names));
}



//����������Ϣ
mapping add_desc(mapping trait, string name)
{
	mapping m = _names[name];
	trait["name"]	= name;
	trait["ids"]	= m["ids"];
	trait["short"]	= m["color"] + name + NOR + "(" + capitalize[m["ids"][0]] + ")";
	trait["long"]	= m["long"];
	trait["unit"]	= m["unit"];
	trait["limbs"]	= m["limbs"];
	return trait;
}

//��ȡ������еĸ�������
mapping query_trait(string name)
{
	mapping m = _names[name];
	mapping trait = ([
		"bonus"		: 1,		//�����׺��Լ�ת��
		"kee"		: 100,		//��Ѫ����
		"sen"		: 100,		//��������
		"add_apply"	: ([
			"armor"		: 100,
			"strength"	: 100,
			"unarmed"	: 100,
			"parry"		: 100,			//�첲�֣����мܣ�combatd�п����гͷ�
			//"force"		: 100,			//���roar
			"dodge"		: 100,			//����̫������ת��Ų
		]),
		
		"interval"	: 4,
		"timer_act"	: (: on_timer :),
		"_post_act"	: 0,
	]);

	return add_desc(trait, name);
}

//ʩչ���־���
int unique_skill(object me, object target)
{
	object weapon = ob->query_temp("weapon");
	string wname = "˫��";
	string act = "��";
	string msg = "\n$n����%s�����һ����ţͷ%s��������\n" +
		"$Nǻ�������һ��ţͷ�������º������۷Ž�⣡\n";
	if(weapon) {
		mapping tab = ([
			"hand"		: "��",
			"axe"		: "��",
			"blade"		: "��",
			"sword"		: "��",
			"dagger"	: "��",
			"fork"		: "��",
			"hammer"	: "��",
			"spear"		: "��",
			"staff"		: "ɨ",
			"stick"		: "ɨ",
			"throwing"	: "��",
			"whip"		: "��",
			"mace"		: "��",
		]);
		string act1 = tab[weapon->query("skill_type")];
		if(act1) {
			wname = weapon->query("name");
			act = act1;
		}
	}
	MSG->vision(msg, me, who, wname, act);

	new("/d/qujing/jilei/obj/head")->move(environment(me));
	return 0;
}

