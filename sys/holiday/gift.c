
#include <ansi.h>

#define LAMP		    "    ����"HIR"������"NOR"�߸߹��ţ�һ��ϲ������ľ���\n"
#define PROP			"holiday/gift"

string* _rooms = ({
	"/d/huanggong/baiyujie",
	"/d/city/ximen",
	"/d/city/dongmen",
	"/d/changan/nanchengkou",
});

mapping _ip_num = ([]);

void create()
{
	seteuid(getuid());
	set_heart_beat(300);
}

object find(string room, string file)
{
	object r = load_object(room);
	return r->query_temp("objects")[file];
}

mixed give_me(object xue)
{
	object who = this_player();
	
	if(!userp(who)) return 0;
	else {
		string ip = query_ip_number(who);
		int exp = who->query("combat_exp") + who->query("daoxing");
		
		if(_ip_num[ip]) {
			tell_object(who, HIR"�װ�����ң�ÿIPֻ����һ���͡�\n"NOR);
			return 0;
		}
		if(exp < 40000) {
			tell_object(who, HIR"�����Ϊ̫�͡�\n"NOR);
			return 0;
		}
		if(who->query(PROP)) {
			//tell_object(who, HIR"��õ��Ĺ����ˡ�\n"NOR);
			return 0;
		}
		else {
			object ob = new(__DIR__"hongbao");
			if(ob->move(who)) {
				who->set(PROP, 20101001);
				_ip_num[ip]++;
				message_vision(CYN"$N��$n˵����ʥ��������ͬ�أ���������㡣\n"NOR, xue, who);
				message_vision("$N��$nһ��"HIR"����"NOR"��\n", xue, who);
			} else {
				tell_object(who, "��Я���Ķ���̫���ˡ�\n");
				destruct(ob);
			}
		}
	}
	return 1;
}

object _table;

void say_sth()
{
	string blank = random(2) ? "" : " ";

	if(random(2)) {
		object bug = find("/d/city/xifuhui", "/d/city/npc/boss");
		if(!_table) {
			_table = new(__DIR__"table");
			_table->move("/d/city/xifuhui");
		}
		if(bug) {
			bug->command("chat �������Ϲ˿ͣ�ϲ��������ṩ������" + blank);

			bug->set("chat_chance", 10);
			bug->set("chat_msg", ({
				bug->name() + "˵������ѹ��ڵģ���ë�ĺ������������\n",
				bug->name() + "˵�������������������ˣ������͸�˳ˮ���顣\n", })
			);
		}
	} else {
		object xue = find("/d/huanggong/damen", "/d/huanggong/npc/xuerengui");
		if(xue) {
			xue->command("chat �������������ͬ�죻��������ʥ�����͡�" + blank);
			xue->set("inquiry/����", (: give_me :));
		}
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
