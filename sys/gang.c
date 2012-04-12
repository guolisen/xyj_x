// firefox 02/21/2010
// 帮会集合

#include <xyj_x.h>
#include <ansi.h>

string* _elems = ({
	"ftb", "shenzhou", "taishan", "haili", "buduo", "lushan", "szcg", "cangyue",
	"dongxing", "huisuo", "xiaoyao"
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
int try_enter(object who)
{
	foreach(object g in elems()) {
		if(g->enter(who)) return 1;
	}
	return 0;
}

//返回帮会老巢
string home(object me)
{
	mapping g = data(me);

	if(g) return GANG_DIR + g["id"] + "/yard";
	return 0;

}
