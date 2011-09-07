// by firefox 04/10/2010

#include <xyj_x.h>

inherit NPC;

int qj_start();

void create()
{
	set_name("��̫��", ({"tang taizong", "tang", "tai zong", "zong", "king", "emperor"}));
	set("long", "���ƹ�֮�ʵ���̫�ڡ�\n");
	set("title", "���ƹ�");
	set("gender", "����");
	set("rank_info/respect", "����");
	set("age", 60);
	set("per", 30);

	set("force", 800);
	set("max_force", 800);
	set("combat_exp", 220*K);

	set_weight(5000*K); 

	set("inquiry", ([
		"ȡ��"		: (: qj_start :),
		"qujing"	: (: qj_start :),]) 
	);

	setup();

	carry_object("/d/obj/cloth/mangpao")->wear();
}

void init ()
{    
	call_out ("test_player", 1, _player);
	_player->start_busy(1);
}

void test_player (object who)
{
	TASK->child("quest")->pay(_this, who);
}


//����ȡ���Ĵ��룬qujingstart�����־Ƿ�淶
int qj_start()
{
	object who = this_player();

	if (who->query("qujingstart")) {
		tell_object (who,"\n��̫��˵��������׼������ȡ����������һ·���أ�\n");
		return 1;
	}
	if ( who->query("dntg/wuxingshan") != "done") {
		tell_object (who,"\n��̫��˵��������·;ңԶ���������ѵ����Σ�\n");
		return 1;
	}

	who->delete("obstacle");
	who->set("qujingstart",1);
	tell_object (who,"\n��̫�ڴ�ϲ�����ѵ�������˾��ģ��޷���Ϊ���ܣ�������������·��Ϊ�Ҵ�����ȡ�澭��\n");
	return 1;
}
