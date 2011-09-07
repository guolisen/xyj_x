// by firefox 06/21/2010

/*
fame
��Ӫ������
��������������������������������������������������������������������
��Ӫ                ̬��                ����              
��������������������������������������������������������������������
����                �羴                6467              [1]
����                �Ѻ�                100
�޵׶�              ���                -190
���ƶ�              ���                -190
--------------------------------------------------------------------
�Ĵ�����            ����                230               [2]
����                ����                204
���              ��                1420
--------------------------------------------------------------------
���ж�              ����                200               [3]
ͨ���              ���                -210
����ɽ              ����                200
--------------------------------------------------------------------
®ɽ                ��                5564              [4]
�����ֻؽ�          ��ͬ����            -7324
��ä                ����                0
ˮ����ɽ            ��Į                -100
--------------------------------------------------------------------
ȡ����              ��                2003              [5]
����ƭ��            ����                0
��������������������������������������������������������������������
*/

#include <xyj_x.h>
#include <ansi.h>

inherit F_PROP_DATA;
inherit F_VECTOR;

void create()
{
	seteuid(getuid());
	set_prop_name(XYJ_X"/fame");
	push_backs( ({"family",	"god", "devil", "guild", "player"}) );
}

mixed* _arr = ({
	({ -4*M,		"��ͬ����" }),
	({ -2*M,		"���" }),
	({ -1*M,		"�䵭" }),
	({ 1*M,			"����" }),
	({ 2*M,			"����" }),
	({ 4*M,			"��" }),
	({ 1000*M,		"�¸�����" }),
});

#define LINE1 "��������������������������������������������������������������������\n"
#define LINE2 "--------------------------------------------------------------------\n"
#define TIT01 "��Ӫ                ̬��                ����\n"
#define FMT01 "%-20s%-20s%d\n"

///�г���Ӫ����
void list(object who)
{	
	mapping data = query(who);
	int has_pre = 0;

	write("��Ӫ������\n");
	write(LINE1);
	write(TIT01);
	write(LINE1);

	foreach(string gid in elems()) {
		mapping group_data = data[gid];
		if(group_data) {
			if(has_pre) {
				write(LINE2);
				has_pre = 0;
			}
			foreach(string k, int value in group_data) {
				string str = sprintf(FMT01,
					k,
					MATH->cvt_rang(_arr, v),
					v,
				);
				write(str);
				has_pre = 1;
			}
		}
	}
	write(LINE1);
}


//������������͵��������٣�����ӵ���������
void update(object who)
{
	mapping data = query(who);
	foreach(string gid, mapping group in data) {
		foreach(string k, int v in data) {
			if(v > 0 && v < 1*M) {
				mapping g = data[random1(keys(data))];
				if(sizeof(g)) {

				}
			}
		}
	}
	
}

