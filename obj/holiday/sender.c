
#include <ansi.h>

#define LAMP		    "    ����"HIR"������"NOR"�߸߹��ţ�һ��ϲ������ľ���\n"
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
		//boss->command("chat �������Ϲ˿ͣ�ϲ��������ṩ������" + blank);
	}
}

//������ʱ��
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


