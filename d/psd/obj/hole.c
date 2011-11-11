// by firefox 11/21/2009

inherit ITEM;

#include <xyj_x.h>
#include <ansi.h>

#define DEST		X_DIR"d/psd/yard"

void create()
{
	set_name("���ϵĶ�", ({"hole"}));
	set("env/invisibility", 1);
	set("value", 1);
	set("no_get", 1);
	set("no_give", 1);

	set("has_box", 1);
	
	seteuid(getuid());
	setup();
}

/*****************************�¹ⱦ��*****************************/

void init()
{
	add_action("do_dig", ({"dig", "wa"}));
}

int do_dig(string arg)
{
	string* items = ({
		({ "һ������",	"/d/southern/jinghe/obj/qiuyin" }),
		({ "һֻ����",	__DIR__"yg-box" }),
	});
	int i = query("has_box");

	if(!can_move(_player)) return notify_fail("����æ�ţ�\n");	

	_player->start_busy(1);

	if(random(3)) {
		msv(CYN"$N����������ϵĸ���......\n"NOR, _player);
	}
	else if(present("yueguang baohe", _player)) {
		msv(CYN"һ��ǿ��������ӵ��´�������$NӲ�������˽�ȥ��\n"NOR, _player);
		_player->move(DEST);
		msv(CYN"���������$N���ڵ��ϡ�\n"NOR, _player);
	} else {
		object ob = new(items[i][1]);
		if(ob->move(_player)) {
			msv(CYN"$N�ڵ���" + items[i][0] + "��\n"NOR, _player);
			set("has_box", 0);
		}
	}
	return 1;
}

/*****************************�Ĵ�����*****************************/

string* rooms = ({
	"/d/dntg/hgs/shifang",
	"/d/dntg/hgs/shifang",
});

void debut()
{
	set("has_box", 1);
	_this->move(random1(rooms));
}

