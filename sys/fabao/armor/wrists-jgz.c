// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit ITEM;
inherit FABAO;

/*
『我那金刚琢，乃是我过函关化胡之器，自幼炼成之宝。
凭你甚么兵器，水火，俱莫能近他。若偷去我的芭蕉扇儿，连我也不能奈他何矣。』

一只手取出那白森森的圈子来，望空抛起，叫声『着！』唿喇的一下，把六般兵器套将下来，慌得那哪吒太子赤手逃生，魔王得胜而回。

*/
void create()
{
	set_name(HIG"金刚琢"NOR, ({ "jinggang zhuo", "zhuo" }) );
	set("long", "一颗光芒四射的宝珠，可以让你测试sldh2技能。\n");
	set("unit", "颗" );
	set("changed", 1);
}

void init()
{
	filter_cmd();
}

//
int ji(object me, object target)
{

}