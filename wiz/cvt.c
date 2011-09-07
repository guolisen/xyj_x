
// by firefox 11/21/2009
// 旧数据转换器

void create()
{
	seteuid(getuid());
	set_heart_beat(1);
}


//灭妖，解谜，门忠，法宝，



#define LIT			"gift/literate"
//降低literate，返还潜能
int set_literate(int lvl)
{
	object who = this_player();

	int literate = who->query_skill("literate", 1);
	int pot = 0;

	if(who->query(LIT)) 
		return notify_fail("你已经变更过literate了。\n");

	if(lvl >= literate)
		return notify_fail("请设定比现在低的literate级别。\n");

	if(lvl < 20)
		return notify_fail("请设定比高于20的literate级别。\n");

	for(int i = lvl; i < literate; ++i) {
		int intelligence = who->query("int") + (i - 20) / 10;
		pot += (i + 1) * (i + 1) / intelligence * 2;
	}
	
	who->set(LIT, 1);
	who->add("learned_points", -pot);
	who->set_skill("literate", lvl);

	return notify_ok("你得到了" + pot + "点潜能。\n");

}

