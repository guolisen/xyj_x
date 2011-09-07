// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit F_RDB;

/*
	_sn		���
	_ts		ʱ��
	qu		����
	an		��
	wei		Ȩ��
	aid		����id
*/
void create()
{
	::create();
	seteuid(getuid());
}

int remove()
{
	return ::remove();
}

//���ݹؼ�������
mapping search_words(string* words, int top)
{	
	mapping rs = search("qu", words, top);
	rs += search("an", words, top);
	return rs;
}

//����
int add(string arg)
{
	string qu;
	string an;
	if(arg && sscanf(arg, "%s %s", qu, an) == 2) {
		insert((["qu" : qu, "an" : an, "aid" : getuid(this_player()) ]));
	}
	return 1;
}

//�г���Ȩ�صļ�¼
mapping lower(int thr, int number)
{
	return select(({ ({ "wei", "<", thr }) }), number);
}

//�г���Ȩ�صļ�¼
int certify(string sn, int wei)
{
	mapping rec = _records[sn];
	if(rec) {
		rec["wei"] += wei;
		return 1;
	}
	return 0;
}

//��ʾָ���ļ���
int list(mapping rs)
{
	printf("��������������������������������������������������������������������������������\n");
	foreach(string sn, mapping rec in rs) {
		printf(NOR"��"HIW"%-60s[%-4s]%s\n"HIG"  %s\n",			
			rec["qu"],
			sn,
			rec["aid"],
			rec["an"],
		);
	}
	printf(NOR);
	printf("��������������������������������������������������������������������������������\n");

	return 1;
}

