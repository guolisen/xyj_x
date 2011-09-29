// firefox 04/16/2011
// iMUD-simul_efunʵ��

#include <imud-efun.h>
#include <ansi.h>

inherit F_iEFUN_LOCAL;		//�̳б��ػ�������ʵ��

/********************************��ѧ����***********************************/

///�ϴ�ֵ
mixed max2(mixed a, mixed b) 
{
	return a >= b ? a : b;
}

///��Сֵ
mixed min2(mixed a, mixed b)
{
	return a <= b ? a : b;
}

///���ֵ
mixed max3(mixed a, mixed b, mixed c)
{
	return max2(max2(a, b), c);
}

///��Сֵ
mixed min3(mixed a, mixed b, mixed c)
{
	return min2(min2(a, b), c);
}

///�����������ѡ��һ��Ԫ��
mixed random1(mixed* arr)
{
	return arr[random(sizeof(arr))];
}

///ϴ��
int* shuffle(int* arr)
{
	int size = sizeof(arr);
	for(int i = 0; i < size; ++i) {
		int j = random(size);
		swap2(arr[i], arr[j]);
	}
	return arr;
}

/********************************�߼�����***********************************/

///���a�ǿ���a������b��
mixed or2(mixed a, mixed b)
{
	return a ? a : b;
}

///���a����a������b
mixed and2(mixed a, mixed b)
{
	return !a ? a : b;
}

/********************************�ַ�������***********************************/

///���䶨���ַ���
string allocate_str(int n)
{
	return sprintf("%" + n + "s", "");
}

///��������ָ���ַ�λ��
int rfind(string str, int ch)
{
	int i;
	for(i = sizeof(str) - 1; i >= 0; --i) {
		if(str[i] == ch) break;
	}
	return i;
}

///ȫ·���е��ļ���
string path_file(string path)
{
	int i = rfind(path, '/');
	return path[i+1..];
}

///ȫ·���е�·����
string path_dir(string path)
{
	int i = rfind(path, '/');
	return path[0..i-1];
}

///������
string neg_direction(string d)
{
	mapping m = (["east" : "west", "south": "north", "west" : "east", "north" : "south"]);
	return m[d];
}

static string _base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

///base64����
string to_base64(int* arr)
{
	int n = sizeof(arr);
	string str = allocate_str(n);

	for(int i = 0; i < n; ++i) {
		str[i] = _base64[arr[i]];
	}
	return str;
}

///base64����
int* from_base64(string str)
{
	int n = sizeof(str);
	int* arr = allocate(n);

	for(int i = 0; i < n; ++i) {
		arr[i] = member_array(str[i], _base64);
	}
	return arr;
}

/********************************������***********************************/

///���ұ������
object player_object(mixed* who)
{
	return (who && who[PMUD] == MUD_ID) ? find_player(who[PID]) : 0;
}

///�������Ϣ����ȫ��ID
string player_gid(mixed* who)
{
	if(!who) who = NOBODY;
	return sprintf("%s:%s:%s", who[PNAME], who[PID], who[PMUD]);
}

///��ȫ��ID���������Ϣ
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


///Ŀ����ļ���������·����ȱʡΪ��ǰ����
varargs string file_leaf(object ob)
{
	return path_file(base_name(or2(ob, _this)));
}

///Ŀ������Ŀ¼�������ļ�����ȱʡΪ��ǰ����
string file_dir(object ob)
{
	return path_dir(base_name(or2(ob, _this)));
}

/********************************��Ϣ����***********************************/

///��wiz�����������
varargs int trace(string msg, object who)
{
	if(!who) who = this_player();
	if(who && wizardp(who)) {
		tell_object(who, HIW"TRACE:"HIY + msg + NOR"\n");
	}
	return 1;
}

///��ʾ��Ϣ�������سɹ�
int notify_ok(string msg)
{
	write(msg);
	return 1;
}

///��ʾ��Ϣ��������̨
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
		msg = replace_string(msg, "$N", "��");
		tell_object(ob1, msg);
	}
	if(ob2) {
		msg = str;
		if(me) msg = replace_string(msg, "$N", name_id(me));
		msg = replace_string(msg, "$n", "��");
		tell_object(ob2, msg);
	}
	return 1;
}

