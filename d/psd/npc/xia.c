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
	({ "紫霞", ({ "zi xia", "zixia", "zi", "xia" }),		"盘丝大仙"}),
	({ "青霞", ({ "qing xia", "qingxia", "qing", "xia" }),	"佛祖灯芯" }),
});

int do_sth();
string ask_for_leave();

//获取当前ID
string the_id()
{
	_index = at_night();
	if(_dying) _index = 0;	//禁止紫霞在交代遗言时变成青霞

	set_name(_tab[_index][0], _tab[_index][1]);
	set("title", _tab[_index][2]);
	return query("id");
}

void create()
{
	the_id();
	
	set("long", @LONG

俊俏的脸庞，幽怨的眼神，让人难忘。

LONG
	);
	set("title", "盘丝大仙");
	set("gender", "女性");
	set("age", 20);
	
	set("per", 30);
	set("str", 10);
	set("con", 500);
	set("spi", 500);
	set("cps", 60);

	create_family("盘丝洞", 1, "祖师");

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
		//银索金玲
	}) );*/

	set("inquiry", ([
		"脱离" : (: ask_for_leave :),
		"leave" : (: ask_for_leave :),
	]) );

	setup();

	carry_object("/d/moon/obj/luoyi")->wear();
	carry_object(__DIR__"equ/zq-sword")->wield();

	//FABAO_D->carry(_this, "hand-bell")->wear();
	//RACE_D->set(_this, "human", "灯芯", 10);
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
			"$N说道：我的意中人是个盖世英雄...",
			"$N说道：我知道有一天他会在一个万众瞩目的情况下出现...",
			"$N说道：身披金甲圣衣， 脚踏七色云彩来娶我...",

			"$N手托香腮，目视前方，会心的笑了。看来又在做白日梦了。",
		}),
		({
			"$N面无表情，冷若冰霜。",
			"$N说道：贱人!",
		}),
	});
	string str = CYN + random1(arr[_index]) + "\n"NOR;
	msv(str, _this);
}

/*****************************香消玉殒*****************************/

void dying(object killer, object wukong)
{
	msv(CYN
		"突然间风起云涌，$N翻下云头，抱起奄奄一息的$n，失声惊呼。\n"
		"$n说道：我的意中人是个盖世英雄...我猜中了前头，可是我猜不着这结局...\n", wukong, _this
	);

	shout(HIW + wukong->name() + "一声哀嚎，响彻云霄。\n"NOR);
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
		if(_env) msv(HIC"\n\n只见$N化作一道青光，消失无踪。\n\n"NOR, _this);
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
			if(_env) msv(HIC"\n\n只见$N化作一道紫光，消失无踪。\n\n"NOR, _this);
			destruct(_this);
		}
	}
}
/*****************************开门收徒*****************************/

void attempt_apprentice(object ob)
{
	if(_index == 1 || ob->query("family/family_name") != "盘丝洞") {
		command("shake");
	} else {
		if(ob->query("daoxing") < 400*K) {
			command("say 你道行尚浅，还需勤加修炼。");
		} else {
			command("pat " + ob->query("id"));
			command("say 好，从今往后你就跟着我了。");
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
	if(_index == 0 && _player->query("family/family_name") == "盘丝洞") {
		_player->set_temp("betray_psd", 1);
		return "你当真要离开盘丝洞？";
	}
	return "从哪里来，自哪里去。\n";
}

int do_agree(string arg)
{
	if(_index == 0 && _player->query("family/family_name") == "盘丝洞"
		&& _player->query_temp("betray_psd"))
	{
		msv("$N答道：是。\n\n", _player);

		command("say 去也终须去，住也如何住？花落花开自有时，总赖东君主。");
		command("sign");
		command("say 去吧...");
		_player->delete_skill("pansi-dafa");
		_player->add("betray/count", 1);
		_player->add("betray/psd", 1);

		_player->delete("family");
		_player->delete("class");
		_player->set("title", "普通百姓");
		_player->set_temp("betray_psd", 0);
		_player->save();
		return 1;
	}
	return 0;
}

/*****************************四处游走*****************************/

string* rooms = ({
	"/d/westway/yinma",
	"/d/dntg/hgs/houshan1",
	X_DIR"d/psd/pool",
});

void debut()
{
	_this->move(random1(rooms));
}

