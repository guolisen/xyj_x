// by firefox 10/01/2010
// ����ɱ-����NPC

inherit NPC;

#include <xys.h>

int do_join();

void create()
{
	set_name("�������", ({"jiangzhu xianzi", "xianzi", "girl", }));
	set("long", @LONG

����������������ü��һ˫��ϲ��ϲ����Ŀ��̬������֮���Ϯһ
��֮��������㣬����΢΢���о�ʱ��毻���ˮ���ж�����������
�硣�Ľϱȸɶ�һ�ϣ���������ʤ���֡�

LONG);

	set("title", HIY"�þ�ʹ��"NOR);
	set("gender", "Ů��");
	set("age", 18);
	set("per", 30);

	set("inquiry", ([
		"���лþ�": (: do_join :),
	]));

	setup();
	carry_object("/d/moon/obj/luoyi")->wear();

}
int do_join()
{
	return XYS->do_join(_this, _player);
}

void die ()
{
	set("kee", 200);
	set("eff_kee", 200);
	set("sen", 200);
	set("eff_sen", 200);
}

void unconcious()
{
	die();
}
