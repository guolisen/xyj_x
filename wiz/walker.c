// by firefox 11/21/2009
// ����

#include <xyj_x.h>
#include <ansi.h>

inherit ITEM;


void create()
{
	set_name(HIG"������"NOR, ({ "map pearl", "pearl" }) );
	set("long", "һ�ű��飬�ɷ���mapָ�\n");
	set("unit", "��" );
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


�Թ������䣬���ڿ��ܱ仯���Ż������仯��
���淿�䲻��ͨ�����벻�Եȡ�

- �ȴ���ͷ
- ����ָ�
- ȥ���ˣ���Ҫ������ͷ���������ξ���
- ɱ/װguard��
- ������롣

����
1.�ӵ�ǰλ�õ���
	- ȷ����ǰλ��
	- ���ͣ�
2.����ĳ��ͼ
3.��¼������Ʒ
4.�͹�ս��


npc: id,name
obj:id,name, flag(no_give,no_drop, no_put)



*/


mapping _maps = ([]);


mapping _room_props = ([

	"name"			: "short",			//����

	"out_door"		: "outdoors",		//����
	"in_water"		: "water",			//ˮ��
	"no_fight"		: "no_fight",		//��ֹս��
	"no_magic"		: "no_magic",		//��ֹħ��
	
	"no_mieyao"		: "no_mieyao",		//��ֹ�й�
]);
	

//���ѡ�񷿼䣬��һ�ŵ�ͼ�ϣ����԰�ȫ��/����
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
								
				//��ȡ����
				r["id"] = files[i][0];
				if(room->query_doors()) r["has_door"] = 0;	//����

				//��ȡ����/��־
				foreach(string k, string v in _room_props) {
					if(room->query(v)) r[k] = 1;
				}
				
				//����
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

