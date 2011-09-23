#ifndef IMUD_UTIL_C_H_INCLUDED
#define IMUD_UTIL_C_H_INCLUDED
// by firefox 04/16/2011
// client util

static mapping _notify_msgs = 0;

///����֪ͨ��Ϣ��
void set_notify(mapping msgs)
{
	_notify_msgs = msgs;
}

///�ͻ��˻��֪ͨ��Ϣ
varargs int on_notify(mapping info)
{
	string str = sprintf(_msgs[msg_id], arg1);
	return notify_ok(str);
}


///��ȡ��ǰmud��id
string mud_id()
{
	return "xyj-cn";
}

///���ݶ�����Ϣ���Ҷ���
object info_ob(mapping info)
{
	if(info["mid"] == mud_id())
		return find_player(info["id"]);
	return 0;
}


//���������������
varargs int send_req(string verb, mixed arg, string req_msg)
{
	mapping info;

	if(mapp(arg)) info = arg;
	else if(userp(arg)) info = (["id" : getuid(arg)]);
	else info = ([]);

	if(req_msg) write(req_msg);
	info["mid"] = MUD_ID;
	//src//info["game"] = "fcs0";		//��Ϣ·��

	{
		string server = __DIR__"s0";
		server->recv_req(verb, info);
	}


	return 1;
}

//�������Է������ӵ�����
varargs int recv_req(string verb, mapping info)
{
	mixed* ret = evaluate(verb, info);

	return 1;
}


#endif

