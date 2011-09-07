#ifndef IMUD_LIB_EFUN_H_INCLUDED
#define IMUD_LIB_EFUN_H_INCLUDED

// iMUD simul_efun

#include <imud.h>
#include <ansi.h>

/********************************��������***********************************/
string name_id(mapping who);

/********************************ͨ�ú�***********************************/

#define object_f		string							//�ļ�������������ͨ�ַ���

#define _this			this_object()

#define assert(_exp)	if(!(_exp)) error("assert: _exp\n")

#define swap2(a, b)		{mixed t = a; a = b; b = t;}

#define MUD_ID			"cn-xyj"



/********************************��ѧ����***********************************/

//�ϴ�ֵ
mixed max2(mixed a, mixed b) 
{
	return a >= b ? a : b;
}

//��Сֵ
mixed min2(mixed a, mixed b)
{
	return a <= b ? a : b;
}

//���ֵ
mixed max3(mixed a, mixed b, mixed c)
{
	return max2(max2(a, b), c);
}

//��Сֵ
mixed min3(mixed a, mixed b, mixed c)
{
	return min2(min2(a, b), c);
}

//���a�ǿ���a������b��
mixed or2(mixed a, mixed b)
{
	return a ? a : b;
}

//���a����a������b
mixed and2(mixed a, mixed b)
{
	return !a ? a : b;
}

//�����������ѡ��һ��Ԫ��
mixed random1(mixed* arr)
{
	return arr[random(sizeof(arr))];
}

/********************************�ַ�������***********************************/

//��������ָ���ַ�λ��
int rfind(string str, int ch)
{
	int i;
	for(i = sizeof(str) - 1; i >= 0; --i) {
		if(str[i] == ch) break;
	}
	return i;
}

//ȫ·���е��ļ���
string path_file(string path)
{
	int i = rfind(path, '/');
	return path[i+1..];
}

//ȫ·���е�·����
string path_dir(string path)
{
	int i = rfind(path, '/');
	return path[0..i-1];
}



//������
string neg_direction(string d)
{
	mapping m = (["east" : "west", "south": "north", "west" : "east", "north" : "south"]);
	return m[d];
}

/********************************��Ϣ����***********************************/

//��wiz�����������
varargs int trace(string msg, object who)
{
	if(!who) who = this_player();
	if(who && wizardp(who)) {
		tell_object(who, HIW"TRACE:"HIY + msg + NOR"\n");
	}
	return 1;
}

//��ʾ��Ϣ�������سɹ�
int notify_ok(string msg)
{
	write(msg);
	return 1;
}

//���ұ������
object find_who(mapping who)
{
	return (who && who["mid"] == MUD_ID) ? find_player(who["id"]) : 0;
}

//��ʾ��Ϣ
varargs int msv11(string str, mapping who, object stand)
{
	if(who)	str = replace_string(str, "$N", name_id(who));
	//todo
	write(str);
}


//��ʾ��Ϣ��������̨
varargs int msg_rooms(mixed* rooms, string str, mapping me, mapping target)
{
	object ob1 = find_who(me);
	object ob2 = find_who(target);
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


/********************************��ѧ��������***********************************/

//ϴ��
int* shuffle(int* arr)
{
	int size = sizeof(arr);
	for(int i = 0; i < size; ++i) {
		int j = random(size);
		swap2(arr[i], arr[j]);
	}
	return arr;
}


#endif

