// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit ITEM;
inherit F_LIQUID;

#define NAME0		HIG"����յ"NOR
#define NAME1		HIG"���Ƶ�����յ"NOR
#define YUDI		"break_zhan_yudi"

void create()
{
	set_name(NAME0, ({"liuli zhan", "zhan"}));
	set_weight(70);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һֻ�⻪���������յ������İ�֮��𶯡�\n");
		set("unit", "ֻ");
		set("value", 20);
		set("no_sell", 1);
		set("max_liquid", 15);
	}

	set("liquid", ([
		"type": "alcohol",
		"name": "�ɾ�",
		"remaining": 15,
		"drunk_apply": 6,
	]));
}

void debut()
{
	_this->set("name", NAME0);
	_this->move("/d/dntg/sky/lingxiao");
}

/*****************************ת�����*****************************/

void init()
{
	add_action("do_drop", ({"drop"}));
	add_action("do_say", ({"say"}));
}

int do_drop(string arg)
{
	if(_this->query("name") == NAME0 
		&& !cannot_move(_player)
		&& REI_D->precondition(_player)
		&& (arg == "liuli zhan" || arg == "zhan"))
	{
		object env = environment(_player);
		object yudi = present("yuhuang dadi", env);
		if(yudi) {
			msv(CYN"$N����һֻ$n������һ������������\n"NOR, _player, _this);
			
			_this->set("name", NAME1);
			_this->move(env);
			
			yudi->command("angry " + _player->query("id"));
			msv(CYN"$N�ȵ����㾹�Ҵ����޵�����յ�����֪�\n"NOR, yudi);

			_player->set_temp(YUDI, yudi);
		}
	}
}

int do_say(string arg)
{
	object yudi = _player->query_temp(YUDI);
	if(same_env(_player, yudi)) {
		if(arg == "��֪��" || arg == "��֪") {
			msv(CYN"$N˵����" + arg + "\n"NOR, _player);
			msv(CYN"$N��Ȼ��ŭ�����󵨿�ͽ����Ȼ������ͥ��أ��Ǿ�ȥ�½����������ɣ�\n"NOR, yudi);
			//yudi->command("chat ");
			msv("ֻ��������������������ʿ�����ְ˽ŵ�����$N���˳�ȥ��\n", _player);
			_player->move("/d/dntg/sky/qianyuangong");
			tell_room(environment(_player), "ֻ��" + _player->query("name") + "���������ĵ����˳�����\n", ({_player}));
			msv("������ʿ���һ������ȥ��$N���ӻ����½硣\n",_player);
			REI_D->to_earth(_player);
			return 1;
		} else {
			yudi->command("heng");
			msv(CYN"$N������Ĺ��㣡\n"NOR, yudi);
		}
	}
	_player->set_temp(YUDI, 0);
	return 0;
}

