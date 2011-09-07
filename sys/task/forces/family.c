// by firefox 04/10/2010
// ��������

#include <xyj_x.h>

inherit TT_Q4;
inherit TDB_FAMILY;

void create()
{
	init_prop(2400);
	tdb_load(X_DATA_DIR + "task/forces/_" + id());
}


//��ȡ��ʾ��Ϣ����
mapping get_msg(object employer)
{
	return ([
		"task"			: ([			
			"ask"			: "$N��$n˵�������Ϊʦ��һ�ˣ�ȥ�ݼ�%sѯ���й�%sһ�¡�\n",
			"kill"			: "$N��$n˵����%s�к����ŵ��ӣ��ﲻ���⣬��ȥ��Ϊʦ���ˣ�\n",
			"give"			: "$N��$n˵����%s�и�ΪʦѰ��%s����ȥ����ɡ�\n",
		]),
		"no_norm"		: "���շ�����",
		"apply_say"		: "·��С�ġ�",
		"check_say"		: "����Ϊ��ǳ�����Ƕ�������ɡ�",
	]);
}

//���轱����������Ҫ�޸�
void give_reward(object who, int reward)
{
	mapping m = data_of(who);
	int wx = reward / 2;
	int qn = reward / 2 / 4;

	who->add(CEXP, wx);
	who->add(PEXP, qn);
	parent()->add_gain(who, CEXP, wx);
	parent()->add_gain(who, PEXP, qn);

	tell_object(who, "��õ���" + chinese_number(wx)
		+ "����ѧ�����" + chinese_number(qn) + "��Ǳ�ܣ�\n");
}

