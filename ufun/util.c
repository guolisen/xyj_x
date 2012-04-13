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