// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit ROOM;
inherit F_CMD;
inherit F_MOVE_TO;

#define MOVE_ACT				"move_act/"


void create ()
{
	set("short", "����");
	set("long", "��������\n");

	set("in_bg", 1);

	set("exits", ([]));

	setup();
}

void init()
{
	//init hook
	ALX->room_init(_this, _player);

	//����ɳ�е�����
	filter_cmd();

	//�ƶ�
	add_action("do_dive", "dive");
	add_action("do_climb", "climb");
	add_action("do_jump", "jump");
	
	add_action("do_m", "m");
	add_action("do_bg", "bg");	
	
	//����ָ��
	add_action("do_cast", "cast");	
	add_action("do_burn", "burn");	
}

int do_move(string type, string arg, string msg1, string msg2)
{
	object player = this_player();
	object room;
	string prop = MOVE_ACT + type;

	string msg = BTL->bad_state(player, ({ "busy", "no_move" }));
	if(msg) return notify_fail("��" + msg + "��\n");

	if(arg) prop += "/" + arg;
	room = query(prop);
	if(objectp(room)) {
		message_vision(msg1, player);
		player->move(room);
		message_vision(msg2, player);
		return 1;
	}
	return 0;
}

int do_dive(string arg)
{
	return do_move("dive", arg, 
		HIC"$NһԾ��������ˮ��\n"NOR,
		HIC"��ͨһ����$N�����ںӵס�\n"NOR
	);
}

int do_climb(string arg) 
{
	return do_move("climb", arg,
		HIC"$N���㲢����������\n"NOR,
		HIC"$Nͷ��ˮ�ݣ�������Ƽ�����ڰ��ߡ�\n"NOR
	);
}

int do_jump(string arg)
{
	int ret = do_move("jump", arg,
		HIC"$N����һ�е��������¡�\n"NOR,
		HIC"$N�����������ͬһ̲����˦�ڵ��档\n"NOR
	);
	if(ret)	this_player()->receive_wound("kee", 2000);
	return ret;
}

int do_m(string arg)
{

	return ALX->cmd_show_map(_player);
}

int do_bg(string arg)
{
	
	return ALX->cmd_bg(arg);
}

/*
int valid_leave (object who, string dir)
{
	return ALX->room_leave(_this, who, dir);
}*/

int do_block(string arg)
{
	return 1;
}

int clean_up()
{
	return 0;
}

void alternative_die(object who)
{
	ALX->room_sb_die(_this, who);
}

int do_cast(string arg)
{
	string* arr = ({"chuqiao", "townportal", "escape", "tudun", "shuidun"});
	if(member_array(arg, arr) != -1) 
		return notify_ok("����ս�����ܵ�������������\n");
	return 0;
}

int do_burn(string arg)
{
	object ob = arg ? present(arg, this_player()) : 0;

	if(ob && ob->query("id") == "escape seal")
		return notify_ok("����ս�����ܵ�������������\n");
	return 0;
}