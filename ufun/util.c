// by firefox 11/21/2009

#include <localtime.h>
#include <ansi.h>
#include <xyj_x.h>

/*****************************搜索函数*****************************/

//查找玩家对象，如果是wiz才可以全局查找
object find_player2(string id)
{
	if(!id || id == "me" || id == getuid(_player)) return _player;
	if(wizardp(_player)) return find_player(id);
	return 0;
}

//根据id搜索对象，依次搜索：玩家身上/环境/全局查找玩家(wiz)
object search_id(object me, string id)
{
	object env = environment(me);
	object ob = me;		//如果id不存在，则对象等于me
	if(id) {
		ob = (id == "here") ? env : present(id, me);
		if(!ob) ob = present(id, env);
		if(!ob && wizardp(me)) ob = find_player(id);
	}
	return ob;
}

//从当前环境寻找目标
object present_here(string id)
{
    object ob = this_player();
    if(ob) ob = environment(ob);
    if(ob && id) ob = present(id, ob);
    return ob;
}

//按名字查找
object present_name(string name, object env)
{
	if(!name || !env) return 0;
	foreach(object ob in all_inventory(env)) {
		if(ob->name() == name) return ob;
	}
    return 0;
}


//按名字和ID查找
object present2(string name, string id, object env)
{
	if(!name || !id || !env) return 0;
	foreach(object ob in all_inventory(env)) {
		if(ob->name() == name && ob->query("id") == id) return ob;
	}
    return 0;
}

/*****************************建立销毁*****************************/

//挪走并销毁
void move_destruct(object ob)
{
	if(ob) ob->move("/obj/empty");
	if(ob) destruct(ob);
}

private void destruct_ob(object ob)
{
	if(ob) destruct(ob);
}

//延时销毁对象
varargs void delay_destruct(object ob, int delay)
{
	if(delay < 1) delay = 1;	
	call_out("move_destruct", delay, ob);
}

/*****************************文件函数*****************************/

//单一文件名，不含路径
string file_leaf(object ob)
{
	return path_file(base_name(ob));
}

//单一文件名，不含路径
string file_dir(object ob)
{
	return path_dir(base_name(ob));
}


mixed test()
{
	string s = __FILE__;//"1234567";
	return s[0..<3];
}


/*****************************其他函数*****************************/
//今天
int today()
{
	return localtime(time())[LT_MDAY];
}

//日期
string date()
{
	mixed* t = localtime(time());
	return sprintf("%02d-%02d-%02d", t[LT_YEAR], t[LT_MON] + 1, t[LT_MDAY]);
}

//时间
string time1()
{
	mixed* t = localtime(time());
	return sprintf("%02d:%02d:%02d", t[LT_HOUR], t[LT_MIN], t[LT_SEC]);
}