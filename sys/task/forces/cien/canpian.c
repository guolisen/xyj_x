// by firefox 08/16/2010

#include <xyj_x.h>

inherit ITEM;
inherit F_LIFE;

//����ѡ�����ʵĴ�˾����֣������ٵ�
string* _names = ({
	"�����ؾ�",
	"�����ܾ�",
	"��ϣ�о�",
	"�����ʾ�",
	"���ޱȾ�",
	/*"�޹��ƾ�",
	"���¾�",
	"�������",
	"Ե��",
	"�����׾�",*/
});

void create()
{
	set_name(random1(_names) + "��Ƭ", ({"can pian", "pian", "debris"}));
		
	set("no_give", 1);

	if(clonep())
		set_default_object(__FILE__);
	else {
		set("long","һƬ���ĵĲ�Ƭ���ּ��Ѿ�ģ������������ˮ��\n");
		set("unit", "Ƭ");


		set("no_put", 1);
		set("no_drop", 1);
		set("no_stock", 1);
	}
	setup();

	set_heart_beat(30);
	life_start(600);
}


void heart_beat()
{
	life_check_end();
}

