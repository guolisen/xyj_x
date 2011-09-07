// by firefox 14/06/2009 

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"gift";

mapping _tab = ([
	"cps" : "����", "per" : "��ò", "cor" : "��ʶ", "kar" : "��Ե",
	"str" : "���", "con" : "����", "int" : "����", "spi" : "����",
]);

mapping _attrs = ([
	"cps" : 10, "per" : 10, "cor" : 10, "kar" : 10,
	"str" : 10, "con" : 10, "int" : 10, "spi" : 10,
]);

void create()
{
	set_name( HIG"ϴ�赤"NOR , ({ "xisui dan" }));
	set("long", "һ�ŷ����̹��Сҩ�裬������(set)����츳��������ϳ��²���Ч��\n");

	setup();
}

void init()
{
	::init();
	add_action("do_set", "set");
	add_action("do_eat", "eat");	
}

int show()
{
	int num = 0;
	object who = this_player();
	foreach(string str in keys(_tab)) {
		num += who->query(str) - _attrs[str];
	}
	printf("\n�츳���£�����%d���츳δ���䣺\n", num);
	printf("��������������������������������������������������������������������\n");
	printf("����(cps):[%d]  ��ò(per):[%d]  ��ʶ(cor):[%d]  ��Ե(kar):[%d]\n",
		_attrs["cps"], _attrs["per"], _attrs["cor"], _attrs["kar"]);
	printf("���(str):[%d]  ����(con):[%d]  ����(int):[%d]  ����(spi):[%d]\n",
		_attrs["str"], _attrs["con"], _attrs["int"], _attrs["spi"]);
	printf("��������������������������������������������������������������������\n");
	if(!num) printf(HIG"�����ڳ������츳����Ч��\n"NOR);
	return num;
}

int do_set(string arg)
{
	string str;
	int num;
	if(!stringp(arg) || sscanf(arg, "%s %d", str, num) != 2) 
		printf("�����ʽ��set �츳 ����\n");
	else if(!_tab[str]) 
		printf("��Ч���츳��\n");
	else if(num < 10 || num > 30) 
		printf("�츳ֵֻ�ܽ���10-30֮�䡣\n");
	else {
		_attrs[str] = num;
	}
	show();
	return 1;
}

int do_eat(string arg)
{
	object who = this_player();

	if(!check(arg)) return 0;

	if(show()) {
		printf("���趨���츳�����������츳�������Ǻϡ�\n");
		return 1;
	}
	
	message_vision(HIG"$N����һ��$n"HIG"���پ���̥���ǡ�\n" NOR, who, _this);

	foreach(string id, int k in _attrs) {
		who->set(id, k);
	}
	
	destruct(_this);
	return 1;
}
