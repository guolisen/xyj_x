// by firefox 06/21/2010

/*
fame
阵营声望表：
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
阵营                态度                贡献              
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
普陀                崇敬                6467              [1]
方寸                友好                100
无底洞              厌恶                -190
火云洞              厌恶                -190
--------------------------------------------------------------------
四大天王            友善                230               [2]
三清                友善                204
天蓬府              尊敬                1420
--------------------------------------------------------------------
毒敌洞              友善                200               [3]
通天河              厌恶                -210
麒麟山              友善                200
--------------------------------------------------------------------
庐山                尊敬                5564              [4]
不堕轮回教          不同戴天            -7324
文盲                中立                0
水泊梁山            冷漠                -100
--------------------------------------------------------------------
取经人              尊敬                2003              [5]
江湖骗子            中立                0
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
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
	({ -4*M,		"不同戴天" }),
	({ -2*M,		"厌恶" }),
	({ -1*M,		"冷淡" }),
	({ 1*M,			"中立" }),
	({ 2*M,			"友善" }),
	({ 4*M,			"尊敬" }),
	({ 1000*M,		"德高望重" }),
});

#define LINE1 "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
#define LINE2 "--------------------------------------------------------------------\n"
#define TIT01 "阵营                态度                贡献\n"
#define FMT01 "%-20s%-20s%d\n"

///列出阵营声望
void list(object who)
{	
	mapping data = query(who);
	int has_pre = 0;

	write("阵营声望：\n");
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


//更新声望，最低的声望减少，随机加到其他声望
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

