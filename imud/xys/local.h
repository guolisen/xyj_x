#ifndef XSHA_LOCAL_H_INCLUDED
#define XSHA_LOCAL_H_INCLUDED
// by firefox 10/01/2010
// X-SHA本地化文件


/********************************常量定义***********************************/



/********************************函数定义***********************************/

//死亡替代函数，用于避免玩家意外死亡
void alternative_die(object who)
{
	who->set("kee", 100);
	who->set("sen", 100);
	who->set("eff_kee", 100);
	who->set("eff_sen", 100);
}

//设置安全区，避免发生战斗
int set_safety()
{
	set("no_fight", 1);
	set("no_cast", 1);

	set("alternative_die", 1);
}

//禁用指令
int do_block(string arg) 
{
	string* casts = ({"escape", "chuqiao", "tudun", "shuidun"});

    if(!arg) return 0;
    while(sscanf(arg, "%s %*s", arg) == 2);
    trace(arg);
    if(member_array(arg,banned_cast)==-1) return 0;
    return notify_ok("请勿使用" + arg + ",多谢合作。\n");
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
