// by firefox 11/21/2009
// �����������ף��ܵ���������

#include <armor.h>
#include <ansi.h>
inherit ARMOR;

//��˿����
void create()
{
	set_name(HIY"���ۻƽ�ϸ��"NOR, ({ "dragon armor", "armor"}));
	set_weight(1);

	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "һ����ӲӵĿ��ף�\n");

		set("material", "iron");
		set("armor_prop/armor", 1);
		set("armor_prop/dodge", 1);

		//set("no_get", 1);
	}
	setup();
}

