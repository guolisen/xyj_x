// by firefox 14/06/2009 

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"gift";

mapping _tab = ([
	"cps" : "定力", "per" : "容貌", "cor" : "胆识", "kar" : "福缘",
	"str" : "体格", "con" : "根骨", "int" : "悟性", "spi" : "灵性",
]);

mapping _attrs = ([
	"cps" : 10, "per" : 10, "cor" : 10, "kar" : 10,
	"str" : 10, "con" : 10, "int" : 10, "spi" : 10,
]);

void create()
{
	set_name( HIG"洗髓丹"NOR , ({ "xisui dan" }));
	set("long", "一颗泛着绿光的小药丸，能设置(set)你的天赋，设置完毕吃下才生效。\n");

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
	printf("\n天赋如下，尚有%d点天赋未分配：\n", num);
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	printf("定力(cps):[%d]  容貌(per):[%d]  胆识(cor):[%d]  福缘(kar):[%d]\n",
		_attrs["cps"], _attrs["per"], _attrs["cor"], _attrs["kar"]);
	printf("体格(str):[%d]  根骨(con):[%d]  悟性(int):[%d]  灵性(spi):[%d]\n",
		_attrs["str"], _attrs["con"], _attrs["int"], _attrs["spi"]);
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	if(!num) printf(HIG"你现在吃下新天赋即生效。\n"NOR);
	return num;
}

int do_set(string arg)
{
	string str;
	int num;
	if(!stringp(arg) || sscanf(arg, "%s %d", str, num) != 2) 
		printf("命令格式：set 天赋 点数\n");
	else if(!_tab[str]) 
		printf("无效的天赋。\n");
	else if(num < 10 || num > 30) 
		printf("天赋值只能介于10-30之间。\n");
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
		printf("你设定的天赋点数和自身天赋点数不吻合。\n");
		return 1;
	}
	
	message_vision(HIG"$N吞下一颗$n"HIG"，顿觉脱胎换骨。\n" NOR, who, _this);

	foreach(string id, int k in _attrs) {
		who->set(id, k);
	}
	
	destruct(_this);
	return 1;
}
