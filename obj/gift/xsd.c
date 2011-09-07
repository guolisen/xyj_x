// by firefox 14/06/2009 

#include <ansi.h>

inherit ITEM;

#define NAME	HIG"ϴ�赤"NOR
#define ID		"xisui dan"

mapping tab = ([
	"cps" : "����", "per" : "��ò", "cor" : "��ʶ", "kar" : "��Ե",
	"str" : "���", "con" : "����", "int" : "����", "spi" : "����",
]);

mapping attrs = ([
	"cps" : 10, "per" : 10, "cor" : 10, "kar" : 10,
	"str" : 10, "con" : 10, "int" : 10, "spi" : 10,
]);

void create()
{
	set_name( NAME , ({ ID }));
	set_weight(90);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "һ�ŷ����̹��Сҩ�裬������(set)����츳��������ϳ��²���Ч��\n");
		set("value", 1000000);
		set("drug_type", "��Ʒ");
	}
	set("is_monitored",1);
	setup();
}

void init()
{
	add_action("do_set", "set");
	add_action("do_eat", "eat");	
}

int show()
{
	int num = 0;
	object who = this_player();
	foreach(string str in keys(tab)) {
		num += who->query(str) - attrs[str];
	}
	printf("\n�츳���£�����%d���츳δ���䣺\n", num);
	printf("��������������������������������������������������������������������\n");
	printf("����(cps):[%d]  ��ò(per):[%d]  ��ʶ(cor):[%d]  ��Ե(kar):[%d]\n",
		attrs["cps"], attrs["per"], attrs["cor"], attrs["kar"]);
	printf("���(str):[%d]  ����(con):[%d]  ����(int):[%d]  ����(spi):[%d]\n",
		attrs["str"], attrs["con"], attrs["int"], attrs["spi"]);
	printf("��������������������������������������������������������������������\n");
	if(!num) printf(HIG"�����ڿ���ʹ�ã�eat "ID"��ʹ�����츳��Ч��\n"NOR);
	return num;
}

int do_set(string arg)
{
	string str;
	int num;
	if(!stringp(arg) || sscanf(arg, "%s %d", str, num) != 2) 
		printf("�����ʽ��set �츳 ����\n");
	else if(!tab[str]) 
		printf("��Ч���츳��\n");
	else if(num < 10 || num > 30) 
		printf("�츳ֵֻ�ܽ���10-30֮�䡣\n");
	else {
		attrs[str] = num;
	}
	show();
	return 1;
}

int do_eat(string arg)
{
	object who = this_player();
	if(show()) {
		printf("���趨���츳�����������츳�������Ǻϡ�\n");
		return 1;
	}
	
	message_vision(HIG"$N����һ��"NAME HIG"���پ���̥���ǡ�\n" NOR, who);

	foreach(string id, int k in attrs) {
		who->set(id, k);
	}
	
	destruct(this_object());
	return 1;
}
