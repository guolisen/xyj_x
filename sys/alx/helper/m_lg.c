// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"m_base";

void create()
{
	set_name("����", ({"ao guang", "ao","guang","longwang","wang"}));

	set("long", "/n�����Ƕ��������������ֱֵܷ��ƹܶ��������ϣ����ĺ���\n");
	set("gender", "����");
	set("age", 66);
	set("title", "��������");
	set("class","dragon");

	create_family("��������", 1, "ˮ��");

	SKI->set_list2(_this, FAMILY->skills_of("��������"), 1);

	set_events(
		([
			"born"		: HIW"һ�����������$N������������ǰ��",
			"leave"		: HIW"$N�Ľ���ͻȻӿ��һ��ˮ����ˮ������$N��֮�����ˣ�",
			"init"		: 0,
			"kill"		: "����Ǻ���Ĵ��ۣ�",

			"cmds"		: ({ "cast freez", "cast water" }),
		])
	);

	setup();

	carry_object("/d/sea/obj/longpao")->wear();
}
