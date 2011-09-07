
#include <xyj_x.h>
#include <ansi.h>

#define MSG_PAT				"$n轻轻地拍拍$N的头。"
#define MSG_HUG				"$n抱着$N，轻轻地哼着摇篮曲。"
#define MSG_LICK			"$n轻轻的舔着$N的毛。"
#define MSG_PUSH			"$n轻轻的拱了$N一下，$N摇摇晃晃地站了起来。"


#define ANIMAL_LIMBS	({ "头部", "脖子", "身体", "后背", "肚皮", "前爪", "后爪", "尾巴"})
#define CATTLE_LIMBS	({ "头部", "脖子", "身体", "后背", "肚皮", "前蹄", "后蹄", "尾巴"})
#define BIRD_LIMBS		({ "头部", "脖子", "身体", "后背", "肚皮", "左爪", "右爪", "尾巴"})
#define SNAKE_LIMBS		({ "头部", "颈部", "身体", "肚皮", "尾巴"})


mapping _subs;			//物种子类
mapping _traits;		//真身特征
string* _weapons;		//武器
mapping _born;			//出生信息

void init_var();

void create()
{
	seteuid(getuid());

	init_var();

	//补全子类的信息(用户可以省略color/short/unit/long)
	foreach(string name, mapping m in _subs) {
		m["name"]	= color_name(name, m["color"]);
		m["unit"]	= or2(m["unit"], "个");
		m["long"]	= or2(m["long"], "一" + m["unit"] + name + "。");		
	}
	if(!_traits["limbs"]) _traits["limbs"] = ({ "头部", "身体" });
}

//得到随机子类
string random_name()
{
	return random1(keys(_subs));
}

//生了
int born(object who)
{
	if(who->move(_born["place"])) {
		object env = environment(who);
		object sb = new(_born["sb."]);
		object ob = present(sb->query("id"), env);
		if(ob) {
			destruct(sb);
			sb = ob;
		} else {
			sb->move(env);
		}
		who->delete_temp("block_msg/all");
		msv(_born["msg"] + "\n"NOR, who, sb);
	}
}

//查询武器
string* query_weapons()
{
	return _weapons;
}

#define ZS_BONUS		10			//转世一次提升技能的百分比

//获取真身所需要的buff
mapping make_buff(object who)
{
	int ratio = 100 + RACE_D->query(who, "num") * ZS_BONUS;
	int skill = who->query_skill("spells", 1) * ratio / 100;
	int kee =  _traits["kee"] * skill/ 100;
	int sen =  _traits["sen"] * skill/ 100;
	int name = RACE_D->query(who, "name");
	mapping sub = _subs[name];

	mapping buff = ([
		"comment"	: "恢复真身，展现原始面貌。",
		"class"		: "变身术",
		"temp"		: ([
			"apply/name"	: ({ name }),
			"apply/id"		: sub["ids"],
			"apply/long"	: ({ sub["long"] + "\n" }),
			"No_Wield"		: 1,
			"powerup"		: 1,
		]),
		"add_apply"	: _traits["add_apply"],
		"replace"	: ([
			"limbs"			: _traits["limbs"],
		]),
		"add"		: ([
			"max_kee"		: kee,
			"eff_kee"		: kee,
			"kee"			: kee,
			"max_sen"		: sen,
			"eff_sen"		: sen,
			"sen"			: sen,
		]),

		"post_act"	: function(mapping buff) {
			object me = buff["me"];
			string* props = ({"kee", "eff_kee", "sen", "eff_sen"});			
			foreach(string prop in props) {		//防止死掉
				me->set(prop, max2(me->query(prop), 1));
			}
		},
		"interval"	: _traits["interval"],
		"timer_act"	: _traits["timer_act"],
	]);

	//加上那些按照百分比增长的属性
	foreach(string k, int v in _traits["add_apply_x"]) {
		buff["add_apply"][k] += v * skill / 100;
	}
	//计算技能亲和
	foreach(string k in ({"unarmed", "dodge", "force", "spells"}) ) {
		string mapped = who->query_skill_mapped(k);
		int v = _traits["skill_bonus"][mapped];
		buff["add_apply"][k] += v * skill / 100;
	}

	//计算force_factor
	buff["replace"]["force_factor"] = who->query_skill("force") / 2
		+ buff["add_apply"]["force"] / 2;

	return buff;
}

