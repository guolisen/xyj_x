// by firefox 04/20/2010

#include <xyj_x.h>

inherit EMPLOYER;

void create()
{
	set_name("Ԭ���", ({"yuan tiangang", "yuan"}));
	set("gender", "����" );
	set("age", 33);
	set("long","

Ԭ��������̨�ܹܣ���˵���������
��Ϊ����ֱ���壬��������һ���ǹ���������顣

");
	set("int", 30);
	set("per", 25);
	set("combat_exp", 50*K);
	set("daoxing", 800*K);

	// discourage NK yuan.
	set("eff_dx",1000);
	set("nkgain",1);
	set("env/wimpy",100);

	set("title", "���̨������");

	set("max_kee", 400);
	set("max_sen", 400);
	set("force", 450);
	set("max_force", 300);
	set("force_factor", 10);
	set("mana", 6000);
	set("max_mana", 3000);
	set("mana_factor", 100);

	SKI->set_list(this_object(), ({
		({ "literate",		50, }),
		({ "sword",			60 }),
		({ "force",			50 }),
		({ "dodge",			50 }),
		({ "changquan",		50,		"unarmed",	60 }),
		({ "baguazhou",		100,	"spells",	100 }), })
	);

	set("chat_msg", ({
		name() + "̾����������������ħ���а���\n",
		name() + "�ʵ�������˭ԸȥΪ����������\n",})
	);

	set_task(TASK_GET("mieyao", "mieyao"),
		({"mieyao", "kill", "����", "��ħ"}),
		([
			"task"		: "$N��������ľ�����ķ�һ������$n˵����\n"
				+ "��������%s��%s��û��Ϊ����С������ȥ�շ���\n",
			"repeat"	: "$N˵�������²�������ȥ�շ�%s��\n",
			"cd"		: "$N��������ľ���������£�˵����л$r,��ħ�Ѿ������ˡ�\n",
		])
	);

	setup();

	add_money("silver", 5);
	carry_object("/d/obj/cloth/baguapao")->wear();
	carry_object("/d/obj/weapon/sword/taomujian")->wield();
}

int accept_fight(object me)
{
	write("Ԭ�����Ȼ����ѧ������Ϊ��ǿ�����Ǵ��ɱɱ��\n");
	return 0;
}

int recognize_apprentice(object me)
{
	if((int)me->query("yuan-learn"))
		return 1;
	return notify_fail("Ԭ���˵������̫�����ˣ�����ô�ҵ���\n");
}

int accept_object(object who,object ob)
{
	if (ob->query("id")=="fan he"){
		if (((string)who->query("family/family_name")=="������")){
			who->set("yuan-learn", 1);
			write("Ԭ���Ц��������������һ���˲ţ��Ժ�����ǰ��ͷ֮����
				Ԭ�����Ϊ��˼���ֵ����������к����⣬����ʱ�������֣��������֪��������𸴣�\n");
				call_out("destroy", 1, ob);
			return 1;
		}
		if (((string)who->query("family/family_name")!="������")){
			command("say ��л��л�����������ģ�");
			command("give 1 silver to " + who->query("id"));                        
			call_out("destroy", 1, ob);
			return 1;
		}
	}
	else return 0;
}

void destroy(object ob)
{
	destruct(ob);
	return;
}

