
#include <ansi.h>

#define LAMP		    "    两侧"HIR"大红灯笼"NOR"高高挂着，一派喜气洋洋的景象。\n"
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
			tell_object(who, HIR"亲爱的玩家，每IP只能领一次赏。\n"NOR);
			return 0;
		}
		if(exp < 40000) {
			tell_object(who, HIR"你的修为太低。\n"NOR);
			return 0;
		}
		if(who->query(PROP)) {
			//tell_object(who, HIR"你得到的够多了。\n"NOR);
			return 0;
		}
		else {
			object ob = new(__DIR__"hongbao");
			if(ob->move(who)) {
				who->set(PROP, 20101001);
				_ip_num[ip]++;
				message_vision(CYN"$N对$n说道：圣上与万民同贺，这个赏与你。\n"NOR, xue, who);
				message_vision("$N给$n一个"HIR"红封袋"NOR"。\n", xue, who);
			} else {
				tell_object(who, "你携带的东西太多了。\n");
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
			bug->command("chat 回馈新老顾客，喜福会免费提供胡饼。" + blank);

			bug->set("chat_chance", 10);
			bug->set("chat_msg", ({
				bug->name() + "说道：快把过期的，长毛的胡饼都搬出来！\n",
				bug->name() + "说道：过了中秋卖不掉了，不如送个顺水人情。\n", })
			);
		}
	} else {
		object xue = find("/d/huanggong/damen", "/d/huanggong/npc/xuerengui");
		if(xue) {
			xue->command("chat 万邦来朝，普天同庆；恩泽万民，圣上有赏。" + blank);
			xue->set("inquiry/领赏", (: give_me :));
		}
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
