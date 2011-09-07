
inherit __DIR__"hp";

#include <ansi.h>

mapping spell_list = ([
	"buddhism"		: "大乘佛法",
	"dao"			: "道家仙法",
	"taiyi"			: "太乙仙法",
	"moonshentong"	: "月宫神通",

	"yaofa"			: "妖法",
	"dengxian-dafa"	: "登仙大法",
	"pansi-dafa"	: "盘丝大法",
	"pingtian-dafa"	: "平天大法",

	"baguazhou"		: "八卦咒",
	"gouhunshu"		: "勾魂术",
	"seashentong"	: "碧海神通",
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
		//统计法术实力
		foreach(string id, string name in spell_list)
		{
			int lvl = user->query_skill(id, 1) / 20;
			int score = lvl * lvl * lvl;
			spells["score"][id] += score;
			spells["sum"] += score;
		}
		//统计门派实力
		{
			string id = user->query("family/family_name");
			int score = eval(user);
			family["score"][id] += score;
			family["sum"] += score;
		}
		reset_eval_cost();
	}

	//排序法术
	spells["top"] = sort_array(keys(spells["score"]), "cmp_spells");

	//排序门派
	family["top"] = sort_array(keys(family["score"]), "cmp_family");

	return 1;
}

varargs void list(mapping tab, string title, function trans)
{
	int avg = tab["sum"] / sizeof(tab["top"]);
	printf("\n『" + title + "实力』排行榜：\n");
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	printf("    名称                            实力    相对于均值的比例\n");
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	for(int i = 0; i < sizeof(tab["top"]); ++i) {
		string id = tab["top"][i];
		printf(NOR"%-4d%-32s%-8d%d%%\n"NOR,
			i + 1,
			trans ? evaluate(trans, id) : id,
			tab["score"][id],
			tab["score"][id] * 100 / avg
		);
	}
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
}

private string trans_mp(string str)
{
	return str ? str : "百姓";
}

private string trans_sp(string str)
{
	return spell_list[str];
}

int do_top(string arg)
{
	if(!spells) do_stat();
	if(arg == "spells") list(spells, "法术", (: trans_sp :));
	else if(arg == "menpai") list(family, "门派", (: trans_mp :));
	else write("指令用法：top menpai | spells\n");
	return 1;
}

//实力相对于均值的比例(单位%)
int str_pct(string subject, string id)
{
	mapping tab = subject == "spells" ? spells : family;
	int avg = tab["sum"] / sizeof(tab["top"]);
	return tab["score"][id] * 100 / avg;
}