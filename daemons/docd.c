// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit F_RDB;

#define DOC_DIR	"/doc/help/wiki/"

//编号，作者，关键字，是否原创，正文

/*
	_sn		编号
	_ts		时间
	title	标题
	abs		摘要
	aid		作者
	src		来源
*/
void create()
{
	::create();
}

int remove()
{
	return ::remove();
}

//根据关键字搜索
mapping search_words(string* words, int top)
{	
	mapping rs = search("title", words, top);
	rs += search("abs", words, top);
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

//显示指定的集合
int list(mapping rs)
{
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	foreach(string sn, mapping rec in rs) {
		printf(NOR"●"HIW"%-60s[%-4s]%s\n"HIG"  %s\n",			
			rec["title"],
			rec["file"],
			rec["aid"],
			rec["abs"],
		);
	}
	printf(NOR);
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

	return 1;
}

//显示指定的集合
int show(string arg)
{
	string name = DOC_DIR + arg;
	if(file_size(name) < 1) return 0;
	this_player()->start_more(read_file(name), 4);
	return 1;
}

//更新文档数据库
int update()
{
	mapping m = ([
		"标题"	: "title",
		"作者"	: "aid",
		"来源"	: "src",
		"摘要"	: "abs",
	]);

	delete_all();

	foreach(string file in get_dir(DOC_DIR)) {
		string path = DOC_DIR + file;
		mapping rec = ([ "file" : file ]);

		for(int i = 0; i < sizeof(m); ++i) {
			string str = read_file(path, i + 1, 1);
			string k, v;
			printf("%d, %s \n", i + 1, str);
			if(str && (sscanf(str, "%s %s\n", k, v) == 2)) {
				k = m[k];
				if(k) rec[k] = v;
			}
		}
		insert(rec);
	}
	save();
	return 1;
}
