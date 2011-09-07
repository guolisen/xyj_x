// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit F_ELEMS;
inherit F_DBASE;


#define WATER_FLAG		"water"
#define MOVE_ACT		"move_act/"

#define dr_en			DIRECTION->en
#define dr_offset		DIRECTION->offset
#define dr_opp			DIRECTION->opp

#define camp_id_		ALX->camp_id

object* rooms = ({});

mapping land = ([]);
mapping water = ([]);

void create()
{
	set("name", "��ͼ��");
	set("short", "��ͼ��");
}


//��ѯ�����ϵķ���
object at(int x, int y)
{
	object room;
	if(mapp(land[x])) room = land[x][y];
	//if(!room) printf("no room at (%d, %d)\n", x, y);
	return room;
}

//��ѯ����ˮ���ϵķ���
object at_water(int x, int y)
{
	object room;
	if(mapp(water[x])) room = water[x][y];
	//if(!room) printf("no water room at (%d, %d)\n", x, y);
	return room;
}

void to(int x, int y)
{
	object room = at(x, y);
	if(room) this_player()->move(room);
}

void to_water(int x, int y)
{
	object room = at_water(x, y);
	if(room) this_player()->move(room);
}


//���ö���һ������
void set_attr(object obj, mapping info) {
	foreach(mixed k, mixed v in info) {
		obj->set(k, v);
	}
}

void show_room(string msg, object room)
{
	printf("%s %s(%d,%d)\n",
		msg,
		room->query("short"), 
		room->query("pos")[0],
		room->query("pos")[1]
	);
}

//��ͨroom
void connct_room(object room1, object room2, string dir)
{
	object r = room1->query("exits/" + dr_en(dir));
	if(objectp(r) && r != room2) {
		printf("connect err:\n");
		show_room("r1", room1);
		show_room(dr_en(dir), room2);
	}
	room1->set("exits/" + dr_en(dir), room2);
}

//���һ������
varargs object add_room(mapping area, int x, int y, mapping info)
{
	object room;
	if(!mapp(area[x])) area[x] = ([]);
	room = area[x][y];

	if(!room) {			//������room
		room = new_elem(__DIR__"room");
		set_attr(room, info);
		room->set("long", "\n" + info["long"]);
		room->set("pos", ({x, y}));
		room->set("name", info["short"]);
		room->set("alternative_die", 1);
		area[x][y] = room;
		show_room("new:", room);
		rooms += ({room});		
		room->move_to(this_object());
	} else {
		show_room("find:", room);
	}
	return room;
}

object add_rooms(mapping area, mapping rooms)
{
	foreach(mapping info, int* pos in rooms) {
		add_room(area, pos[0], pos[1], info);
	}
}



//����һ��path�ϵ�����room
void add_path(mapping area, int x, int y, string path, mapping info)
{
	object room1 = add_room(area, x, y, info);

	foreach(string str in STRING->split(path, ';')) {
		int rep;
		string direction;

		if(sscanf(str, "%d%s", rep, direction) != 2) {
			rep = 1;
			direction = str;
		}
		for(int i = 0; i < rep; ++i) {
			object room2;
			x += dr_offset(direction)[0];
			y += dr_offset(direction)[1];
			room2 = add_room(area, x, y, info);
			connct_room(room1, room2, direction);
			connct_room(room2, room1, dr_opp(direction));
			room1 = room2;
		}
	}
}

void add_road(mapping area, mapping road)
{
	foreach(mapping info, mapping list in road) {
		foreach(int* xy, string path in list) {
			add_path(area, xy[0], xy[1], path, info);
		}
	}
}

//�����ƶ�����
void set_move(object from, object to, string act)
{
	from->set(MOVE_ACT + act, to);
}

//����ˮ½����
varargs void water_land(int* river_pos, int* bank_pos1, int* bank_pos2)
{
	string sound = "    ��Լ��������ˮ����\n\n";
	string b1 = "    ���߷������¡�����������\n\n";
	string b2 = "    �����������¡�����������\n\n";
	object river = at_water(river_pos[0], river_pos[1]);

	object bank = at(bank_pos1[0], bank_pos1[1]);
	set_move(bank, river, "dive");
	bank->set("long", bank->query("long") + sound);

	if(!bank_pos2) {	//һ��
		river->set("long", river->query("long") + b1);
		set_move(river, bank, "climb");
	} else {			//����
		object bank2 = at(bank_pos2[0], bank_pos2[1]);
		set_move(bank2, river, "dive");
		bank2->set("long", bank2->query("long") + sound);

		river->set("long", river->query("long") + b2);
		set_move(river, bank, "climb/south");
		set_move(river, bank2, "climb/north");		
	}
}



