#include <ansi.h>
#include <xyj_x.h>

inherit F_CLEAN_UP;

#define SIZE		20
#define INTERVAL	911

#define	ID			0
#define	TITLE		1
#define	OBJ			2
#define	TIME		3
#define	LIST		4

mixed* _tops = ({
	({ "gs",	"实力榜",				"uforce",	0, 0}),
	({ "pt",	"实力榜-普陀",		"uforce",	0, 0}),
	({ "fc",	"实力榜-方寸",		"uforce",	0, 0}),
	({ "wzg",	"实力榜-五庄观",		"uforce",	0, 0}),
	({ "moon",	"实力榜-月宫",		"uforce",	0, 0}),

	({ "jjf",	"实力榜-将军府",		"uforce",	0, 0}),
	({ "lg",	"实力榜-龙宫",		"uforce",	0, 0}),
	({ "hell",	"实力榜-地府",		"uforce",	0, 0}),
	
	({ "xs",	"实力榜-雪山",		"uforce",	0, 0}),
	({ "wdd",	"实力榜-无底洞",		"uforce",	0, 0}),
	({ "hyd",	"实力榜-火云洞",		"uforce",	0, 0}),
	({ "psd",	"实力榜-盘丝洞",		"uforce",	0, 0}),
	
	//"skill"		: ({ "高手技能榜",		"uforce",	0}),
	
	({ "rich",	"富豪榜",				"udata",	0, 0}),
	({ "killer","杀手榜",				"udata",	0, 0}),
	({ "nk",	"NK榜",				"udata",	0, 0}),
	({ "mieyao","灭妖榜",				"udata",	0, 0}),
	({ "quest",	"解谜榜",				"udata",	0, 0}),
	({ "age",	"寿星榜",				"udata",	0, 0}),
	({ "wx",	"武学榜",				"udata",	0, 0}),
	({ "dx",	"道行榜",				"udata",	0, 0}),
	({ "force",	"内力榜",				"udata",	0, 0}),
	({ "mana",	"法力榜",				"udata",	0, 0}),
	({ "kee",	"气血榜",				"udata",	0, 0}),
	({ "sen",	"精神榜",				"udata",	0, 0}),
	({ "stl",	"狮驼岭功勋榜",		"udata",	0, 0}),

	({ "mp",	"门派流行榜",			"stat",		0, 0}),
	({ "sforce","内功流行榜",			"stat",		0, 0}),
	({ "spells","法术流行榜",			"stat",		0, 0}),
	({ "dodge",	"轻功流行榜",			"stat",		0, 0}),
	({ "wq",	"武器流行榜",			"stat",		0, 0}),
	({ "tf",	"天赋流行榜",			"stat",		0, 0}),
	
	/*


	
	"zj"		: ({ "stl",			"狮驼岭战绩榜" }),*/
	
	/*"bang"		: ({ "bang",		"帮会战绩榜" }),
	"weapon"	: ({ "bang",		"兵器谱" }),
	"pat"		: ({ "pat",			"神兽榜" }),
	"pat"		: ({ "pat",			"神兵榜" }),

	"star"		: ({ "special",		"明星榜" }),		//第一色狼，登徒子，柳下惠，第一流氓，战神，
	*/
});

mixed* find(string id)
{
	if(!id) id = "gs";
	foreach(mixed* arr in _tops) {
		if(arr[ID] == id) return arr;
	}
	return 0;
}


int main(object me, string arg)
{
	mixed* info = find(arg);
	object_f ob;
	mapping list;

	if(!info) return notify_fail("指定的榜单不存在。\n");
	if(!cd_start(me, "cmd", 5)) return notify_fail("请不要连续使用该指令。\n");

	ob = X_DIR"cmds/top/" + info[OBJ];

	//刷新数据
	if(info[TIME] + INTERVAL < time()) {
		info[LIST] = ob->query(info[ID], SIZE);
		info[TIME] = time();
	}

	//获取并显示数据
	list = info[LIST];
	write(info[TITLE] + "：\n" + LINE1);
	write(list["header"]);
	write(NOR + LINE1);
	foreach(string line in list["lines"])
		write(line);
	write(NOR + LINE1);

	return 1;
}

int help(object me)
{
	write("指令格式 : top [榜单缩写]\n\n可选缩写如下：\n");
	
	foreach(mixed* arr in _tops)
		printf("    %-10s      %s\n", arr[ID], arr[TITLE]);
    return 1;
}

