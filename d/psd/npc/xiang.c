// by firefox 11/21/2009

inherit NPC;

#include <xyj_x.h>

void create()
{
	set_name("����", ({ "xiang xiang", "xiang" }));
	set("long", "\nţħ�������ã�������Ⱥ��\n");

	create_family("���ƶ�", 2, "����");
	set("title", "���ƹ���");

	set("gender", "Ů��");
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


/*****************************������ͽ*****************************/

void attempt_apprentice(object ob)
{
	if(ob->query("family/family_name") != "���ƶ�") {
		command("shake");
	} else {
		if(ob->query("daoxing") < 300000) {
			command("say �������ǳ�������ڼ�������\n");
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
                ob->set("title", "����ɽĦ�ƶ�С��");
        }
}

/*****************************�Ĵ�����*****************************/

string* rooms = ({
	"/d/qujing/firemount/dongnei",
	"/d/dntg/hgs/up1",
	"/d/dntg/hgs/pubu",
});

void debut()
{
	_this->move(random1(rooms));
}