// by firefox 04/10/2010
// ������ģ��

#include <xyj_x.h>
#include <ansi.h>

inherit F_DATA_OF;
inherit F_FOT;
inherit F_VECTOR;

string _stat_prop;				//��������ͳ����Ϣ������


///��ʼ������
void init_prop()
{
	seteuid(getuid());

	set_data_prop(TASK_PROP + "/list/" + id());
	_stat_prop = TASK_PROP + "/stat/" + id();
}

///��¼���ĳ������
void add_gain(object who, string prop, int num)
{
	who->add(_stat_prop + "/gain/" + prop, num);
}
