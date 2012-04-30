// by firefox 11/21/2009

inherit NPC;

#include <xyj_x.h>
#include <ansi.h>

int do_sth();

void create()
{
	set_name("孙悟空", ({ "sun wukong", "sun", "wukong" }));
	set("title", HIR"齐天大圣"NOR);
	set("gender", "男性");
	set("age", 23);

	set("per", 15);
	set("str", 500);
	set("spi", 300);
	set("cps", 100);

	set("combat_exp", 5000*K);
	set("daoxing", 5000*K);

	set("chat_chance", 10);
	set("chat_msg", ({ 
		CYN"孙悟空漫不经心地吃着香蕉。\n"NOR,
		(: random_move :),
		(: do_sth :), 
	}) );

	SKI->set_list(this_object(), ({
		({ "literate",		60,		"stealing",	180 }),
		({ "qianjun-bang",	600,	"stick",	600,	"parry",		180 }),
		({ "dao",			200,	"spells",	200 }),
		({ "wuxiangforce",	400,	"force",	400 }),
		({ "jindouyun",		300,	"dodge",	180 }),
	}));

	HP->to_max(_this);

	set("chat_chance_combat", 80);
	set("chat_msg_combat", ({
        (: perform_action,	"stick",	"qiankun" :),
		(: perform_action,	"stick",	"qiankun" :),		
		(: perform_action,	"stick",	"pili" :),
		(: perform_action,	"stick",	"pili" :),
        (: cast_spell,		"dingshen" :),
		(: cast_spell,		"fenshen" :),
	}) );

	setup();

	carry_object(__DIR__"equ/wk-boots")->wear();	//步云履
	carry_object(__DIR__"equ/wk-waist")->wear();	//蓝田带
	carry_object(__DIR__"equ/wk-cloth")->wear();	//赭黄袍
	carry_object(__DIR__"equ/wk-armor")->wear();	//金甲圣衣
	carry_object(__DIR__"equ/wk-bonnet")->wear();	//紫金冠
	carry_object(__DIR__"equ/wk-stick")->wield();	//如意金箍棒
}

//鬼混于牛夫人，香香，(此时和白晶晶分手了)
int do_sth()
{
	string* arr0 = ({
		"$N道：长夜漫漫无心睡眠，我以为只有我睡不着觉，原来$n也睡不着啊！",
		"$N对$n说：我不怕别人怎么说，千万人唾骂我一个人承担下来！",
		"$N用极其肉麻的声音对$n说道：小甜～甜～。",		
		"$N搂着$n说：今晚我们一起去看月亮！",

		"$n对$N说道：你这没良心的臭猴子！",
		"$n在$N屁股上狠狠的在拧了一把。",
	});
	string* arr1 = ({
		"$n对$N说：啊？你叫我大嫂？",
	});
	string* arr2 = ({
		"$N对$n说道：过一段时间我来娶你。",
	});

	object env = environment(_this);
	object ob = present("tieshan gongzhu", env);
	string* msgs = arr0 + arr1;

	if(!ob) {
		ob = present("xiang xiang", env);
		msgs = arr0 + arr2;
	}
	if(ob) msv(CYN + random1(msgs) + NOR"\n", _this, ob);
}

void die ()
{
	msv(CYN"$N从脑后拔出一根"HIY"救命毫毛"NOR CYN"念动咒语，一道光芒笼罩全身！\n"NOR, _this);
	HP->full(_this);
}

void unconcious()
{
	die();
}

/*****************************四处游走*****************************/

string* rooms = ({
	"/d/qujing/firemount/dongnei",
	"/d/qujing/jilei/woshi",
	"/d/dntg/hgs/up1",
	"/d/dntg/hgs/pubu",
});

void debut()
{
	_this->move(random1(rooms));
}

