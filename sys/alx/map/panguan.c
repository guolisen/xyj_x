// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit NPC;
inherit F_GREET;

void create()
{
	set_name(HIW"����"NOR, ({"cui jue", "cui"}));
	set("title", HIW"����й�"NOR);
	set("gender", "����");
	set("long", "���й�ԭ������Ϊ�٣��������£����󱻷�Ϊ�����й١�\n");
	set("age", 30);

	setup();

	carry_object("/d/obj/cloth/choupao")->wear();
	carry_object("/d/obj/weapon/sword/panguanbi")->wield();
}

void init()
{
	string msg = HIW"\n���й���$n�����֣�˵���������ģ���Ī���ܣ��������������Һ����㻹����\n\n"NOR;
	::init();
	greet(_this, _player, msg);
}
