// by firefox 02/21/2010
// 帮派模板

#include <xyj_x.h>
#include <ansi.h>

inherit F_DATA_OF;
inherit F_FOT;


#define GANG_JOIN		"g_join"

#define LEADER			0
#define VLEADER			1
#define TEAM_LEADER		2
#define MUMBER			3

static string* _ranks = ({"帮主", "副帮主", "堂主", "帮众"});
static mapping _props;			//帮派属性

//帮派信息样板
void create()
{
	_props = ([
		"id"		: "ftb",
		"name"		: "斧头帮",
		"color"		: HIW,
		"location"	: "城西饮马峪",
		"slogan"	: "山贼，有前途的职业！",
		
		"npc"		: ([
		]),

		"street"	: ([
			"short"		: "崖顶",
			"long"		: "\n山顶树木繁茂苍翠，崖下是寂静幽深的山谷，北面一条小路，蜿蜒\n通向一处山寨。\n\n",
		]),

		"leave"		: ([
			"dst"	: "/d/westway/yinma",
			"verb"	: "down",
			"msg1"	: "$N不顾一切地纵身跳下悬崖。",
			"msg2"	: "随着一声惨叫，$N从山顶上滚了下来，如同一滩鼻涕甩在地面。",
		]),

		"arrive"		: ([
			"dst"	: "/d/westway/yinma",
			"msg1"	: "$N攀着藤条，向山崖上爬去。",
			"msg2"	: "$N从崖下爬了上来，灰头土脸，满山草屑。",
		]),
	]);
}


/********************************基础函数***********************************/

int setup()
{
	set_data_prop(GANG_PROP);
}

//获取属性
mixed query(string prop)
{
	return _props[prop];
}

//设置属性
void set(string prop, mixed value)
{
	_props[prop] = value;
}

//帮派名称
string name()
{
	return _props["color"] + _props["name"] + NOR;
}

//是否是本帮成员
int is_mumber(object who)
{
	return data_of(who, "id") == _props["id"];
}

//是不是本帮高管
int is_executive(object who)
{
	mapping m = data_of(who);
	return m && m["id"] == _props["id"] && m["rank"] <= VLEADER;
}

//获取所有成员
object* mumbers()
{
	object* arr = ({});
	foreach(object user in children("/obj/user")) {
		if(is_mumber(user))	arr += ({ user });
	}
	return arr;
}

//获取公会房间
object_f room(string name)
{
	return GANG_DIR + _props["id"] + "/" + name;
}


//发布帮派消息
int msg(string msg)
{
	foreach(object who in mumbers()) {
		tell_object(who, msg);
	}
	return 1;
}


//设置头衔
varargs int set_title(object who, string title)
{
	mapping m = data_of(who);
	m["title"] = title ? title : _ranks[m["rank"]];
	who->set("title", m["color"] + m["name"] + " " + m["title"] + NOR);
	return 1;
}

/********************************xxxx应函数***********************************/

//接收成员
int recruit(object who, int rank)
{
	mapping m = ([
		"id"	: _props["id"],
		"name"	: _props["name"],
		"color"	: _props["color"],
		"rank"	: rank,
	]);
	who->set(GANG_PROP, m);
	set_title(who);
	return 1;
}

//移除成员
int expel(object who)
{
	mapping m = data_of(who);
	if(m && m["rank"] != LEADER) {
		msg(HIY + name_id(who) + "离开了帮会。\n"NOR);
		who->set("title", m["name"] + "叛徒");
		who->delete(GANG_PROP);
		return 1;
	}
	return 0;
}

//进入帮派驻地
int enter(object who)
{
	mapping m = query("arrive");
	string room = base_name(environment(who));

	if(room == m["dst"]) {
		message_vision(HIC + m["msg1"] + "\n\n"NOR, who);
		who->move(room("street"));
		if(!who->is_busy()) who->start_busy(3);
		message_vision(HIC"\n" + m["msg2"] + "\n"NOR, who);
		return 1;
	}
	return 0;
}



//帮派内交流
int talk(object who, string msg)
{
	if(!msg) msg = "...";
	msg = HIY"【帮派】" + name_id(who) + "：" + msg + NOR"\n";
	msg(msg);

	return 1;
}

//改变某人等级
int chg_rank(object me, object who, int level)
{
	mapping g1 = GANG->data(me);
	mapping g2 = GANG->data(who);

	if(g1 && g1["rank"] <= VLEADER
		&& g2 && g1["id"] == g2["id"]
		&& g2["rank"] > g1["rank"])
	{
		g2["rank"] += level;
		if(g2["rank"] > MUMBER) g2["rank"] = MUMBER;
		set_title(who);
		if(g2["rank"] == LEADER) {	//帮主让位
			g1["rank"] += 1;
			set_title(me);
			return 2;
		}
		return 1;
	}
	return 0;
}



