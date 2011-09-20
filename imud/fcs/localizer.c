// by firefox 04/16/2011
// iFCS本地化文件

#include <imud-efun.h>

mapping _db = ([
	"prop_root"		: "imud/fcs",				//属性根节点
	"ROE"			: (500*10000/1000),			//汇率，玩家平均日收入换1K筹码
	
	"dealer"		: (["id" : "dealer", "name" : "发牌女郎", "title" : "侍者"]),
	"desk_name"		: "桌边",
	"desk_desc"		: "\n这是一张考究的桌子，光洁的桌面上泛着红木特有的幽暗光芒。四下几\n"
					  "把大气的椅子，衬托出庄重的气氛。桌边有：\n\n",
	"stand_name"	: "大厅",
	"stand_desc"	: "\n宽敞明亮的大厅，装饰得金碧辉煌。四周则是一排排椅子，场中间一张\n"
					  "气派的紫檀木大桌。桌边有：\n\n",
	"corridor_name"	: "二楼",
	"corridor_desc"	: "\n楼上显得格外热闹，走廊里人来人往，几间屋子里人声嘈杂，钱币落盘\n"
					  "的声音不绝。看样子，客人们赌得正欢呢。\n\n",
	"exits"			: ([
			"down"		: "/d/qujing/chechi/jiuguan",
	]),
]);

//获取属性
mixed get(string prop)
{
	return _db[prop];
}

/********************************安全保证***********************************/

//设置安全区，避免干扰游戏的战斗
int set_safety(object room)
{
	room->set("no_fight", 1);
	room->set("no_cast", 1);

	room->set("alternative_die", 1);
}

/********************************本地显示***********************************/

//格式化选手信息，用于显示
string format_player(mapping who)
{
	string str = sprintf("  %s %s", who["title"], name_id(who));
	if(who["chip"]) str += "<手边" + who["chip"] + "筹码>";
	return str + "\n";
}

//刷新玩家看到的场景，包括游戏室和看台
int refresh_look(mapping dealer, mapping g, mixed deskside, mixed stand)
{
	string desc = format_player(dealer);
	
	foreach(mapping who in g["players"]) {
		desc += format_player(who);
	}
	desc += "  ----------------------------------\n";
	foreach(mapping who in g["queue"]) {
		desc += format_player(who);
	}
	desc +="\n";

	deskside->set("short", get("desk_name"));
	deskside->set("long", get("desk_desc") + desc);
	if(stand) {
		stand->set("short", get("stand_name"));
		stand->set("long", get("stand_desc") + desc);
	}
}

//桌边的玩家看到的信息
int deskside_look(object room)
{
	write(room->query("short") + " -\n");
	write(room->query("long"));
	return 1;
}

//初始化走廊，设置好与外界的出入口
void setup_corridor(object room)
{
	room->set("short", get("corridor_name"));
	room->set("long", get("corridor_desc"));
	room->set("exits", get("exits"));
	set_safety(room);
}

/********************************筹码兑换***********************************/

//换筹码
int exchange_chip(object who, int amount)
{
	int n = amount * get("ROE");
	if(who->query("balance") >= n) {
		who->add("balance", -n);
		who->save();
		return 1;
	}
	write("银行存款不足。\n");
	return 0;
}