//���Ƶ�ͼ
int draw(mapping map)
{
	//����
	if(map["river"]) {
		foreach(mapping info in keys(map["river"])) {
			info[WATER_FLAG] = 1;
		}
		add_road(water, map["river"]);
	}

	//�ݵ�
	if(map["fort"])	{
		foreach(mapping info in keys(map["fort"])) {
			info["short"] = HIY + info["short"] + NOR;
			info["no_change"] = 1;	//��ֹ�ͷ�����
		}
		add_rooms(land, map["fort"]);
	}

	//����
	if(map["bridge"]) {
		add_rooms(land, map["bridge"]);

		//���Ӻ���������
		foreach(int* xy in values(map["bridge"])) {
			object r1 = at(xy[0], xy[1]);
			object r2 = at_water(xy[0], xy[1]);
			if(!r1 || !r2) {
				printf("����ˮ�����Ӵ���");
			} else {
				r1->set(MOVE_ACT + "dive", r2);
			}
		}
	}

	//��·
	if(map["road"]) add_road(land, map["road"]);
	
	return sizeof(rooms);
}

//������Ϊ(ox,oy)���߳�Ϊ2n + 1�����η�Χ�����ѡ�񷿼�
object random_room(int ox, int oy, int n)
{
	object* arr = ({});	//��㼯��

	for(int y = oy - n; y <= oy + n; ++y) {
		for(int x = ox - n; x <= ox + n; ++x) {
			object r = at(x, y);
			if(r) arr += ({r});
			r = at_water(x, y);
			if(r) arr += ({r});
		}
	}
	return arr[random(sizeof(arr))];
}

//���һ������
object random_room1()
{
	return random1(rooms);
}

//�����������
void blow(object who, int radius, int busy)
{
	int* xy = environment(who)->query("pos");
	object room = random_room(xy[0], xy[1], radius);

	msv(YEL"\n��Ȼһ��Ʒ��Х������$N���ɼ������˽�ȥ��\n"NOR, who);
	who->move(room);
	msv(YEL"$N���ص�һ��ˤ�ڵ��ϣ����ζ������á�\n"NOR, who);
	if(!who->is_busy()) who->start_busy(busy);
}

private string room_str(object who, object room, string color)
{
	int camp_index = 0;
	string* colors = ({ HIY, HIG, HIR });
	if(!room) return "  ";
	foreach(object user in all_inventory(room)) {
		if(userp(user)) {
			if(user == who) return BLINK + colors[camp_id_(who)] + "��"NOR;
			if(!camp_index) camp_index = camp_id_(user);				//����������Ӫ
			else if(camp_id_(user) != camp_index) return HIW"��"NOR;		//�෽
		}
	}
	if(camp_index) return colors[camp_index] + "��"NOR;
	return color + "��"NOR;
}

//��ʾ��ͼ
void show_map(object who, int width, int height)
{
	write(LINE1);
	for(int y = 0; y < height; ++y) {
		string line = "";
		for(int x = 0; x < width; ++x) {
			object room = at(x, y);
			if(room) line += room_str(who, room, YEL);
			else {
				room = at_water(x, y);
				line += room_str(who, room, HIB);
			}
		}
		tell_object(who, line + "\n");
	}
	write(LINE1);
}
/*
todo:�����Ż�map����ʾ�����ֲ�����
string* _map_lines;
object* _map_rooms;

//��ʾ��ͼ
void show_map1(object who, int width, int height)
{
	if(!_map_lines) {
		_map_lines = ({});
	}
	write(LINE1);
	for(int y = 0; y < height; ++y) {
		string line = "";
		for(int x = 0; x < width; ++x) {
			object room = at(x, y);
			if(room) line += room_str(who, room, YEL);
			else {
				room = at_water(x, y);
				line += room_str(who, room, HIB);
			}
		}
		tell_object(who, line + "\n");
	}
	write(LINE1);
}
*/

string stat()
{
	object* tab = rooms - ({0});
	return "rooms: " + sizeof(tab) + "/" + sizeof(rooms);
}

