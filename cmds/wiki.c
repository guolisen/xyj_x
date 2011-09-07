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
				printf("FAQ 编号为%d的条目：\n", n);
				FAQ_D->list(([ "" + rec["_sn"] : rec ]));
				return 1;
			}
		}
		return notify_fail("无效的FAQ编号。\n");
	}
	else if(sscanf(arg, "d%d", n) == 1) {
		if(n > 0) {
			if(DOC_D->show("" + n)) return 1;
		}
		return notify_fail("无效的DOC编号。\n");
	}
	else {
		string* words = explode(arg, " ");
		mapping rs = FAQ_D->search_words(words, MAX_ITEM);
		if(rs && sizeof(rs)) {
			write("FAQ 中的搜索结果如下：\n");
			FAQ_D->list(rs);
		}
		rs = DOC_D->search_words(words, MAX_ITEM);
		if(rs && sizeof(rs)) {
			write("DOC 中的搜索结果如下：\n");
			DOC_D->list(rs);
		}
		return 1;
	}
	return help(me);
}

int help(object me)
{
	write(@HELP

指令格式 :
    wiki 关键字列表      搜索包含这些关键字的DOC或FAQ
    wiki f编号           显示指定编号的FAQ
    wiki d编号           显示指定编号的文档

系统中有两类文档：FAQ，简短的常见问题解答；DOC，关于某个
专题的文章。当使用命令第一种用法时，将在这两类文档中搜索。
搜索结果中包括了文档的摘要和文档编号（在文档条目右侧）。
如果要读某个文档就可以用指令后两种用法，在f或d后面直接加
上前面搜索到的编号。另外要注意的是关键字列表要用空格分隔。
 
HELP
	);
    return 1;
}