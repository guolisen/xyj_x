// firefox 04/16/2011
// iMUD-simul_efun实现

#include <imud-efun.h>
#include <ansi.h>

inherit F_iEFUN_LOCAL;		//继承本地化函数的实现

/********************************数学函数***********************************/

///较大值
mixed max2(mixed a, mixed b) 
{
	return a >= b ? a : b;
}

///较小值
mixed min2(mixed a, mixed b)
{
	return a <= b ? a : b;
}

///最大值
mixed max3(mixed a, mixed b, mixed c)
{
	return max2(max2(a, b), c);
}

///最小值
mixed min3(mixed a, mixed b, mixed c)
{
	return min2(min2(a, b), c);
}

///从数组中随机选择一个元素
mixed random1(mixed* arr)
{
	return arr[random(sizeof(arr))];
}

///洗牌
int* shuffle(int* arr)
{
	int size = sizeof(arr);
	for(int i = 0; i < size; ++i) {
		int j = random(size);
		swap2(arr[i], arr[j]);
	}
	return arr;
}

/********************************逻辑函数***********************************/

///如果a非空则a，否则b。
mixed or2(mixed a, mixed b)
{
	return a ? a : b;
}

///如果a空则a，否则b
mixed and2(mixed a, mixed b)
{
	return !a ? a : b;
}

/********************************字符串函数***********************************/

///分配定长字符串
string allocate_str(int n)
{
	return sprintf("%" + n + "s", "");
}

///反向搜索指定字符位置
int rfind(string str, int ch)
{
	int i;
	for(i = sizeof(str) - 1; i >= 0; --i) {
		if(str[i] == ch) break;
	}
	return i;
}

///全路径中的文件名
string path_file(string path)
{
	int i = rfind(path, '/');
	return path[i+1..];
}

///全路径中的路径名
string path_dir(string path)
{
	int i = rfind(path, '/');
	return path[0..i-1];
}

///反方向
string neg_direction(string d)
{
	mapping m = (["east" : "west", "south": "north", "west" : "east", "north" : "south"]);
	return m[d];
}

static string _base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

///base64编码
string to_base64(int* arr)
{
	int n = sizeof(arr);
	string str = allocate_str(n);

	for(int i = 0; i < n; ++i) {
		str[i] = _base64[arr[i]];
	}
	return str;
}

///base64解码
int* from_base64(string str)
{
	int n = sizeof(str);
	int* arr = allocate(n);

	for(int i = 0; i < n; ++i) {
		arr[i] = member_array(str[i], _base64);
	}
	return arr;
}

/********************************对象函数***********************************/

///查找本地玩家
object player_object(mixed* who)
{
	return (who && who[PMUD] == MUD_ID) ? find_player(who[PID]) : 0;
}

///从玩家信息产生全局ID
string player_gid(mixed* who)
{
	if(!who) who = NOBODY;
	return sprintf("%s:%s:%s", who[PNAME], who[PID], who[PMUD]);
}

///从全局ID产生玩家信息
mixed* gid_player(string gid)
{
	mixed* who = NOBODY;
	string name, id, mud;
	if(gid && sscanf(gid, "%s:%s:%s", name, id, mud) == 3) {
		who[PNAME] = name;
		who[PID] = id;
		who[PMUD] = mud;
	}
	return who;
}


///目标的文件名，不含路径，缺省为当前对象
varargs string file_leaf(object ob)
{
	return path_file(base_name(or2(ob, _this)));
}

///目标所在目录，不含文件名，缺省为当前对象
string file_dir(object ob)
{
	return path_dir(base_name(or2(ob, _this)));
}

/********************************消息函数***********************************/

///向wiz报告测试数据
varargs int trace(string msg, object who)
{
	if(!who) who = this_player();
	if(who && wizardp(who)) {
		tell_object(who, HIW"TRACE:"HIY + msg + NOR"\n");
	}
	return 1;
}

///显示信息，并返回成功
int notify_ok(string msg)
{
	write(msg);
	return 1;
}

///显示信息，包括看台
varargs int msg_rooms(mixed* rooms, string str, mixed* me, mixed* target)
{
	object ob1 = player_object(me);
	object ob2 = player_object(target);
	object* exclude = ({ ob1, ob2 });
	string msg = str;

	if(me) msg = replace_string(msg, "$N", name_id(me));
	if(target) msg = replace_string(msg, "$n", name_id(target));
	
	foreach(object room in rooms) {	
		tell_room(room, msg, exclude);
	}
	if(ob1) {
		msg = str;
		if(target) msg = replace_string(msg, "$n", name_id(target));
		msg = replace_string(msg, "$N", "你");
		tell_object(ob1, msg);
	}
	if(ob2) {
		msg = str;
		if(me) msg = replace_string(msg, "$N", name_id(me));
		msg = replace_string(msg, "$n", "你");
		tell_object(ob2, msg);
	}
	return 1;
}

