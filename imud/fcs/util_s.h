#ifndef IMUD_UTIL_S_H_INCLUDED
#define IMUD_UTIL_S_H_INCLUDED
// by firefox 04/16/2011
// server util

mapping _g;									//��Ϸ����
mapping _listeners;							//��������Ϸ��MUD
string _client;								//�ͻ��˶�Ӧ����

//������ʾΪ�ַ���(�麯��)
string scene_str();

//��ȡ��Ϸ����
mixed g()
{
	return _g;
}

///��ʼ��������
void server_create()
{
	string* arr = explode(base_name(_this));

	_client = arr[>2] + "/c" + arr[>1][1..]
	_listeners = ([]);
}

///��ͻ��˷���֪ͨ��Ϣ
int notify(mixed* info, mixed msg)
{
	string msg = sprintf("%s->%s(%s)", _client, "on_notify", implode(info, ":"));
	ICE->send_msg(mud, msg);
	return 0;
}

///�ͻ��˼�������Ϸ
int listen(mixed* info)
{
	_listeners[info[PMUD]] = time();
}

///���м���MUD����ˢ����Ϣ
int refresh_all(string verb, mixed* info)
{
	int	thr = time() - 5*60;
	string msg = implode(info, ":");

	string msg = sprintf("%s->%s(%s)[%s]", _client, verb, implode(info, ":"), scene_str());

	foreach(string mud, int time in _listeners) {
		if(time > thr) ICE->send_msg(mud, msg);
	}
	return 1;
}

///���÷��ɺ���
void invoke(string fun)
{
	string who, list;
	mixed* info;

	if(sscanf(fun, "%s(%s)", fun, who) != 2) return;
	info = explode(who, ":");

	evaluate(fun, info);
	listen(info);
}


#endif

