
#include <ansi.h>

#define LAMP		    "    两侧"HIR"大红灯笼"NOR"高高挂着，一派喜气洋洋的景象。\n"
#define PROP			"holiday/gift"

string* _rooms = ({
	"/d/huanggong/baiyujie",
		"/d/city/ximen",
		"/d/city/dongmen",
		"/d/changan/nanchengkou",
});

void create()
{
	seteuid(getuid());
	set_heart_beat(3);
}

object find(string room, string file)
{
	object r = load_object(room);
	return r->query_temp("objects")[file];
}

object _table;

void say_sth()
{	
	object boss = find("/d/city/xifuhui", "/d/city/npc/boss");
	if(!_table) {
		_table = new(__DIR__"table");
		_table->move("/d/city/xifuhui");
	}
	if(boss) {
		string blank = random(2) ? "" : " ";
		//boss->command("chat 回馈新老顾客，喜福会免费提供胡饼。" + blank);
	}
}

//触发定时器
void heart_beat()
{
	foreach(string room in _rooms) {
		if(!room->query("holiday")) {
			room->set("holiday", 1);
			room->add("long", LAMP);
		}
	}
	say_sth();
}


