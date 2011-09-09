// by firefox 04/10/2010
// 开封解谜任务模板

#include <xyj_x.h>

inherit TT_Q4;

//本任务的彩云属性
string colors_prop()
{
	return _stat_prop + "/colors/" + id();
}

//检查前提条件
int pre_check(object employer, object who)
{
	mapping msg = get_msg(employer);
	mapping m = data_of(who);

	if(m["state"] == "进行") {
		msvx(msg["repeat"], employer, who, m["tname"]);
		return 0;
	}
	if(who->query(_stat_prop + "/balance") > 0) {
		msvx("$N对$n说道：这位$r，$S见你身上祥云环绕，何不去从速赴长安进宫请赏？\n", employer, who);
		return 0;
	}
	return 1;
}

//新任务
void new_task(object who, mapping task)
{
	::new_task(who, task);
	
	//if(who->query(colors_prop())) task["remark"] += "*";		//让用户知道几彩了
}


//兑现奖励，开封任务需要兑换，以及数花色
void give_reward(object who, int reward)
{
	who->add(_stat_prop + "/balance", reward);		//任务奖励可兑换的余额
	who->add(colors_prop(), 10);
}

