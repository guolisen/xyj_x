
inherit __DIR__"hp";

#include <ansi.h>

mapping spell_list = ([
	"buddhism"		: "��˷�",
	"dao"			: "�����ɷ�",
	"taiyi"			: "̫���ɷ�",
	"moonshentong"	: "�¹���ͨ",

	"yaofa"			: "����",
	"dengxian-dafa"	: "���ɴ�",
	"pansi-dafa"	: "��˿��",
	"pingtian-dafa"	: "ƽ���",

	"baguazhou"		: "������",
	"gouhunshu"		: "������",
	"seashentong"	: "�̺���ͨ",
]);

mapping spells;
mapping family;

private int cmp_spells(string spells1, string spells2)
{
	return spells["score"][spells1] <= spells["score"][spells2] ? 0 : -1;
}

private int cmp_family(string family1, string family2)
{
	return family["score"][family1] <= family["score"][family2] ? 0 : -1;
}

int do_stat()
{
	spells = ([ "score" : ([]), "sum" : 1 ]);
	family = ([ "score" : ([]), "sum" : 1 ]);

	foreach(object user in users()) {
		if(wizardp(user) && !user->query("test_not_wizard")) continue;
		if(user->query("test_exclude")) continue;
		//ͳ�Ʒ���ʵ��
		foreach(string id, string name in spell_list)
		{
			int lvl = user->query_skill(id, 1) / 20;
			int score = lvl * lvl * lvl;
			spells["score"][id] += score;
			spells["sum"] += score;
		}
		//ͳ������ʵ��
		{
			string id = user->query("family/family_name");
			int score = eval(user);
			family["score"][id] += score;
			family["sum"] += score;
		}
		reset_eval_cost();
	}

	//������
	spells["top"] = sort_array(keys(spells["score"]), "cmp_spells");

	//��������
	family["top"] = sort_array(keys(family["score"]), "cmp_family");

	return 1;
}

varargs void list(mapping tab, string title, function trans)
{
	int avg = tab["sum"] / sizeof(tab["top"]);
	printf("\n��" + title + "ʵ�������а�\n");
	printf("��������������������������������������������������������������������\n");
	printf("    ����                            ʵ��    ����ھ�ֵ�ı���\n");
	printf("��������������������������������������������������������������������\n");
	for(int i = 0; i < sizeof(tab["top"]); ++i) {
		string id = tab["top"][i];
		printf(NOR"%-4d%-32s%-8d%d%%\n"NOR,
			i + 1,
			trans ? evaluate(trans, id) : id,
			tab["score"][id],
			tab["score"][id] * 100 / avg
		);
	}
	printf("��������������������������������������������������������������������\n\n");
}

private string trans_mp(string str)
{
	return str ? str : "����";
}

private string trans_sp(string str)
{
	return spell_list[str];
}

int do_top(string arg)
{
	if(!spells) do_stat();
	if(arg == "spells") list(spells, "����", (: trans_sp :));
	else if(arg == "menpai") list(family, "����", (: trans_mp :));
	else write("ָ���÷���top menpai | spells\n");
	return 1;
}

//ʵ������ھ�ֵ�ı���(��λ%)
int str_pct(string subject, string id)
{
	mapping tab = subject == "spells" ? spells : family;
	int avg = tab["sum"] / sizeof(tab["top"]);
	return tab["score"][id] * 100 / avg;
}