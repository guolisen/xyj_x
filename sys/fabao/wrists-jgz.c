// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit ITEM;
inherit FABAO;

/*
�����ǽ�����������ҹ����ػ���֮������������֮����
ƾ����ô������ˮ�𣬾�Ī�ܽ�������͵ȥ�ҵİŽ��ȶ�������Ҳ�����������ӡ���

һֻ��ȡ���ǰ�ɭɭ��Ȧ�������������𣬽������ţ���������һ�£�����������׽��������ŵ�����߸̫�ӳ���������ħ����ʤ���ء�

*/
void create()
{
	set_name(HIG"�����"NOR, ({ "jinggang zhuo", "zhuo" }) );
	set("long", "һ�Ź�â����ı��飬�����������sldh2���ܡ�\n");
	set("unit", "��" );
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