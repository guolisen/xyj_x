// by firefox 04/10/2010
// 门派任务

#include <xyj_x.h>

inherit TT_Q4;
inherit TDB_FAMILY;

void create()
{
	init_prop(2400);
	tdb_load(X_DATA_DIR + "task/forces/_" + id());
}


//获取提示信息集合
mapping get_msg(object employer)
{
	return ([
		"task"			: ([			
			"ask"			: "$N对$n说道：你代为师走一趟，去拜见%s询问有关%s一事。\n",
			"kill"			: "$N对$n说道：%s残害本门弟子，罪不可赦，你去代为师除了！\n",
			"give"			: "$N对$n说道：%s托付为师寻找%s，你去代办吧。\n",
		]),
		"no_norm"		: "来日方长。",
		"apply_say"		: "路上小心。",
		"check_say"		: "你修为尚浅，还是多加修炼吧。",
	]);
}

//给予奖励，奖励需要修改
void give_reward(object who, int reward)
{
	mapping m = data_of(who);
	int wx = reward / 2;
	int qn = reward / 2 / 4;

	who->add(CEXP, wx);
	who->add(PEXP, qn);
	parent()->add_gain(who, CEXP, wx);
	parent()->add_gain(who, PEXP, qn);

	tell_object(who, "你得到了" + chinese_number(wx)
		+ "点武学经验和" + chinese_number(qn) + "点潜能！\n");
}

