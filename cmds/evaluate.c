// by firefox 11/21/2009

inherit F_CLEAN_UP;

#include <xyj_x.h>
#include <ansi.h>


int main(object me, string arg)
{
	string id;
	string tid;

	if(!arg) {
		FABAO->info(me);
	} else if(arg == "zhenshen") {
		FABAO->zhenshen(me);
	}
	else if(arg == "human") {
		FABAO->human(me);
	}
	else {
		string skill, tid;
		object target;
		
		if(sscanf(arg, "%s on %s", skill, tid) == 2) {
			target = precent(tid, environment(me));
		} else if(arg == "skill") {
			skill = "skill";
			target = me;
		}
		if(skill == "skill")
			FABAO->skill(me, target);		
	}
	return 1;
}

int help(object me)
{
	write(@HELP

ָ���ʽ : 

    comment ĳ�� Ʒ��             ����ĳ��
	
Ʒ�а�����

    ��ò	����ˢ�������ˣ���������
    

    ����
    ����

    ƫ��
	����    morals
    ����    ys    friendly      lm    ��Į
    ��Ծ    hy    lively        ld    ��߶
    ����    kq    manner        cl    ��³
    ��ʵ    cs    honest        sh    ������
    ����    gz    justness      zs    ��˽
    ����    ql    diligent      ld    ����



��ҵ�Ʒ�н�Ӱ����ҵ�������

HELP
	);
	return 1;
}

chat ����ҵõ���Ծ�ȣ�
��лĳ�ˣ��Է��õ����ƶȣ�
��Ͷ��ĳ�ˣ������Է��ġ�

