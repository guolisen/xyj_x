// by firefox 11/21/2009

inherit NPC;

#include <xyj_x.h>
#include <ansi.h>

int do_sth();

void create()
{
	set_name("�����", ({ "sun wukong", "sun", "wukong" }));
	set("title", HIR"�����ʥ"NOR);
	set("gender", "����");
	set("age", 23);

	set("per", 15);
	set("str", 500);
	set("spi", 300);
	set("cps", 100);

	set("combat_exp", 5000*K);
	set("daoxing", 5000*K);

	set("chat_chance", 10);
	set("chat_msg", ({ 
		CYN"������������ĵس����㽶��\n"NOR,
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

	carry_object(__DIR__"equ/wk-boots")->wear();	//������
	carry_object(__DIR__"equ/wk-waist")->wear();	//�����
	carry_object(__DIR__"equ/wk-cloth")->wear();	//������
	carry_object(__DIR__"equ/wk-armor")->wear();	//���ʥ��
	carry_object(__DIR__"equ/wk-bonnet")->wear();	//�Ͻ��
	carry_object(__DIR__"equ/wk-stick")->wield();	//����𹿰�
}

//�����ţ���ˣ����㣬(��ʱ�Ͱ׾���������)
int do_sth()
{
	string* arr0 = ({
		"$N������ҹ��������˯�ߣ�����Ϊֻ����˯���ž���ԭ��$nҲ˯���Ű���",
		"$N��$n˵���Ҳ��±�����ô˵��ǧ����������һ���˳е�������",
		"$N�ü��������������$n˵����С���𡫡�",		
		"$N§��$n˵����������һ��ȥ��������",

		"$n��$N˵��������û���ĵĳ����ӣ�",
		"$n��$Nƨ���Ϻݺݵ���š��һ�ѡ�",
	});
	string* arr1 = ({
		"$n��$N˵����������Ҵ�ɩ��",
	});
	string* arr2 = ({
		"$N��$n˵������һ��ʱ������Ȣ�㡣",
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
	msv(CYN"$N���Ժ�γ�һ��"HIY"������ë"NOR CYN"����һ����â����ȫ��\n"NOR, _this);
	HP->full(_this);
}

void unconcious()
{
	die();
}

/*****************************�Ĵ�����*****************************/

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

