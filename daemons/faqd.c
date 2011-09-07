// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit F_RDB;

/*
	_sn		编号
	_ts		时间
	qu		问题
	an		答案
	wei		权重
	aid		作者id
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

//根据关键字搜索
mapping search_words(string* words, int top)
{	
	mapping rs = search("qu", words, top);
	rs += search("an", words, top);
	return rs;
}

//增加
int add(string arg)
{
	string qu;
	string an;
	if(arg && sscanf(arg, "%s %s", qu, an) == 2) {
		insert((["qu" : qu, "an" : an, "aid" : getuid(this_player()) ]));
	}
	return 1;
}

//列出低权重的记录
mapping lower(int thr, int number)
{
	return select(({ ({ "wei", "<", thr }) }), number);
}

//列出低权重的记录
int certify(string sn, int wei)
{
	mapping rec = _records[sn];
	if(rec) {
		rec["wei"] += wei;
		return 1;
	}
	return 0;
}

//显示指定的集合
int list(mapping rs)
{
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	foreach(string sn, mapping rec in rs) {
		printf(NOR"●"HIW"%-60s[%-4s]%s\n"HIG"  %s\n",			
			rec["qu"],
			sn,
			rec["aid"],
			rec["an"],
		);
	}
	printf(NOR);
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

	return 1;
}

