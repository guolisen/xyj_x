// by firefox 11/21/2009
// 战场NPC模板

inherit NPC;

#include <ansi.h>
#include <xyj_x.h>

#define	NORM_RATIO			20

string do_reward();

void setup()
{
	set("str", 100);
	set("con", 300);
	set("spi", 300);

	set("combat_exp", 5000*K);
	set("daoxing", 8000*K);

	HP->to_max(_this);

	set("chat_chance_combat", 80);
	set("chat_msg_combat", ({
		(: cast_spell, "bighammer" :),
		})
	);

	set("inquiry", ([
		"领赏"		: (: do_reward :),
		"reward"	: (: do_reward :),])
	);

	set_temp("invite", "public");		//邀请玩家加盟
	//me->set_temp("accept",obj->query("id"));

	::setup();
}

void unconcious()
{
	die();
}

void die()
{
	HP->full(_this);
}

#define REWARD_POT			100*K

string do_reward()
{
	string* gift = ({ "dan-huan", "dan-7", "dan-cool" });
	int i = time() / 3600 / 24 % 3;
	object ob;
	
	if(ALX->score_balance(_player) < REWARD_POT) return "你寸功未立，何谈领赏？";
	if(total_exp(_player) < 5*K*K) return "你现在修为尚浅，日后定有重赏！";

	ob = new_to(X_DIR"obj/gift/" + gift[i], _player);

	if(!ob) return "你拿不了更多东西了。";

	//检查配额
	if(TASK_EXC->do_reward(_player, name(), "领赏", ob->query("rewards"), NORM_RATIO)) 
	{
		ALX->score_use(_player, REWARD_POT);

		msvx(CYN"$N给$n一粒%s。\n"NOR, _this, _player, ob->name());
		return "嗯，你战功卓著，当受此奖！";
	}
	destruct(ob);
	return "你先去休息吧，过些时日再来。";
}

