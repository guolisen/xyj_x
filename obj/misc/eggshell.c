// by firefox 02/21/2010

inherit ITEM;

void create()
{
	set_name("����", ({ "dan ke", "ke", "shell" }) );
	set_weight(500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "һֻ����ĵ��ǡ�\n");
		set("unit", "ֻ");
	}

	setup();
}
