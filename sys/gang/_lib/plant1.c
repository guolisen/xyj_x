/*

Ŀǰxyj�Ĺ��ߴ������Щ
⨺���;��ź;����;����;�˲ι�
�ƹ�;���;��«;����;����;�ײ�
һ����������ֲ��ؼ��ܣ��ü��ܺ�ֲ�ﱾ�����������ƽ����ʵ�ĳɹ���
һ����û����ֲ���ܣ������ӵ���������ƣ�����rsg���ӳ��ֵĸ��ʺܵͣ�
ֲ�ﱾ�������ʾ��������ʵ�ĳɹ���
���Բ��ð������ӵķ�������Ҳ��ܿ��������������͵����ӣ�
����ȵ���ѿ���֪����
��ֲͬ����˽���ʲ�ͬ����������Ҳ��ͬ��Խ�õ�ֲ�����Խ��
����ͬһ��ֲ��ۼ�ʧ�ܴ����ﵽһ��ֵ��Ȼ�ɹ�
���ڿ��������Լ���Ҫ�����Ӿͻ������е�ֲ��������
��ʵ�ĳɹ��ʺ���ҵȼ���ιҹ���һ����Ҫһ���ж�ȥ���ưװ���ֲ�ɹ��ʣ���Ȼ���׷�
��ʵ�ɶѣ����Խ���topֵ����������׼



ֲ��	
	�׶�	����	��ѿ	С��	С��	����
	


��԰��
	����loose	
	
����
	����	

ֲ��		�¶�	������	������	������	����	��ή��	��Ч

��ɫС��	0-5		
ѩ��		0-5
��ź
����
���
�˲ι�
⨺���

��¯����������Ʒ����������
��ҩ

���е�
��ѧ��
����
����	����������

���絤

����	
����

����


"ī����"	({"mo qilin", "qilin"})				/d/sea/npc/beast/beast4	�����
"һͷ����ī�̵����룬����һͷ���ޡ�\n"

"����"		({"dragon"})						/d/qujing/wudidong/npc/dragon
"һ��������צ�Ķ���������ʮ�ֿ��¡�\n"
"����"		({"huo bing", "bing"})				/d/dntg/laojunlu/npc/huobing
"����",
"��ѻ",
"����",
"�칬��ս�����þ�ɳ����\n"

"�Һ�"		({ "tao he", "taohe","he" })		/d/dntg/pantao/obj/taohe

HIB"��ɫС��"NOR	({"xiao cao", "xiaocao", "cao"}))	/d/obj/misc/xiaocao
"���ֲ�Ҷ��Բ��ɫ����������ȷ�ÿ��� \n"

"ѩ��"		({"xue lian", "xuelian", "lian"}))			/d/moon/obj/xuelian
"һ��ѩ������ֻ�����ھ��弫��֮����\n"

YEL"⨺���"NOR	({"mihou tao","mihoutao","tao"})	/d/obj/drug/mihoutao
"�Ƴȳȵ�һ��⨺��ң�����˴������Ρ�\n"

RED"����"NOR	({"huo zao","zao"})
"unit", "ö"
"һö���Ժ�����ɽ��ɫ���������档\n"			/d/obj/drug/huozao


"�쾦���"										/d/xueshan/npc/hama		���
"���֩��"	({ "wucai zhizhu", "zhizhu" })		/d/xueshan/npc/zhizhu	֩��˿
"˫βЫ"	({ "xiezi jing", "xiezi", "jing" })	/d/xueshan/npc/xiezi	����
"����С��"	({ "chilian xiaoshe", "she" })		/d/xueshan/npc/she		�߶�
"�������", ({ "baizu wugong", "wugong" })		/d/xueshan/npc/wugong	��Һ



��������

����/�¶ȷ�Χ	����Ǵ�ѩɽ������ǻ���ɽ


        message_vision("$Nʹ��ȫ�������ȥ����ʯ����ʯ�������ƿ��ˣ���������������\n",who);
        message_vision("\n������һ�ţ���׼$N��������ɷ۽�����Ļ�����\n", who);
        if( (int)who->query_temp("push_time") > 3) {
                call_out("faint_him", 0, who);
        return 1;
	}

        message_vision("\n$N���յı������ˣ��Ҳ��̶á�\n", who);





*/

//pick cai��ժ

mapping info = ([
	"plant"		: ([
		"birthday"		: 100,		//����ʱ��
		""
	]),
	"animal"	: ([

	]),
	"stove"		: ([
	]),
]);

