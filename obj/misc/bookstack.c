// by firefox 02/21/2010

inherit "/d/sldh2/feature/container";

void create()
{
	set_name("���", ({ "shu jia", "jia", "bookstack" }) );
	set_weight(500000);
	set_max_encumbrance(500000);
	set_max_items(20);

	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ�����Ĵ���ܣ������飬Ҳ�ɷ�һЩ���\n");
		set("value", 50);
		set("no_get", 1);
	}
	load_data();
}
