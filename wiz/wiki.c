// by firefox 02/21/2010

#include <weapon.h>
#include <ansi.h>
#include <xyj_x.h>

inherit F_LOADABLE;
inherit DAGGER;

string help_msg = @LONG

一本记录记录了西游记清华站百科知识的书籍。可以用以下命令获取
或者记录帮助文档。注意关键字列表中的关键字要用空格分隔开。

    wiki key_words         根据关键字列表搜索帮助信息
    faq_add                增加一条faq
    faq_lower              列出最后的faq，编辑专用
    faq_del                删除一条faq，编辑专用
    faq_certify            确认一条faq，编辑专用

    doc_update             更新文档数据库，wiz专用

LONG;

void create()
{
	set_name(HIG"西游百科"NOR, ({ "xyj wiki", "wiki" }) );
	set_weight(10);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "卷");
		set("long", help_msg);
		set("weapon_prop/spells", 20);
		set("wield_msg", "$N从怀中摸出一卷$n捧在手中。\n");
		set("unwield_msg", "$N将手中的$n藏入怀中。\n");
		set("changed", 1);

	}
	init_dagger(1);
	setup();
}

void doc_add_actions();

void init()
{
	doc_add_actions();
}

/*****************************函数主题*****************************/
#define MAX_ITEM	15

void doc_add_actions()
{
	object who = this_player();

	add_action("faq_add", "faq_add");

	if(who->query("doc_editor")) {
		add_action("faq_del", "faq_del");
		add_action("faq_lower", "faq_lower");
		add_action("faq_certify", "faq_certify");
	}	

	if(wizardp(who)) {
		add_action("doc_update", "doc_update");
	}
}

//增加faq
int faq_add(string arg)
{
	if(arg) {
		FAQ_D->add(arg);
		write("OK.\n");
		return 1;
	}
	return notify_fail("指令格式：faq_add 问题 答案\n");
}

//确认faq
int faq_certify(string arg)
{
	if(arg && FAQ_D->certify(arg, 100)) {
		write("OK.\n");
		return 1;
	}

	return notify_fail("指令格式：faq_add 问题 答案\n");
}

//增加faq
int faq_del(string arg)
{
	int n = to_int(arg);
	if(n > 0) {
		FAQ_D->delete(n);
		write("OK.\n");
		return 1;
	}
	return notify_fail("指令格式：faq_del 编号\n");
}

//列出牌位最低的faq
int faq_lower(string arg)
{
	int n = to_int(arg);	
	if(n > 1) {
		mapping rs = FAQ_D->lower(n, MAX_ITEM);
		printf("FAQ 权重低于%d的条目：\n", n);
		FAQ_D->list(rs);	
	}
	return 1;
}

//更新文档数据库
int doc_update()
{
	return DOC_D->update();
}
