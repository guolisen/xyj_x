// by firefox 11/21/2009


С������������צ����ٽ𹿡��Ǹ��봹�����ߣ�����ۻϳ��ơ��Ǹ����������������������������硣�Ǹ�����ү���ҵ�ӣ���������콫������������������������ĥ�ۣ���Ҫ�ɹ������ܡ���

/d/sea/girl3

/d/sea/npc/longnu





/*
���ڱ仯���������ơ�
��צ�����ף������辵����
��Ʈ��������ˬ����������ͦͦ�塣
�Ķ��Ρ��Բ��������
����Ī�ܲ⣬���ﲻ������
������ʱ���꣬���缴�����硣
�����������ʥ�����������ͷ��Ƶ�ͥ��
*/
mapping _trait = ([
	"����"	: ([
		"ids"			: ({"cang dragon", "dragon"}),
		"long"			: "һ�����������Ƴ��ߡ������ס�����β�����г��롢������¹������צ��",
		"color"			: HIC,
		"spells"		: "seashentong",
		"act"			: function(object target, mapping buff) {
			//�˺���
		},
	]),
	"����"	: ([
		"ids"			: ({"fire dragon", "dragon"}),
		"long"			: "һ��������ȫ���л���ơ�",
		"color"			: HIR,
		"spells"		: "taiyi",
		"act"			: function(object target, mapping buff) {
		},
	]),
	"����"		: ([
		"ids"			: ({"poison dragon", "dragon"}),
		"long"			: "һ����������ɣ����ɫ���������ġ�",
		"color"			: HIB,
		"spells"		: gouhunshu,
		"act"			: function(object target, mapping buff) {
			//�ж�
		},
	]),
	"����"	: ([
		"ids"			: ({"cold dragon", "dragon"}),
		"long"			: "һ���������������ˡ�",
		"color"			: HIW,
		"spells"		: "dengxian-dafa",
		"act"			: function(object target, mapping buff) {
			//no_move
		},
	]),
	"����"	: ([
		"ids"			: ({"cang long", "long", "dragon"}),
		"long"			: "һ��������״���ߣ����绢������ţ�������ɡ�",
		"color"			: HIG,
		"spells"		: 50,
		"act"			: function(object target, mapping buff) {
			//
		},
	]),
]);

mapping buff = ([

	"add_apply"	: ([
		"armor"		: 100,
		"unarmed"	: 100,
		"parry"		: 100,			//�첲�֣����мܣ�combatd�п����гͷ�
		"force"		: 100,			//���roar
		"dodge"		: 100,			//����̫������ת��Ų
		"personality"	: -30,			//���Ƚ�����
	]),

	"replace"	: ([
		"limbs"		: ({ "ͷ��", "����", "ǰצ", "β��", "��Ƥ", "��צ"}),
	]),

	"add"		: ([
		"max_kee"	: 100,
		"kee"		: 100,
	]),
	"start_msg"	: HIC"$N��Ϊһ��������צ��%s"HIC"���˵�ɱ�����ˡ�",
	"stop_msg"	: HIC"$N�������ķ�����һ������ϣ�����Ҳ������ԭ�ˡ�",
	"post_act"	: function(mapping buff) {
		object me = buff["me"];
		me->receive_curing("kee", 1);
		me->receive_heal("kee", 1);
	},
	"interval"	: 4,
	"timer_act"	: (: on_timer :),	
]);

