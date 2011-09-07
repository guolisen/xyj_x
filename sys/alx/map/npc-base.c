// by firefox 11/21/2009
// ս��NPCģ��

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
		"����"		: (: do_reward :),
		"reward"	: (: do_reward :),])
	);

	set_temp("invite", "public");		//������Ҽ���
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
	
	if(ALX->score_balance(_player) < REWARD_POT) return "��繦δ������̸���ͣ�";
	if(total_exp(_player) < 5*K*K) return "��������Ϊ��ǳ���պ������ͣ�";

	ob = new_to(X_DIR"obj/gift/" + gift[i], _player);

	if(!ob) return "���ò��˸��ණ���ˡ�";

	//������
	if(TASK_EXC->do_reward(_player, name(), "����", ob->query("rewards"), NORM_RATIO)) 
	{
		ALX->score_use(_player, REWARD_POT);

		msvx(CYN"$N��$nһ��%s��\n"NOR, _this, _player, ob->name());
		return "�ţ���ս��׿�������ܴ˽���";
	}
	destruct(ob);
	return "����ȥ��Ϣ�ɣ���Щʱ��������";
}

