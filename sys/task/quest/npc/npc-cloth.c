// by firefox 04/20/2010

#include <xyj_x.h>

inherit EMPLOYER;

void create()
{
	set_name("����", ({"xiang lan", "xiang", "lan"}));
	set("gender", "Ů��");
	set("age", 28);
	set("per", 28);

	set("chat_msg",({
		"��������һЦ�������챦�ɲ��١�\n",
		"�������һЦ˵�����������˶�Ҳ��\n",
		"����˵�����۽磬��Ҳ��Ҳ��\n",
	}));

	set("inquiry", ([
		"here":   "���˸�����ͤ��Ҳ�������ڴ��ռ������챦��\n",
		"name":   "�߼�С������Ҳ��\n",
	]));

	set("rank_info/self", "����");

	set_task(TASK_GET("quest", "cloth"),
		({"cloth", "�챦", "ļ��", "��"}),
		([				
			"task"		:
				"$N��$nһЦ��$S����������Ҫ%s��\n"
				"��λ$r�ܷ���$S����취��\n",
			"repeat"	:
				"$N��$n˵������λ$r��$S����������%s�أ�\n",
			"done"		:
				"$N��$n˵������л��λ$r������Ѱ��%s��$S�ø����ģ�\n",
			"name_err"	:
				"$N��$n˵������λ$r��$S˵����Ҫ%s��������$S%s��������档\n",
			"id_err"	:
				"$N��$n˵������λ$r��$S����Ҫ%s��������ͦ�󣬵�����ͬһ������\n"
				"$SҪ����(%s)����������(%s)��\n",
		])
	);

	setup();

	carry_object("/d/obj/cloth/pinkskirt")->wear();
	carry_object("/d/obj/cloth/shoes")->wear();
}

