// by shines 02/07/2010

inherit ITEM;

#include <ansi.h>

void create()
{
	set_name(HIY"���¾�"NOR, ({"huayue jing", "jing zi", "jing", "mirror"}));

	set("long", 
		"һ�滪����ͭ����������һ�¿���(kan)���ݡ��������У�\n\n"
		"    Ʃ�羵�л�������ˮ���£��˽��Ļû�������ʵ���ߡ�\n"
		"    ���������ߣ���֪��֮���Ĵ����ٺϣ�������Ů��\n"
		"    ��������𣬻���̰���֣��������Ե���˷���Ů����\n"
		"    ����Ϊ�ͺϣ�������ƻã���¶�ݵ��ƣ�Ӧ�����ǹۡ�\n\n"
		"���濴�ƹ����������� ����(Shines)��\n\n"
		);
	set("unit", "��");
	set("value", 50000);

	setup();
}

void init()
{
	add_action("do_zhao", ({"kan"}));
}

int do_zhao(string arg)
{
	object me = this_object();
	object who = this_player();
	mapping tab = ([
		"����"	: ({ "Ů��", "Ů��", "����" }),
		"Ů��"	: ({ "����", "����", "���" }),
	]);

	if(arg && (present(arg, who) == me)) {
		string* arr = tab[who->query("gender")];
		if(arr) {
			who->set("gender", arr[0]);
			write(HIC"�㷢��һ��" + arr[1] + "�����ھ������������һ����\n"NOR);
			who->command("wa1");
			write(HIC"������Ծ����ǣ�����������" + arr[2] + "��\n"NOR);

			if(!random(5)) {
				message_vision("$Nһʧ�֣�$n���ڵ���ˤ���ˣ��ƾ���Բ��\n", who, me);
				destruct(me);
			}
			return 1;
		}
	}
	return 0;
}
