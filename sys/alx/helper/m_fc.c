// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"m_base";


void create()
{
	set_name("��������", ({"master yunyang", "master", "yunyang"}));
	set("title", "С��ʦ");
	set("long", "����������������ʦʵ�ǰ�ʦ���ѣ�Ҳ�����Ƕ������ܹܡ�\n");
	set("gender", "����");
	set("age", 70);

	set("str", 30);

	create_family("����ɽ���Ƕ�", 2, "��");


	SKI->set_list2(_this, FAMILY->skills_of("����ɽ���Ƕ�"), 1);

	set_events(
		([
			"born"		: CYN"ֻ�����˺����η����������������ˣ�",
			"leave"		: CYN"$N̾��������һ�ߣ�ħ��һ�ɡ�˵�յ��ƶ�ȥ��",
	
			"cmds"		: ({ "cast dingshen", "cast light", "cast thunder", "cast fenshen" }),
		])
	);

	setup();

	carry_object("/d/lingtai/obj/xiangpao")->wear();
	carry_object("/d/lingtai/obj/bang")->wield();
}
