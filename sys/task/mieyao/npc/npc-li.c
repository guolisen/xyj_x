// by firefox 04/20/2010

#include <xyj_x.h>

inherit EMPLOYER;

void create()
{
	set_name("�", ({ "li jing", "jing", "li" }) );
	set("gender", "����" );
	set("long", "�����������������Ԫ˧������ʮ������콫�������ޱߡ�\n");	
	set("title", "��������");
	set("age",40);
	set("str", 40);

	set("chat_chance", 1);
	set("chat_msg", ({ name() + "˵������λ���ɿ�Ըȥ�½�������\n",}) );

	seteuid(getuid());
	FAMILY->quick_setup(_this, "����ɽ���Ƕ�", 180);

	set_task(TASK_GET("mieyao", "mieyao"),
		({"mieyao", "kill", "����"}),
		([
			"task"		: "$N���������������½�һ�Σ�\n"
				+ "$N��$n˵��������%s��%sΪ������������ȥ������\n",
			"repeat"	: "$N˵�����Ϸ�������ȥ����%s��\n",
			"cd"		: "$N������������һ����˵����λ$r,��ħ�ѳ���,������ȥЪϢ��\n",
		])
	);

	setup();
	carry_object("/d/obj/fabao/huangjin-baota");
	carry_object("/d/obj/armor/jinjia")->wear();
	carry_object("/d/sky/obj/zhanyaojian")->wield();
}

