// by firefox 04/10/2010
// �����������ģ��

#include <xyj_x.h>

inherit TT_Q4;

//������Ĳ�������
string colors_prop()
{
	return _stat_prop + "/colors/" + id();
}

//���ǰ������
int pre_check(object employer, object who)
{
	mapping msg = get_msg(employer);
	mapping m = data_of(who);

	if(m["state"] == "����") {
		msvx(msg["repeat"], employer, who, m["tname"]);
		return 0;
	}
	if(who->query(_stat_prop + "/balance") > 0) {
		msvx("$N��$n˵������λ$r��$S�����������ƻ��ƣ��β�ȥ���ٸ������������ͣ�\n", employer, who);
		return 0;
	}
	return 1;
}

//������
void new_task(object who, mapping task)
{
	::new_task(who, task);
	
	//if(who->query(colors_prop())) task["remark"] += "*";		//���û�֪��������
}


//���ֽ���������������Ҫ�һ����Լ�����ɫ
void give_reward(object who, int reward)
{
	who->add(_stat_prop + "/balance", reward);		//�������ɶһ������
	who->add(colors_prop(), 10);
}

