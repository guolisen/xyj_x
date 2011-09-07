// by firefox 11/21/2009
// 西游杀-游戏场所

inherit ROOM;

#include "xys.h"
#include "cmds.c"

void create ()
{
	set("short", "西行幻境");
	set("long", "这是梦境中的一个虚拟场景，仿佛是在西行路上。\n");

	set("no_fight", 1);
	set("no_magic", 1);

	seteuid(getuid());

	setup();
}

void init()
{
	add_action("do_ready", ({"ready"}));
	add_action("do_leave", ({"leave"}));

//	add_action("do_kickout", "kickout");		//踢出某人
	add_action("do_start", "start");			//玩家就绪后，由主公启动
	
	add_action("do_top", "top");				//在线排名
	
	add_action("do_look", "look");				//大家状态
	add_action("do_hp", "hp");					//自身状态
	add_action("do_inventory", "inventory");	//显示手牌	
	add_action("do_skills", "skills");			//自身技能
	
	add_action("do_equip", "equip");			//装备一件装备
	add_action("do_unequip", "unequip");		//卸下一件装备

	add_action("do_use", "use");				//出牌/使用牌
	add_action("do_discard", "discard");		//弃牌

	if(wizardp(_player))
		add_action("do_stat", "stat");			//查看身份，战绩
}


mixed* _players = ({});

int _round = 0;
int _turn = -1;


//入场选手宣布就绪
int do_ready(string arg)
{
	if(_round > 0) return notify_fail("比赛已经开始了。\n");

}

//入场选手离开
int do_leave(string arg)
{
	if(_round > 0) return notify_fail("比赛进行中，不能离开。\n");

}
