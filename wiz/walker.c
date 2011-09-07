// by firefox 11/21/2009
// 爬虫

#include <xyj_x.h>
#include <ansi.h>

inherit ITEM;


void create()
{
	set_name(HIG"漫步者"NOR, ({ "map pearl", "pearl" }) );
	set("long", "一颗宝珠，可发出map指令。\n");
	set("unit", "颗" );
	set("changed", 1);
}

void init()
{
	if(wizardp(this_player())) {

		add_action("do_map", "map");
	}
}

/*

map
	name
	rooms
		room
			short
			flag(no_fight, no_magic, no_mieyao, in_maze, has_door) 
			exits ([])


迷宫，房间，出口可能变化，门或其他变化。
报告房间不联通，出入不对等。

- 等待桥头
- 特殊指令。
- 去不了，需要背。豹头，将军府梦境。
- 杀/装guard。
- 变身进入。

任务
1.从当前位置到达
	- 确定当前位置
	- 传送，
2.遍历某地图
3.记录房间物品
4.和怪战斗


npc: id,name
obj:id,name, flag(no_give,no_drop, no_put)



*/


mapping _maps = ([]);


mapping _room_props = ([

	"name"			: "short",			//名称

	"out_door"		: "outdoors",		//室外
	"in_water"		: "water",			//水下
	"no_fight"		: "no_fight",		//禁止战斗
	"no_magic"		: "no_magic",		//禁止魔法
	
	"no_mieyao"		: "no_mieyao",		//禁止有怪
]);
	

//随机选择房间，在一张地图上，忽略安全区/密室
object random_room1(string dir)
{
	mapping map = ([ "rooms" : ([]), "gate" : ([]) ]);
	mixed* files = get_dir(dir + "/*.c", -1);
	for(int i = 0; i < sizeof(files); i++) {
		if( files[i][1] > 0 ) {
			object room = load_object(dir + "/" + files[i][0]);
			if(room) {
				mapping r = ([]);
				mapping exits = room->query("exits");
								
				//获取属性
				r["id"] = files[i][0];
				if(room->query_doors()) r["has_door"] = 0;	//有门

				//获取属性/标志
				foreach(string k, string v in _room_props) {
					if(room->query(v)) r[k] = 1;
				}
				
				//出口
				if(exits) {
					mapping e = ([]);
					foreach(string exit, string dst in exits) {
						string file = path_file(dst);
						string dir1 = path_dir(dst);
						if(dir1 == dir)
							e[exit] = file;
						else {
							e[exit] = ({ dir1, file });
							map["gate"][dir1] += ({ r[id], exit });
						}
					}
				}

				
			}
		}
	}
}

			mixed exits;

			query_doors

			if (!room
				|| room->query("no_fight")
				|| room->query("no_magic")
				|| room->query("no_mieyao")
				|| !(exits = room->query("exits"))
				|| sizeof(exits) < 1)
				continue;
			return room;
		}
	}
	return 0;
}


int do_map(string arg)
{
	object env = environment(_player);
	string w = MISC_D->find_place(env);

	write(w + "\n");

	return 1;
}

