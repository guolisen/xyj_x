#ifndef XSHA_LOCAL_H_INCLUDED
#define XSHA_LOCAL_H_INCLUDED
// by firefox 10/01/2010
// X-SHA���ػ��ļ�


/********************************��������***********************************/



/********************************��������***********************************/

//����������������ڱ��������������
void alternative_die(object who)
{
	who->set("kee", 100);
	who->set("sen", 100);
	who->set("eff_kee", 100);
	who->set("eff_sen", 100);
}

//���ð�ȫ�������ⷢ��ս��
int set_safety()
{
	set("no_fight", 1);
	set("no_cast", 1);

	set("alternative_die", 1);
}

//����ָ��
int do_block(string arg) 
{
	string* casts = ({"escape", "chuqiao", "tudun", "shuidun"});

    if(!arg) return 0;
    while(sscanf(arg, "%s %*s", arg) == 2);
    trace(arg);
    if(member_array(arg,banned_cast)==-1) return 0;
    return notify_ok("����ʹ��" + arg + ",��л������\n");
}

//�㲥�����ڿ�̨���
void broadcast(string msg) 
{
	object room = load_object(__DIR__"stand");
	string prefix = HIY"����̨��"NOR;
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
