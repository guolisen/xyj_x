// firefox 2011.11
// ȭ��

#include <weapon.h>

inherit KNUCKLES;

void create()
{
	set_name("ȭ��", ({"quan li", "knuckles"}));
	set_weight(500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long","ȭ���ϰ�װ�����У�ʼ�ڴ�����ȭ�̡�ȭ����ȭ�С�\n");
		set("unit", "��");
		set("value", 1000);
	}
	init_knuckles(26, EDGED);
	setup();
}

