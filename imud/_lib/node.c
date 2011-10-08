// firefox 04/16/2011
// C/S���ò���

#include <imud-efun.h>

mapping _listeners = ([]);


///���Զ�̼�����
void add_listener(mixed* info)
{
	_listeners[info[PMUD]] = time();	
}

///���ɵ���
void invoke(string fun_str)
{
	string fun, gid, arg;
	mixed* info;
	
	if(sscanf(fun_str, "%s(%s,%s)", fun, gid, arg) != 3) error("invoke invalid arg.\n");
	info = gid_player(gid);	
	
	add_listener(info);
	call_other(_this, fun, info, arg);

}


///����ߵļ���MUD����ˢ����Ϣ
varargs int reply(string peer_name, string fun, mixed* who, mixed arg)
{
	string req = sprintf("%s->%s(%s,%s)",
		peer_name,
		fun,
		player_gid(who),
		(undefinedp(arg) ? "" : "" + arg),
	);

	ICE_D->send_msg(who[PMUD], req);
	return 1;
}

