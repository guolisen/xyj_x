

#include <ansi.h>

inherit NPC;

#define DNTG11	"dntg11"	//dtng 11�ر��

int work_me();

void create()
{
	set_name("������", ({ "rulai fo", "rulai", "fo" }));
	set("title", "������Ӱ�٤��");
	set("long", "��ȴ���ɽ������ɲ������Ӱ�٤��������ү��\n");
	set("gender", "����");
	set("age", 10000);
	set("attitude", "peaceful");
	set("rank_info/self", "ƶɮ");
	set("rank_info/respect", "����үү");
	//set("class", "bonze");
	set("str",100);
	set("per",100);
	set("max_kee", 10000);
	set("max_gin", 10000);
	set("max_sen", 10000);
	set("force", 10000);
	set("max_force", 10000);
	set("force_factor", 500);
	set("max_mana", 10000);
	set("mana", 10000);
	set("mana_factor", 500);
	set("combat_exp", 4000000);
	set("daoxing", 10000000);

	set_skill("literate", 300);
	set_skill("spells", 300);
	set_skill("buddhism", 300);
	set_skill("unarmed", 300);
	set_skill("jienan-zhi", 300);
	set_skill("dodge", 300);
	set_skill("lotusmove", 300);
	set_skill("parry", 300);
	set_skill("force", 300);
	set_skill("lotusforce", 300);
	set_skill("staff", 300);
	set_skill("lunhui-zhang", 300);
	map_skill("spells", "buddhism");
	map_skill("unarmed", "jienan-zhi");
	map_skill("dodge", "lotusmove");
	map_skill("force", "lotusforce");
	map_skill("parry", "lunhui-zhang");
	map_skill("staff", "lunhui-zhang");
	set("chat_chance_combat", 80);
	set("chat_msg_combat", ({
		(: cast_spell, "bighammer" :),
	}) );

	set("inquiry", ([
		"�칬"			: (: work_me :),
		"���"			: (: work_me :),
		"�ʵ�"			: (: work_me :),
		"��λ"			: (: work_me :),
	]) );

	setup();
	carry_object("/d/obj/cloth/jia_sha")->wear();
}

void init()
{
	add_action("do_say", "say");
}

int work_me()
{
	object me = this_object();
	object who = this_player();

	object shanding = load_object(__DIR__"shanding");

	//todo:�������
	if( who->query("combat_exp") < 300000 ) {
		message_vision("$N��$n˵�������������㡣\n", me, who);
		return 1;
	}
	if(shanding->query("short") != "��������ɽ����") {	//ɽ�Ѿ�����
		message_vision("$N��$n˵�����԰����ꡣ\n", me, who);
		return 1;
	}

	message_vision(CYN"$N��$n˵�������������۰��ȥ�����칬��������\n"NOR, me, who);
	who->set_temp("dadu/stage", ({1, ({"��", "��", "����"})}));
	return 1;
}

int say(object who, string msg)
{
	message_vision(CYN"$N˵����" + msg + "\n"NOR, who);
}

int do_say(string arg)
{
	object me = this_object();
	object who = this_player();
	mixed* stage = who->query_temp("dadu/stage");
	int answer_ok = 0;

	if(!arg || !stage) return 0;

	//�ж�ʱ����ȷ�Ļش���ָ���Ĺؼ���
	foreach(string word in stage[1]) {
		if(strsrch(arg, word) >= 0) answer_ok = 1;
	}
	if(!answer_ok) return 0;
	if(wizardp(who)) printf("[bebug]:stage[0]:%d\n", stage[0]);

	switch(stage[0]) {
	case 1:		
		say(who, "�ԣ��ʵ������������굽�Ҽҡ��������ã���Ҫ���ң�������ƽ��");
		say(me, "����������仯֮�������к��ܣ���ռ�칬ʤ����");
		who->set_temp("dadu/stage", ({2, ({"�ֶ�", "ʮ��", "��ǧ", "����"})}));
		break;
	case 2:
		say(who, "�ҵ��ֶ����࣬һ�ݾ���ʮ���ǧ������������λ��");
		me->command("shake");
		say(me, "�������������������б��´���������ƣ�����Ӯ������ó��칬��");
		say(me, "�����ܴ�����ƣ��㻹�½�Ϊ�������޼��٣�ȴ��������");
		who->set_temp("dadu/stage", ({3, ({"��"})}));
		break;
	case 3:
		say(who, "�ã�");
		message_vision("$n˵����������$N���ģ�������ȥҲ��һ·�ƹ⣬��Ӱ����ȥ�ˡ�\n", me, who);		
		who->set_temp("dadu/stage", ({4, ({"�쾡ͷ", "��", "�Ǻ�"})}));
		who->move(__DIR__"finger");
		break;
	case 4:
		say(who, "����ȥ���쾡ͷ�����˼Ǻţ��ٽ�������칬���ң�");
		say(me, "������򾫣���ֻ�Ե�ͷ������");
		message_vision(CYN"$N������֣���ָд�š������ʥ������һ�Ρ���ָѾ�ﻹ����������\n"NOR, me, who);
		say(who, "������£�������£��Ҿ����ţ����ţ�������ȥ����");
		message_vision(HIR"$n�������ɣ�$N����һ���Ƴ��������⣬��ָ��������ɽ����ѹס��\n"NOR, me, who);
		who->set(DNTG11, "done");		//todo:��ǵ�ʮһ����ɣ���ʮ���ؿ�ʼ
		who->delete_temp("dadu");		
		who->move(__DIR__"shandi");		
		break;
	}		
	return 1;
}
