// by firefox 06/21/2010

#include <xyj_x.h>
#include <ansi.h>

inherit EMPLOYER;

void create()
{
	set_name("�ȶ���ʦ", ({"cien fashi", "cien", "fashi"}) );
	set("title", "����");
	set("gender", "����");
	set("age", 50);
	set("long","

������ʦ���׳ƴȶ���ʦ��ξ�پ���ֶ֮�����ʷ�������֮ͽ����ʮ��
������뾭����ס�ȶ��£��󴴡������ڡ���Ҳ�ơ��ȶ��ڡ���

");
	set("daoxing", 50000);
	set("str", 30);
	set("per", 30);
	set("int", 30);

	set("inquiry", ([
		"name" : "��������������֣����ſ��������˳����ҡ��ȶ���ʦ����\n",
	]) );
	
	set("chat_msg", ({
		name() + "̾�����澭���в��𣬲��Ҷ���ȡ�壬������Ǻã�\n",
		name() + "̾�����������ܰ�����Ѱ�澭��Ƭ���Բ�ȫ�澭������ǹ���������\n",
		name() + "˵���������������ֲ�ȫ�澭����������\n" })
	);

	set("rank_info/self", "����");

	set_task(TASK_GET("forces", "cien"),
		({"task"}),
		([
			"task"		: "$N��$n˵������λ$r�ɷ�ȥ������Ѱ��%s��\n",
			"repeat"	: "$N˵�������Ĳ�������ȥѰ��%s��\n",
			"done"		: "$N��$n˵������л��λ$r�����Ϳ�Ѱ��%s�����ĸм�������\n",
			"name_err"	: "$N��$n˵������λ$r��$S��ȱ%s������%s���������ٽ�������\n",
			"id_err"	: "$N��$n˵������λ$r��$S��ȱ%s(%s)�����Ǵ���(%s)��\n",
		])
	);
	
	setup();
	carry_object("/d/obj/cloth/sengyi")->wear();
}

void init()
{
	::init();
	add_action("do_answer", "answer");
}


int do_answer(string arg)
{
	return _task->answer(_this, _player, arg);
}
