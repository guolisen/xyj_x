// by firefox 03/13/2010

inherit F_CLEAN_UP;

#include <xyj_x.h>
#include <ansi.h>

#define MAX_ITEM	15

int help(object me);

int main(object me, string arg)
{
	int n;
	if(!arg) return help(me);

	if(sscanf(arg, "f%d", n) == 1) {
		if(n > 0) {
			mapping rec = FAQ_D->select1(n);
			if(rec) {
				printf("FAQ ���Ϊ%d����Ŀ��\n", n);
				FAQ_D->list(([ "" + rec["_sn"] : rec ]));
				return 1;
			}
		}
		return notify_fail("��Ч��FAQ��š�\n");
	}
	else if(sscanf(arg, "d%d", n) == 1) {
		if(n > 0) {
			if(DOC_D->show("" + n)) return 1;
		}
		return notify_fail("��Ч��DOC��š�\n");
	}
	else {
		string* words = explode(arg, " ");
		mapping rs = FAQ_D->search_words(words, MAX_ITEM);
		if(rs && sizeof(rs)) {
			write("FAQ �е�����������£�\n");
			FAQ_D->list(rs);
		}
		rs = DOC_D->search_words(words, MAX_ITEM);
		if(rs && sizeof(rs)) {
			write("DOC �е�����������£�\n");
			DOC_D->list(rs);
		}
		return 1;
	}
	return help(me);
}

int help(object me)
{
	write(@HELP

ָ���ʽ :
    wiki �ؼ����б�      ����������Щ�ؼ��ֵ�DOC��FAQ
    wiki f���           ��ʾָ����ŵ�FAQ
    wiki d���           ��ʾָ����ŵ��ĵ�

ϵͳ���������ĵ���FAQ����̵ĳ���������DOC������ĳ��
ר������¡���ʹ�������һ���÷�ʱ�������������ĵ���������
��������а������ĵ���ժҪ���ĵ���ţ����ĵ���Ŀ�Ҳࣩ��
���Ҫ��ĳ���ĵ��Ϳ�����ָ��������÷�����f��d����ֱ�Ӽ�
��ǰ���������ı�š�����Ҫע����ǹؼ����б�Ҫ�ÿո�ָ���
 
HELP
	);
    return 1;
}