mapping peach = ([
	"name"			: "����",
	"ids"			: ({"tao shu", "peach", "tree"}),
	"long"			: "\nһ��������������紵����Ҷɳɳ���졣\n",

	"req"			([ "outdoors" : 1, "temperature" : 20 ]);

	"life-span"		: 10,
	"life_old"		: "�ɿݵ�",
	"life_end"		: "$N��$n�������������ӵ���ǽ�⡣",

	"fruit"			: "/d/xiantao",
	"fruit_amount"	: 0,

	//"init_msg"		: ({"������紵��%sҶɳɳ���졣"}),
	
	"work_verb"		: ({"shifei", "manure"}),
	"work_msg"		: "$N��ʼ������ʩ�ʣ�һ����۵ý�ƣ������\n",

	"gather_verb"	: ({"cai", "pick"}),
	"gather_msg0"	: "$N��$n�������˰��죬ʲôҲû���֡�\n",
	"gather_msg1"	: "$N��$n��ժ��$n2��\n",
	
	"feed_verb"		: ({"reng", "bury"}),
	"feed_msg0"		: "$N�뽫$n���˸�$n2�����ϣ������־��ò��̡�",
	"feed_msg1"		: "$N��$n����$n2�£��������µ��������ˡ�",
	
	"seed"			: "/d/taohe",
	"spread_verb"	: ({"zhong", "spread"}),
	"spread_msg0"	: "���ﲻ����ֲ����������ˡ�",
	"spread_msg1"	: "$N�������εİ�һ��$n���������������ˮ��",
]);

mapping hama = ([
	"name"			: "�쾦���",
	"ids"			: ({"bing chan", "hama", "toad"}),
	"long"			: "\nһֻ����ܣ�ͨ��ѩ�ף�����ȴѪҲ��죬ģ�����ǿɰ���ȴҲ��\n���к�����֮����\n",

	"req"			([ "outdoors" : 0,  "temperature" : 20 ]);

	"life-span"		: 10,
	"life_old"		: "������",
	"life_end"		: "$N��������$n���˳�����$n��$N���ϲ��˲䣬���������ˡ�",

	"fruit"			: "/d/chansu",
	"fruit_amount"	: 0,
	
	"work_verb"		: ({"qingli", "clean"}),
	"work_msg"		: "$N��ʼ����������������һ����۵ý�ƣ������\n",
		
	"gather_verb"	: ({"pai", "pat"}),
	"gather_msg0"	: "$N����������$n����������û�κη�Ӧ��\n",
	"gather_msg1"	: "$N����������$n���Ӷ���󼷳�$n2��\n",
	
	"feed_verb"		: ({"reng", "feed"}),
	"feed_msg0"		: "$N�뽫$nι$n2�������־��ò��̡�",
	"feed_msg1"		: "$N��$n�ӽ�������$n2��ǰһ�����¡�",

	"seed"			: "/d/hama",
	"spread_verb"	: ({"yang", "breed"}),
	"spread_msg0"	: "���ﲻ��Ȧ������Ķ����ˡ�",
	"spread_msg1"	: "$N���$n�Ž����������Ļ�ϲ�Ĺ����š�",
]);


mapping daoxingdan = ([
	"name"			: "��¯",
	"ids"			: ({ "dan lu", "lu", "stove" }),
	"long"			: "\n����һ��һ�˶�ߵ���ɫ��¯�����������ŷ���׵磬���а��Ը�\n��ͼ����\n",

	"req"			([ "outdoors" : 0 ]);

	"fruit"			: "/d/daoxingdan",
	"fruit_amount"	: 0,
	
	"work_verb"		: ({"huo", "fire"}),
	"work_msg"		: "$N�³�һ�Ż𣬻���ע��¯�У�����̱���ڵء�\n",

	"gather_verb"	: ({"mo", "grope"}),
	"gather_msg0"	: "$N�������$n�һ���������������$N�ս���\n",
	"gather_msg1"	: "$N�������$n�ת������%s��\n",

	"feed_verb"		: ({"reng", "smelt"}),
	"feed_msg0"		: "$N�뽫$n�ӽ�%s�������־��ò��̡�",
	"feed_msg1"		: "$N��$n�ӽ���¯��ת��$n�ͱ����������ˡ�",

	"seed"			: "/d/danlu",
	"spread_verb"	: ({"fang", "place"}),
	"spread_msg0"	: "���ﲻ�ܷ��ø����%s�ˡ�",
	"spread_msg1"	: "$N���$n���£������׵���",

]);

//��
//��¯Ҫ���ӽ�ȥ�Ķ���������������


mapping chansu = ([
	"name"			:"���",
]);
