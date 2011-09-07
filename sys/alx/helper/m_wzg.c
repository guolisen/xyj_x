// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"m_base";

string* _poem = ({

"
    ���˼��������֣������̽�ն����
    ��Ȼ������ͷ�䣬����̾�����ݡ�
",
"
    ̤�裬̤�裬���ɺͣ�
    ����ת���Σ�
    ����������������һ����
    ���˻��ȥ���������˷׷������ࡣ
    �����ﵽ���䣬ĺ��ɣ�����ײ���
    ���������ڿռʣ��������ڸ��϶롣
",
"
    ������Ϊ�����������������ѡ�
    ��ʱ���Ƿ���ȥ���������һ�㴺��
",
"
    ���Ц����������һ���ɷ���·ң��
    ��ȥ����Ū���£�����ƺ������ 
",

});

mapping* _npc = ({
	([
		"name"		: "������",
		"ids"		: ({"lu dongbin", "lu", "dongbin"}),
		"cloth"		: "/d/obj/cloth/xianpao",
		"weapon"	: "/d/obj/weapon/sword/changjian",

		"prop"		: ([
			"title"		: "������",
			"gender"	: "����",
			"age"		: 35,
			"per"		: 30,
			"long"		: "�������������Ԫ����������ĵ����ˣ��Ĳɷ�����ɫ�����졣\n",
		]),
	]),
	([
		"name"		: "���ɺ�",
		"ids"		: ({"lan caihe", "lan", "caihe"}),
		"cloth"		: "/d/obj/cloth/linen",
		"weapon"	: "/d/obj/weapon/blade/yanblade",

		"prop"		: ([
			"gender"	: "����",
			"age"		: 18,
			"per"		: 20,
			"long"		: "һλ������Ƶ����ꡣ\n",
		]),
	]),
	([	
		"name"		: "������",
		"ids"		: ({"han xiangzi", "han", "xiangzi"}),
		"cloth"		: "/d/obj/cloth/choupao",
		"weapon"	: "/d/obj/weapon/sword/zijinxiao",

		"prop"		: ([
			"gender"	: "����",
			"age"		: 22,
			"per"		: 30,
			"long"		: "��һλ�����������๫�������ӱ�������֮��ȴ��ϲ�������ˡ�\n�������г��������ѧ������š�\n",
		]),
	]),
	([
		"name"		: "���ɹ�",
		"ids"		: ({"he xiangu", "he", "xiangu"}),
		"cloth"		: "/d/obj/cloth/skirt",
		"weapon"	: "/d/obj/weapon/sword/heye",

		"prop"		: ([
			"gender"	: "Ů��",
			"age"		: 25,
			"per"		: 20,
			"long"		: "���ɹ������Ԫ����ϲ������λͬ�Ŵ��������á�\n���ɹ�ԭ������ã������ǿ��������ģ���Ͷ����ׯ��ǰ�ǵ��������ġ�������ʩ����\n",
		]),
	]),
});


void create()
{
	int i = random(sizeof(_npc));
	mapping m = _npc[i];

	set_name(m["name"], m["ids"]);
	foreach(string k, mixed v in m["prop"]) {
		_this->set(k, v);
	}
	

	create_family("��ׯ��", 3, "����");

	SKI->set_list2(_this, FAMILY->skills_of("��ׯ��"), 1);

	set_events(
		([
			"born"		: "\n����д���һ��������\n"HIC + _poem[i] + NOR"\n$N����һ�����ƻ������¡�",
			"leave"		: CYN"$N˵�����������£�ˡ�����㡣˵�ռ��ƶ�ȥ��",

			"cmds"		: ({ "cast zhenhuo", "cast zhenhuo", "cast qimen" }),
		])
	);

	setup();

	carry_object(m["cloth"])->wear();
	carry_object(m["weapon"])->wield();

}




/*
�Ź���

�޳ɽ�������棬
�������ٲ��ƴ���
Ұ�����������㣬
�л����԰����¡�
��ҡ��ɉ�ú���
ˮ����ɰ�����ۡ�
�������ɶ���죬
�Ͻ��ټ��ں쳾��


����Ȩ

���Գ�Я��һ����
����˫��ʶ�ʶ���
Ǭ����������գ�
��ɢ����һ�ɷ�

*/