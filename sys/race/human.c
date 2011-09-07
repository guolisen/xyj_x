// by firefox 11/21/2009

#include "race.h"
/*
青牛


牛王嘻嘻的笑了一笑，现出原身，一只大白牛，头如峻岭，眼若闪光，
两只角似两座铁塔，牙排利刃。
连头至尾，有千余丈长短，自蹄至背，有八百丈高下

那牛王拚命捐躯，斗经五十余合，抵敌不住，败了阵，往北就走。
早有五台山秘魔岩神通广大泼法金刚阻住道：『牛魔，你往那里去！我等乃释迦牟尼佛祖差来，布列天罗地网，至此擒汝也！』
正说间，随后有大圣、八戒、众神赶来。
那魔王慌转身向南走，又撞着峨眉山清凉洞法力无量胜至金刚挡住喝道：『吾奉佛旨在此，正要拿住你也！』牛王心慌脚软，急抽身往东便走，却逢着须弥山摩耳崖毗卢沙门大力金刚迎住道：『你老牛何往！我蒙如来密令，教来捕获你也！』牛王又悚然而退，向西就走，又遇着昆仑山金霞岭不坏尊王永住金刚敌住喝道：『这厮又将安走！我领西天大雷音寺佛老亲言，在此把截，谁放你也！』那老牛心惊胆战，悔之不及。


，使斩妖剑望颈项上一挥，不觉得把个牛头斩下。天王收刀，却才与行者相见。
那牛王腔子里又钻出一个头来，口吐黑气，眼放金光。被哪吒又砍一剑，头落处，又钻出一个头来。

哪吒取出火轮儿挂在那老牛的角上，便吹真火，焰焰烘烘，把牛王烧得张狂哮吼，摇头摆尾。才要变化脱身，又被托塔天王将照妖镜照住本象，腾那不动，无计逃生，只叫『莫伤我命！情愿归顺佛家也！』哪吒道：『既惜身命，快拿扇子出来！』牛王道：『扇子在我山妻处收着哩。』

哪吒见说，将缚妖索子解下，跨在他那颈项上，一把拿住鼻头，将索穿在鼻孔里，用手牵来。






*/

mapping _arrive = ([
	"place"	: "/d/gao/daotian1",
	"sb."	: "/d/gao/npc/bull",
	"msg"	: "你扑通一声掉在地上，清醒了过来。",
]);

//来临
int arrive(object who)
{
	string name = random1(keys(_names));


	if(who->move(_arrive["place"])) {
		object env = environment(who);
		object sb = new(_arrive["sb."]);
		sb->move(env);
		msv(_arrive["msg"], who, sb);		
	}
}


string _long = @LONG

一头牛，头如峻岭，眼若闪光，两只角似两座铁塔，牙排利刃。
连头至尾，有千余丈长短，自蹄至背，有八百丈高下。

LONG;

string _limbs = ({ "头部", "身体", "前爪", "尾巴", "肚皮", "后爪"});

//物种子类
mapping _names = ([
	"白牛"	: ([
		"ids"			: ({"bai niu", "niu", "cattle"}),
		"long"			: _long,
		"color"			: HIW,
		"unit"			: "头",
		"limbs"			: _limbs,
	]),
	"青牛"	: ([
		"ids"			: ({"qing niu", "niu", "cattle"}),
		"long"			: _long,
		"color"			: HIC,
		"unit"			: "头",
		"limbs"			: _limbs,
	]),
]);

//得到随机子类
string random_name()
{
	return random1(keys(_names));
}



//设置描述信息
mapping add_desc(mapping trait, string name)
{
	mapping m = _names[name];
	trait["name"]	= name;
	trait["ids"]	= m["ids"];
	trait["short"]	= m["color"] + name + NOR + "(" + capitalize[m["ids"][0]] + ")";
	trait["long"]	= m["long"];
	trait["unit"]	= m["unit"];
	trait["limbs"]	= m["limbs"];
	return trait;
}

//获取真身具有的各种特征
mapping query_trait(string name)
{
	mapping m = _names[name];
	mapping trait = ([
		"bonus"		: 1,		//技能亲和以及转世
		"kee"		: 100,		//气血增量
		"sen"		: 100,		//精神增量
		"add_apply"	: ([
			"armor"		: 100,
			"strength"	: 100,
			"unarmed"	: 100,
			"parry"		: 100,			//胳膊粗，能招架，combatd中空手有惩罚
			//"force"		: 100,			//挽救roar
			"dodge"		: 100,			//体型太大，难闪转腾挪
		]),
		
		"interval"	: 4,
		"timer_act"	: (: on_timer :),
		"_post_act"	: 0,
	]);

	return add_desc(trait, name);
}

//施展物种绝技
int unique_skill(object me, object target)
{
	object weapon = ob->query_temp("weapon");
	string wname = "双手";
	string act = "扳";
	string msg = "\n$n举起%s，大喝一声将牛头%s了下来。\n" +
		"$N腔里又钻出一个牛头来，口吐黑气，眼放金光！\n";
	if(weapon) {
		mapping tab = ([
			"hand"		: "扳",
			"axe"		: "劈",
			"blade"		: "砍",
			"sword"		: "削",
			"dagger"	: "割",
			"fork"		: "叉",
			"hammer"	: "砸",
			"spear"		: "挑",
			"staff"		: "扫",
			"stick"		: "扫",
			"throwing"	: "射",
			"whip"		: "抽",
			"mace"		: "抽",
		]);
		string act1 = tab[weapon->query("skill_type")];
		if(act1) {
			wname = weapon->query("name");
			act = act1;
		}
	}
	MSG->vision(msg, me, who, wname, act);

	new("/d/qujing/jilei/obj/head")->move(environment(me));
	return 0;
}

