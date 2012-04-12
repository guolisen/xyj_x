// by firefox 06/21/2010

#include <xyj_x.h>
#include <ansi.h>

#define RACE_PROP		XYJ_X"/race"	//种族属性
#define BUFF_ID			"zhenshen2"
#define BUFF_NAME		"真身"
#define CD				10


//各种族出现的几率
mapping _races = ([
	"cattle"		: 10,
	"centipede"		: 10,
	"corpse"		: 10,
	"dragon"		: 10,
	"mouse"			: 10,
	"phoenix"		: 10,
	"pig"			: 10,
	"scorpion"		: 10,
	"snake"			: 10,
	"spider"		: 10,
	"tortoise"		: 10,
	"weasel"		: 10,
	"wolf"			: 10,
]);

void create()
{
	seteuid(getuid());
}

//查询目标的种族信息
varargs mixed query(object who, string prop)
{
	mapping m = DB->query_map(who, RACE_PROP);
	return prop ? m[prop] : m;
}

//获取指定ID的种族对象
object_f find(string id)
{
	return id ? (__DIR__ + "race/" + id) : 0;
}

//获取目标的种族对象
object_f race_of(object who)
{
	string id = query(who, "id");
	return find(id);
}

//定制种族
varargs int set(object who, string id, string name, int num)
{
	mapping m = query(who);
	m["id"] = id;
	m["name"] = name;
	m["num"] = or2(num, sizeof(REI_D->query(who)));
}

//给对象设置一个随机物种，返回物种对象
object_f set_random(object who)
{
	string id = roulette(_races);
	object_f race = find(id);

	set(who, id, race->random_name());
	return race;
}

//获取目标种族信息
void info(object who)
{
	mapping m = query(who);
	string name = or2(m["name"], "人类");
	printf("真身：%s 转世次数：%d。\n", name, m["num"]);	
}

//恢复真身
int zhenshen(object who)
{
	object_f race = race_of(who);
	mapping req = ([
		"cd"		: ([ BUFF_ID	: 1 ]),
		"ex_temp"	: ([ "no_wield" : 1, "powerup" : 1, "d_mana" : 1]),
		"ex_class"	: ([ "变身术" : 1 ]),
	]);

	if(!race) return notify_fail("你没有真身状态。\n");
	if(!BTL->require(who, BUFF_NAME, req)) return 1;
	else {
		mapping buff = race->make_buff(who);

		buff["id"]	= BUFF_ID;
		buff["name"]= BUFF_NAME;
	
		MSG->vison(HIC"$N就地一滚，化为一%s。", who, 0, buff["_unit"] + buff["_name"]);

		BUFF->add(who, buff);
		BUFF->start_cd2(who, buff, CD);
	}

	return 1;
}

//定时触发龙的特效
int on_timer(mapping buff)
{
		/*object enemy = query_temp("last_damage_from");
	object weapon;
	if(enemy && weapon = enemy->query_temp("weapon")) {
		damage = weapon->query("weapon_prop/damage");
	}
	//兵器融化，$N的武器仿佛要被$n身上的火焰融化/烧着了set("material", "steel");
	//query("material") != "ice" ) "bone");*/

	return 1;
}

//获取龙的种类与特征
mapping query_trait(object who)
{/*
	mapping m;
	string spells = who->query_skill_mapped("spells");
	if(!spells || !trait[spells]) spells = "misc";
	if(spells == "pingtian-dafa") spells = "taiyi";

	m = trait[spells];
	if(!m["id"]) m["id"] = "dragon";
	if(!m["short"])
		m["short"] = m["color"] + m["name"] + NOR + "(Dragon)";
	return m;*/
}


//变成人身
int human(object who)
{
	mapping buff = BUFF->find(who, BUFF_ID);
	int mana = who->query("max_mana") / 10;

	if(!buff) return notify_fail("你没有处于真身状态。\n");
	if(who->is_busy()) return notify_fail("你正忙着。\n");
	if(mana > who->query("mana")) return notify_fail("你的法力不足以变回人形。\n");
	who->add("mana", -mana);
	msv(HIC"$N摇身一变，化作人形。\n"NOR, who);
	BUFF->remove(buff);
	who->start_busy(1);
	return 1;
}

//施展真身招数
void skill(object who, object target)
{
}

