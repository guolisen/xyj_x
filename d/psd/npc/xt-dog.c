// by firefox 03/21/2009

inherit NPC;

#include <xyj_x.h>
#include <ansi.h>

void create()
{
	set_name("啸天犬", ({ "xiaotian quan", "quan" }) );
	set("race", "野兽");
	set("age", 3);
	set("long", "一只长得很吓人的恶狗。吐着舌头，留着口水。\n");
	
	set("per", 100);
	set("str", 200);
	set("dex", 36);
	set("gender", "雄性");

	set("combat_exp", 1000*K);
	set("daoxing", 1000*K);

	set("limbs", ({ "头部", "身体", "前脚", "后脚", "尾巴" }) );
	set("verbs", ({ "bite", "claw" }) );

	set("chat_chance", 6);
	set("chat_msg", ({
		CYN"啸天犬警觉的抬起头。\n"NOR,
	}) );
		
	set_temp("apply/attack", 300);
	set_temp("apply/armor", 300);

	setup();
}


void die()
{
	if(environment()) message_vision(CYN"\n\n$N惨叫一声，夹着尾巴跑掉了。\n\n"NOR, _this);
	destruct(this_object());
}

/*****************************四处游走*****************************/

int mount_dog()
{
	object me = this_object();
	string* arr = ({
		"/d/ourhome/npc/dog",
		"/d/city/npc/dog",
		"/d/lingtai/npc/oldwolf",
	});
	string str = random1(arr);
	object* dogs = children(str);

	if(sizeof(dogs)) {
		object dog = random1(dogs);
		object env = environment(dog);
		if(env && me->move(env)) {
			dog->set_temp("ride_msg", "骑");
			dog->set_temp("ride_prop/dodge", 1);
			dog->set("gender", "雌性");
			me->command("mount " + dog->query("id"));
		}
	}
	return 1;
}

void debut()
{
	mount_dog();
}