// by firefox 14/06/2009 

#include <ansi.h>

inherit ITEM;

#define NAME	HIM"���"NOR
#define ID		"pan tao"

void create()
{
	set_name( NAME , ({ ID }));
	set_weight(90);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "\n"
			"����������㣬�����ɸ����س�����Ц����Դ���֣������츮����ǿ��\n"
			"���ƽ�������٣�罺�������Ī˫���������������壬��Եʳ���Էǳ���\n\n"
		);

		set("value", 100000);
		set("drug_type", "��Ʒ");
	}
	setup();
}

void init()
{
	add_action("do_eat", "eat");	
}

int do_eat(string arg)
{
	object who = this_player();
//��������
	
	message_vision(HIG"$N����һ��"NAME HIG"���پ���̥���ǡ�\n" NOR, who);

	
	destruct(this_object());
	return 1;
}
