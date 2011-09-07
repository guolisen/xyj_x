// by firefox 04/10/2010

#include <xyj_x.h>

inherit NPC;

int qj_start();

void create()
{
	set_name("唐太宗", ({"tang taizong", "tang", "tai zong", "zong", "king", "emperor"}));
	set("long", "大唐国之皇帝唐太宗。\n");
	set("title", "大唐国");
	set("gender", "男性");
	set("rank_info/respect", "陛下");
	set("age", 60);
	set("per", 30);

	set("force", 800);
	set("max_force", 800);
	set("combat_exp", 220*K);

	set_weight(5000*K); 

	set("inquiry", ([
		"取经"		: (: qj_start :),
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


//启动取经的代码，qujingstart这个标志欠规范
int qj_start()
{
	object who = this_player();

	if (who->query("qujingstart")) {
		tell_object (who,"\n唐太宗说道：朕已准你西天取经，请御弟一路保重！\n");
		return 1;
	}
	if ( who->query("dntg/wuxingshan") != "done") {
		tell_object (who,"\n唐太宗说道：西天路途遥远，朕怕你难当此任！\n");
		return 1;
	}

	who->delete("obstacle");
	who->set("qujingstart",1);
	tell_object (who,"\n唐太宗大喜道：难得你有如此决心，朕封你为御弟，望御弟早日上路，为我大唐求取真经！\n");
	return 1;
}
