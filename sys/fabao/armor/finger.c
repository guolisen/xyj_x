
#include <armor.h>

inherit FINGER;

/*

�ݾ�cu�� ju��
�����۶ϰ�ָ����������Ʒ��

  ���sh�� ju��
���������s���׳ư�ָ���ָ��

*/

void create()
{
	set_name("���ָ", ({ "jin jiezhi", "jiezhi", "ring" }));
	set("weight", 400);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("value", 2000);
		set("material", "gold");
		set("armor_prop/armor", 1);
	}
	setup();
}	
