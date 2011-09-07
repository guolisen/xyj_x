// by firefox 11/21/2009

inherit NPC;

#include <xyj_x.h>

void create()
{
	set_name("香香", ({ "xiang xiang", "xiang" }));
	set("long", "\n牛魔王的妹妹，法力超群。\n");

	create_family("火云洞", 2, "弟子");
	set("title", "火云公主");

	set("gender", "女性");
	set("age", 18);
	set("per", 16);
	set("str", 30);
	set("con", 200);
	set("spi", 300);

	set("combat_exp", 1000*K);
	set("daoxing", 2000*K);

	SKI->set_list(this_object(), ({
		({ "literate",		30, }),
		({ "moyun-shou",	200,	"unarmed",	180 }),
		({ "pingtian-dafa",	200,	"spells",	200 }),
		({ "huomoforce",	120,	"force",	120 }),
		({ "moshenbu",		120,	"dodge",	120 }),
	}));

	HP->to_max(_this);

	setup();
	carry_object("/d/moon/obj/luoyi")->wear();
}


/*****************************开门收徒*****************************/

void attempt_apprentice(object ob)
{
	if(ob->query("family/family_name") != "火云洞") {
		command("shake");
	} else {
		if(ob->query("daoxing") < 300000) {
			command("say 你道行尚浅，还需勤加修炼。\n");
		} else {
			command("nod");
			command("recruit " + ob->query("id") );
		}
	}
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) ) {
                ob->set("class", "yaomo");
                ob->set("title", "积雷山摩云洞小妖");
        }
}

/*****************************四处游走*****************************/

string* rooms = ({
	"/d/qujing/firemount/dongnei",
	"/d/dntg/hgs/up1",
	"/d/dntg/hgs/pubu",
});

void debut()
{
	_this->move(random1(rooms));
}