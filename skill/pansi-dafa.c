// by firefox 03/16/2010

#define NAME		"盘丝大法"

inherit SKILL;

int valid_enable(string usage) { return usage=="spells"; }

int valid_learn(object me)
{
	if(me->query("family/family_name") != "盘丝洞") 
		return notify_fail(NAME"太过深奥，非盘丝中人无法理解。\n");
	
	if(me->query_skill("spells", 1) < 10)
		return notify_fail("你的法术修为还不够高深，无法学习"NAME"。\n");
	return 1;
}

string cast_spell_file(string spell)
{
	return CLASS_D("yaomo") + "/pansidong/pansi-dafa/" + spell;
}

string type() { return "magic";}

void random_level_up(object who)
{
	int lvl = who->query_skill("pansi-dafa", 1);
	//你求学之心不专，无法更深入的理解
	if(who->query("betray/count")) return;

	if(!random(lvl * 2)) who->improve_skill("pansi-dafa", 1);
}

