//������ҵ�ƾ֤������ԭ����
#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(HIY"����������ӡ"NOR, ({"feng yin", "yin", "seal"}));
	set("weight", 5);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long","һ���ƾ���滭�Ű����̡�����������ܽޡ������������������ᣬһ��С�֣�Ǭ�������ɣ����������\n");
		set("unit", "��");
		set("no_get", 1);
		set("no_give", 1);
	}
	set("channel_id", "ȡ��ϵͳ");
	setup();
}