/********************************命令相应函数***********************************/

//列出帮派成绩
string* list(object* users)
{
	string* lines = ({});
	
	lines += ({ LINE1 });
	lines += ({ "   门派   玩家                职位          等级 贡献  战功  \n" });
	lines += ({ LINE1 });
	for(int i = 0; i < sizeof(users); ++i) {
		string family = FAMILY->short(users[i]);
		mapping g = GANG->data(users[i]);
		lines += ({
			sprintf("%-3d%-7s%-20s%-14s%-5d%-6d%-6d\n",
				i + 1,
				family ? family : "百姓",
				name_id(users[i]),
				g["title"],
				g["rank"],
				g["score"],
				g["ba"],
			)
		});
	}
	lines += ({ LINE1 });
	return lines;
}

//帮派成员列表
int who()
{
	string* arr = list(mumbers());
	foreach(string line in arr) {
		write(line);
	}
	return 1;
}

//移除帮派成员
int quit(object me)
{
	if(!expel(this_player())) return notify_fail("你不能退出帮派。\n");;
	return 1;
}
	
//玩家申请加入帮会
int join(object me)
{	
	me->set_temp(GANG_JOIN, query("id"));
	write("你申请加入" + query("name") + "。\n");
	msg(HIY + name_id(me) + "申请入帮。\n"NOR);
	return 1;
}

//帮会接受玩家加入申请
int accept(object me, object who)
{		
	mapping g = GANG->data(me);

	if(g["rank"] > VLEADER) return notify_fail("副帮主以上才有权邀请。\n");
	if(!who) return notify_fail("收谁入伙？\n");

	if(GANG->id(who)) return notify_fail("对方已经加入帮会。\n");
	if(who->query_temp(GANG_JOIN) != g["id"]) return notify_fail("对方无意入伙。\n");
	
	recruit(who, MUMBER);	
	msg(HIY + name_id(me) + "同意" + name_id(who) + "加入本帮。\n"NOR);
	who->delete_temp(GANG_JOIN);	
	return 1;
}

//提升帮会成员
int promote(object me, object who)
{
	if(!who) return notify_fail("提升谁？\n");
	else {		
		int ret = chg_rank(me, who, -1);
		string str = ret == 1 ? "提升" : "让位给";
		
		if(!ret) return notify_fail("提升失败。\n");
		return msg(HIY + name_id(me) + str + name_id(who) + "。\n"NOR);
	}
	return 1;
}

//降级帮会成员
int	demote(object me, object who)
{
	if(!who) return notify_fail("降职谁？\n");
	else {
		int ret = chg_rank(this_player(), who, 1);
		if(!ret) return notify_fail("降职失败。\n");
		return msg(HIY + name_id(me) + "降职" + name_id(who) + "。\n"NOR);
	}
	return 1;
}

#define TITLE_MSG			HIY"%s任命%s为%s。\n"NOR

//设置成员头衔
int title(object me, object who, string title)
{
	if(title && sizeof(title) > 10) notify_fail("头衔过长。\n");
	if(!who) notify_fail("设置谁的头衔？\n");
	else {
		mapping g1 = GANG->data(me);
		mapping g2 = GANG->data(who);
			if(g1 && g2 && (g1["id"] == g2["id"])
				&& (g1["rank"] < g2["rank"] || g1["rank"] == 0))
			{
				set_title(who, title);
				return msg(sprintf(TITLE_MSG, name_id(me), name_id(who), title));
			}
	}
	return notify_fail("无法设置头衔。\n");
}

//设置帮会首领
int leader(object who)
{
	if(!who) return notify_fail("设谁为帮会领袖？\n");
	
	recruit(who, LEADER);
	return msg(HIY + name_id(who) + "成为帮会领袖。\n"NOR);
}

/********************************帮派地图函数***********************************/

//设置npc的属性
void npc_setup(object npc, string type)
{
	mapping m = _props["npc"][type];
	mapping db;

	npc->set_name(m["name"], m["ids"]);

	recruit(npc, MUMBER);
	set_title(npc, m["title"]);

	db = npc->query_entire_dbase();		//db没有set前可能为空
	foreach(string k, mixed v in m["props"]) {
		db[k] = v;
	}

	db["str"]		= 500;

	db["max_kee"]	= 50 * K;
	db["max_sen"]	= 50 * K;

	db["max_force"]	= 3 * K;
	db["max_mana"]	= 3 * K;

	db[CEXP]		= 2 * K * K;
	db[DEXP]		= 2 * K * K;

	SKI->set_list2(npc, FAMILY->skills_of(or2(m["family"], "将军府")), 180);

	HP->full(npc);

	npc->setup();

	if(m["cloth"]) npc->carry_object(m["cloth"])->wear();
	if(m["weapon"]) npc->carry_object(m["weapon"])->wield();
}
