
#include <skill.h>

//读任何书都会，增加读书识字，练武也可增加武学

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object env = environment(me);
	object book;
	mapping prop;
	int cost, skill, exp;

	if(env->query("no_fight") || env->query("no_magic") )
		return notify_fail("这里不是读书的地方。\n");
	if(me->is_fighting() || me->is_busy())
		return notify_fail("你现在正忙着呢。\n");
	if(!arg || !objectp(book = present(arg, me)))
		return notify_fail("你要读什么？\n");
	if(!mapp(prop = book->query("skill")))
		return notify_fail("你无法从这样东西学到任何东西。\n");
	if(!me->query_skill("literate", 1))
		return notify_fail("你是个文盲，先学学读书识字(literate)吧。\n");

	message_vision("$N正专心地研读$n", me, book);

	skill = me->query_skill(prop["name"], 1);
	
	exp = skill * skill /10 * skill;
	if(SKILL_D(prop["name"])->type() == "martial") {
		if(exp > me->query("combat_exp")) {
			write("你的武学修为还没到这个境界，光读是没用的。\n");
			return 1;
		}
	}
	else if(SKILL_D(prop["name"])->type()=="magic" ) {
		if(exp > me->query("daoxing")) {
			write("你的道行还没到这个境界，光读是没用的。\n");
			return 1;
		}
	}
	
	if(!SKILL_D(prop["name"])->valid_learn(me))
		return notify_fail("以你目前的能力，还没有办法学这个技能。\n");;

	cost = prop["sen_cost"] + prop["sen_cost"] * (prop["difficulty"] - me->query_int()) / 20;

	if (cost < 5) cost = 5;
	cost *= 2;                                                                      //firefox 2011.10

	if(me->query("sen") < cost) {
		write("你现在过于疲倦，无法专心下来研读新知。\n");
		return 1;
	}
	if(me->query_skill(prop["name"], 1) > prop["max_skill"]) {
		write("你研读了一会儿，但是发现上面所说的对你而言都太浅了，没有学到任何东西。\n");
		return 1;
	}

	me->receive_damage("sen", cost);

	if(!me->query_skill(prop["name"], 1)) me->set_skill(prop["name"], 0);
	me->improve_skill(prop["name"], me->query_skill("literate", 1) * 2 + 1);           //firefox 2011.10
	write("你研读有关" + to_chinese(prop["name"]) + "的技巧，似乎有点心得。\n");
	return 1;
}

int help(object me)
{
	write( @HELP
指令格式: study|du <物品名称>

这个指令使你可以从秘笈或其他物品自学某些技巧,
但前提是: 你不能是个『文盲』。

see also : learn
HELP
	);
	return 1;
}


