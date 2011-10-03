// by firefox 04/16/2011
// iMUD local simul_efun

#include <imud-efun.h>

//����ID��ʾ
string name_id(mapping who)
{
	if(who[PMUD]) return sprintf("%s(%s@%s)", who[PNAME], capitalize(who[PID]), who[PMUD]);
	return sprintf("%s(%s)", who[PNAME], capitalize(who[PID]));
}

//�������
string player_name(object who)
{
	return filter_color(who->query("name"));
}

//��������Ϣ��ȱʡΪ��ǰ���
varargs mixed* player_info(object who)
{
	if(!who) who = this_player();
	if(who) return ({ player_name(who), getuid(who), MUD_ID });
	return 0;
}
