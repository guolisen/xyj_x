
// by firefox 04/16/2011

/********************************保障场景安全***********************************/

//死亡替代函数，用于避免玩家意外死亡
void alternative_die(object who)
{
	who->set("kee", 100);
	who->set("sen", 100);
	who->set("eff_kee", 100);
	who->set("eff_sen", 100);
}





//广播，用于看台玩家
void broadcast(string msg) 
{
	object room = load_object(__DIR__"stand");
	string prefix = HIY"【擂台】"NOR;
	string s1 = str, s2 = "", s3;
	int i;

	reset_eval_cost();

	// remove extra trailing NOR. mon 7/13/99
	s1=replace_string(s1,"\n"NOR,"\n");

	while (strsrch(s1,"\n\n") != -1)
		s1 = replace_string(s1,"\n\n","\n");

	while (sizeof(s1)>1 && s1[sizeof(s1)-1]=='\n')
	{
		s1 = s1[0..(sizeof(s1)-2)];
		s2 = "\n";
	}
	if (sizeof(s1) <= 1)
		return;

	s1 = replace_string(s1,"\n","\n"+prefix);

	tell_room (room, prefix+s1+ NOR+"\n");
}
