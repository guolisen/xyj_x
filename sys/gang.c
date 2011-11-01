// by firefox 02/21/2010
// 帮会集合

#include <xyj_x.h>
#include <ansi.h>

string* _elems = ({
	"ftb", "shenzhou", "taishan", "buduo", "lushan", "szcg", "cangyue",
	"dongxing", "xiaoyao"
});

void create()
{
	seteuid(getuid());
}

/********************************目标帮会信息查询***********************************/

//获取目标的帮会信息
mapping data(object who)
{
	return who->query(GANG_PROP);
}

//获取目标的帮会ID
string id(object who)
{
	return who->query(GANG_PROP"/id");
}

//查找帮会对象
object find(string gid)
{
	object g;
	if(member_array(gid, _elems) < 0) return 0;
	return load_object(GANG_DIR + gid);
}

//获取全部帮会对象
object* elems()
{
	object* arr = allocate(sizeof(_elems));
	for(int i = 0; i < sizeof(_elems); ++i) {
		arr[i] = find(_elems[i]);
	}
	return arr;
}

//获取目标的帮会对象
object of(object who)
{
	return find(id(who));
}

//获取目标的帮会名字
string name(object who)
{
	return who->query(GANG_PROP"/name");
}

//判定是否同一帮会，无帮会者算一个帮会
int same(object ob1, object ob2)
{
	return ob1 && ob2 && id(ob1) == id(ob2);
}

/********************************帮会接口***********************************/

//列出所有帮会
int list()
{
	printf(LINE1);
	printf("帮会              位置        来自        主旨\n");
	printf(LINE1);
	foreach(string g in elems()) {
		printf("%s%-18s%-12s%-12s%-20s\n"NOR,
			g->query("color"),
			name_id(g),
			g->query("location"),
			g->query("from"),
			g->query("slogan"),
		);
	}
	printf(LINE1);
	return 1;
}

//尝试从当前位置进入门派
int try_enter(object who, string verb)
{
	foreach(object g in elems()) {
		if(g->enter(who, verb)) return 1;
	}
	return 0;
}

//返回帮会老巢
int home(object me)
{
	mapping g = data(me);

	trace(getuid(me));

	if(!g
		|| me->is_fighting()
		|| me->is_busy()
		|| me->query_temp("pending/exercising")
		|| !(wizardp(me) || environment(me)->query("outdoors"))
		|| me->is_ghost()
		|| me->query_temp("no_move")
		|| me->query("daoxing") < 16000
		|| me->query("max_mana") < 360
		|| me->query("mana") < 200)
	{
		return 0;
	} else {
		string yard = GANG_DIR + g["id"] + "/yard";
		string ridemsg = "";
		object ridee = me->ride();

		if (ridee) {
			ridemsg = ridee->query("ride/msg")+"着"+ridee->name();
			ridee->move(yard);
		}
		message_vision(HIY"$N手一指，召来一朵云彩，高高兴兴地坐了上去，\n"
			"再吹一声口哨，随之往上冉冉地升起。。。\n\n"NOR, me);
		me->add("mana", -20);
		me->move(yard);
		write("\n\n到了！你按下云头跳了下来。\n");
		message_vision(HIY"\n只见半空中降下一朵云彩，$N" + ridemsg + "从里面走了出来。\n"NOR, me);
	}
	return 1;

}
