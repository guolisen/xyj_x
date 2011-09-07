// by firefox 11/21/2009
// ip��idת��

#include "xyj_x.h"

mapping _id_ip = ([]);		//ip����Ӫ��Ӧ��
mapping _ip_ids = ([]);		//ip��id�����Ӧ��


//ipתid��
string* ip_to_ids(string ip)
{
	if(!_ip_ids[ip]) _ip_ids[ip] = ({});
	return _ip_ids[ip];
}

//idתip
string ip_of_id(string id)
{
	return _id_ip[id];
}

//ip�ϵ�id��
int ip_id_count(string ip)
{
	return sizeof(ip_to_ids(ip));
}

//���ip
void ip_clear()
{
	_ip_ids = ([]);
	_id_ip = ([]);
}

//��¼һ��ip & id
void ip_add2(string ip, string id)
{	
	if(!_ip_ids[ip]) _ip_ids[ip] = ({ id });
	else _ip_ids[ip] += ({ id });
	_id_ip[id] = ip;
}

//��¼һ���û�
void ip_add(object who)
{
	string ip = query_ip_number(who);
	string id = getuid(who);
	ip_add2(ip, id);
}

//ɾ��һ���û�
void ip_remove_id(string id)
{
	string ip = _id_ip[id];
	map_delete(_id_ip, id);
	_ip_ids[ip] -= ({ id });
}

//ɾ��һ���û�
void ip_remove(object who)
{
	string id = getuid(who);
	ip_remove_id(id);
}

//ɾ�������Ѿ����ߵ��û�
int ip_shrink()
{
	string* ids = ({});
	foreach(string ip, string* arr in _ip_ids) {
		foreach(string id in arr) {
			if(!find_player(id)) ids += ({ id });
		}
	}
	foreach(string id in ids) {
		ip_remove_id(id);
	}
	return sizeof(ids);
}


int ip_test()
{
	object me = this_player();
	string id = getuid(me);
	string ip = query_ip_number(me);
	string* arr;

	ip_clear();
	ip_add(me);

	assert(ip_of_id(id) == ip);
	assert(ip_id_count(ip) == 1);
	assert(ip_to_ids(ip)[0] == id);
	
	return 1;
}

