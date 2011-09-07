// by firefox 11/21/2009

inherit NPC;
inherit F_MASTER;

#include <ansi.h>
#include <xyj_x.h>

#define DONKEY			"/d/qujing/wuzhuang/npc/xiaomaolu"

int _index = 0;
int _dying = 0;
object _donkey;

mixed* _tab = ({
	({ "��ϼ", ({ "zi xia", "zixia", "zi", "xia" }),		"��˿����"}),
	({ "��ϼ", ({ "qing xia", "qingxia", "qing", "xia" }),	"�����о" }),
});

int do_sth();
string ask_for_leave();

//��ȡ��ǰID
string the_id()
{
	_index = at_night();
	if(_dying) _index = 0;	//��ֹ��ϼ�ڽ�������ʱ�����ϼ

	set_name(_tab[_index][0], _tab[_index][1]);
	set("title", _tab[_index][2]);
	return query("id");
}

void create()
{
	the_id();
	
	set("long", @LONG

���ε����ӣ���Թ����������������

LONG
	);
	set("title", "��˿����");
	set("gender", "Ů��");
	set("age", 20);
	
	set("per", 30);
	set("str", 10);
	set("con", 500);
	set("spi", 500);
	set("cps", 60);

	create_family("��˿��", 1, "��ʦ");

	set("combat_exp", 3000*K);
	set("daoxing", 4000*K);

	SKI->set_list(this_object(), ({
		({ "literate",		120, }),
		({ "ziqing-sword",	200,	"sword",	180,	"parry",	180,	"dodge",	180 }),
		({ "pansi-dafa",	200,	"spells",	200 }),
		({ "lotusforce",	180,	"force",	180 }),
	}));

	set_temp("apply", ([ "attack" : 500, "defense" : 500, "armor" : 800 ]));

	HP->to_max(_this);

	set("chat_chance", 1);
	set("chat_msg", ({
		(: do_sth :), 
	}) );

	/*set("chat_chance_combat", 80);
	set("chat_msg_combat", ({
		//(: cast_spell, "love" :),
		//��������
	}) );*/

	set("inquiry", ([
		"����" : (: ask_for_leave :),
		"leave" : (: ask_for_leave :),
	]) );

	setup();

	carry_object("/d/moon/obj/luoyi")->wear();
	carry_object(__DIR__"equ/zq-sword")->wield();

	//FABAO_D->carry(_this, "hand-bell")->wear();
	//RACE_D->set(_this, "human", "��о", 10);
}

void remove()
{
	if(_donkey) {
		_donkey->move("/obj/empty");
		destruct(_donkey);
	}
}


void init()
{
	the_id();

	add_action("do_agree", "agree");

	::init();
	if(userp(_player)) call_out("mount_lu", 1);
}

void mount_lu()
{	
	if(_index == 0 && _env->query("outdoors"))	{
		if(!_donkey) _donkey = new(DONKEY);
		if(!same_env(_this, _donkey)) _donkey->move(_env);
	}
}

int do_sth()
{
	mixed* arr = ({
		({
			"$N˵�����ҵ��������Ǹ�����Ӣ��...",
			"$N˵������֪����һ��������һ��������Ŀ������³���...",
			"$N˵�����������ʥ�£� ��̤��ɫ�Ʋ���Ȣ��...",

			"$N����������Ŀ��ǰ�������ĵ�Ц�ˡ������������������ˡ�",
		}),
		({
			"$N���ޱ��飬������˪��",
			"$N˵��������!",
		}),
	});
	string str = CYN + random1(arr[_index]) + "\n"NOR;
	msv(str, _this);
}

/*****************************��������*****************************/

void dying(object killer, object wukong)
{
	msv(CYN
		"ͻȻ�������ӿ��$N������ͷ����������һϢ��$n��ʧ��������\n"
		"$n˵�����ҵ��������Ǹ�����Ӣ��...�Ҳ�����ǰͷ�������Ҳ²�������...\n", wukong, _this
	);

	shout(HIW + wukong->name() + "һ���������쳹������\n"NOR);
	wukong->set_leader(killer);
	wukong->kill_ob(killer);

	killer->start_busy(5);
}

void unconcious()
{
	die();
}

void die()
{
	if(_index) {
		if(_env) msv(HIC"\n\nֻ��$N����һ����⣬��ʧ���١�\n\n"NOR, _this);
		destruct(_this);
	} else {		
		object killer = query_temp("last_damage_from");
		object env = environment(_this);
		object wukong = ACTOR_D->find("wukong");
		
		if(env->query("outdoors")
			&& same_env(_this, killer) 
			&& wukong 
			&& wukong->move(env))
		{
			if(!_dying) {
				_dying = 1;
				dying(killer, wukong);
				destruct(_this);
			}
		} else {
			if(_env) msv(HIC"\n\nֻ��$N����һ���Ϲ⣬��ʧ���١�\n\n"NOR, _this);
			destruct(_this);
		}
	}
}
/*****************************������ͽ*****************************/

void attempt_apprentice(object ob)
{
	if(_index == 1 || ob->query("family/family_name") != "��˿��") {
		command("shake");
	} else {
		if(ob->query("daoxing") < 400*K) {
			command("say �������ǳ�������ڼ�������");
		} else {
			command("pat " + ob->query("id"));
			command("say �ã��ӽ�������͸������ˡ�");
			command("recruit " + ob->query("id") );
		}
	}
}

int recruit_apprentice(object ob)
{
	if(::recruit_apprentice(ob)) ob->set("class", "yaomo");
}

string ask_for_leave()
{
	if(_index == 0 && _player->query("family/family_name") == "��˿��") {
		_player->set_temp("betray_psd", 1);
		return "�㵱��Ҫ�뿪��˿����";
	}
	return "����������������ȥ��\n";
}

int do_agree(string arg)
{
	if(_index == 0 && _player->query("family/family_name") == "��˿��"
		&& _player->query_temp("betray_psd"))
	{
		msv("$N������ǡ�\n\n", _player);

		command("say ȥҲ����ȥ��סҲ���ס�����仨������ʱ��������������");
		command("sign");
		command("say ȥ��...");
		_player->delete_skill("pansi-dafa");
		_player->add("betray/count", 1);
		_player->add("betray/psd", 1);

		_player->delete("family");
		_player->delete("class");
		_player->set("title", "��ͨ����");
		_player->set_temp("betray_psd", 0);
		_player->save();
		return 1;
	}
	return 0;
}

/*****************************�Ĵ�����*****************************/

string* rooms = ({
	"/d/westway/yinma",
	"/d/dntg/hgs/houshan1",
	X_DIR"d/psd/pool",
});

void debut()
{
	_this->move(random1(rooms));
}

