// by firefox 11/21/2009

#include <localtime.h>
#include <ansi.h>
#include <xyj_x.h>

/*****************************��������*****************************/

//������Ҷ��������wiz�ſ���ȫ�ֲ���
object find_player2(string id)
{
	if(!id || id == "me" || id == getuid(_player)) return _player;
	if(wizardp(_player)) return find_player(id);
	return 0;
}

//����id�������������������������/����/ȫ�ֲ������(wiz)
object search_id(object me, string id)
{
	object env = environment(me);
	object ob = me;		//���id�����ڣ���������me
	if(id) {
		ob = (id == "here") ? env : present(id, me);
		if(!ob) ob = present(id, env);
		if(!ob && wizardp(me)) ob = find_player(id);
	}
	return ob;
}

//�ӵ�ǰ����Ѱ��Ŀ��
object present_here(string id)
{
    object ob = this_player();
    if(ob) ob = environment(ob);
    if(ob && id) ob = present(id, ob);
    return ob;
}

//�����ֲ���
object present_name(string name, object env)
{
	if(!name || !env) return 0;
	foreach(object ob in all_inventory(env)) {
		if(ob->name() == name) return ob;
	}
    return 0;
}


//�����ֺ�ID����
object present2(string name, string id, object env)
{
	if(!name || !id || !env) return 0;
	foreach(object ob in all_inventory(env)) {
		if(ob->name() == name && ob->query("id") == id) return ob;
	}
    return 0;
}

/*****************************��������*****************************/

//Ų�߲�����
void move_destruct(object ob)
{
	if(ob) ob->move("/obj/empty");
	if(ob) destruct(ob);
}

private void destruct_ob(object ob)
{
	if(ob) destruct(ob);
}

//��ʱ���ٶ���
varargs void delay_destruct(object ob, int delay)
{
	if(delay < 1) delay = 1;	
	call_out("move_destruct", delay, ob);
}

/*****************************�ļ�����*****************************/

//��һ�ļ���������·��
string file_leaf(object ob)
{
	return path_file(base_name(ob));
}

//��һ�ļ���������·��
string file_dir(object ob)
{
	return path_dir(base_name(ob));
}


mixed test()
{
	string s = __FILE__;//"1234567";
	return s[0..<3];
}

/*****************************��˺���*****************************/

//����
varargs int dismount(object who, int silence)
{
	object ridee = who->query_temp("ridee");

	if(ridee) {
		if(!silence) msv("$Nͦ���$n��Ծ������\n", who, ridee);
		ridee->set_temp("no_return", 0);
		ridee->set_temp("rider", 0);
	}

	who->set_temp("ridee", 0);
	who->add_temp("apply/dodge", -who->query_temp("ride/dodge"));
	who->set_temp("ride/dodge", 0);
	return 1;
}

//����
varargs int mount(object who, object ridee, int silence)
{
	object where = environment(who);
	object r1 = who->query_temp("ridee");
	if(same_env(r1, who)) return 0;
	
	dismount(who, 1);	//������Ч���������

	if(!silence) 
		MSG->vision("$N������һ���������ȵ�%s��$n�ϣ�\n", who, ridee, ridee->query("ride/msg"));
	
	ridee->set_temp("no_return", 1);
	ridee->set_temp("rider", who);
  
	who->set_temp("ridee", ridee);
	ridee->move(where);
	who->set_temp("ride/dodge", ridee->query("ride/dodge"));
	who->add_temp("apply/dodge", ridee->query("ride/dodge"));
}

/*****************************��������*****************************/
//����
int today()
{
	return localtime(time())[LT_MDAY];
}

//����
string date()
{
	mixed* t = localtime(time());
	return sprintf("%02d-%02d-%02d", t[LT_YEAR], t[LT_MON] + 1, t[LT_MDAY]);
}

//ʱ��
string time1()
{
	mixed* t = localtime(time());
	return sprintf("%02d:%02d:%02d", t[LT_HOUR], t[LT_MIN], t[LT_SEC]);
}