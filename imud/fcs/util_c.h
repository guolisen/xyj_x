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

///���֪ͨ��Ϣ
void on_notify(mapping info)
{
	string str = sprintf(_msgs[msg_id], arg1);
	notify_ok(str);
}

//��ù�����Ϣ
void on_message(mapping info)
{
	msv(_msgs[], info);	
}

//ͨ�ñ���
object_f _localizer;			//���ػ�����
object_f _stand;				//��̨

void init_c()
{
	_game_id	= path_file(__FILE__)[0] - '0';
	_stand		= __DIR__"stand" + _game_id;

	_localizer	= __DIR__"localizer";
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

//��ȡ�������
varargs mixed data_of(object who, string prop)
{
	string root = _localizer->get("prop_root");
	mapping m = who->query(root);
	if(!mapp(m)) who->set(root, m = ([]));
	return prop ? m[prop] : m;
}

//���ֳ��Ϳ�̨������Ϣ
varargs int msv(string str, mapping who, mapping target)
{
	return msg_rooms(({_this, _stand}), str, who, target);
}

//ĳ��˵��
varargs int say(mapping who, string str)
{
	msv(CYN + "$N˵����" + str + NOR, who);
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

