// by firefox 07/21/2010

#include <xyj_x.h>

/*

真身技

等级和map unarmed一致，
受技能亲和加成，比如dragonfight + 命中，威力。老鼠受yinfeng-zhua。

*/

void create()
{
	seteuid(getuid());
}


//攻击技能
mapping _attack_act = ({
		
	//毒牙
	"poison-tooth"		: ({
		"$N如影随形般附在$n背上，露出尖利的"HIW"毒牙"NOR"，悄无声息地向$n咬去！"
		"$N突然近身，白森森的"HIW"毒牙"NOR"已到眼前，$n即刻要成$N口中餐！"
	}),

	//毒舌头
	"poison-tongue" : ({
		"$N昂首挺立，嘶嘶突出"HIR"毒信"NOR"，直刺向$n，一股腥风扑面而来。",
	}),

	//蛇身
	"snake-body"	: ({
		"$N迅速贴住$n，继而盘旋而上，要将$n缠住，勒个粉身碎骨。"
	}),

	"mouth"		: ({
		"$N张开血盆大口，恶狠狠的向$n咬去！",
	}),

	"tail"		: ({
		"$N身形一转，尾巴如钢鞭一般向$n扫去！",
	});

	"horn"		: ({
		"$N连连后退，蓄势挺角，风驰电掣般向$n撞去！",
		"$N低下头，以角对准$n，一个海底捞月向$n挑去。",
		"$n藏到$N身后，正欲进攻，谁料$N猛然回头，右角如利刃般刺来。",
	}),

	//牲畜
	"hoof"		: ({
		"$N纵身一跃，前蹄以雷霆万钧之势向$n踏下！"
		"$N身形一转，后蹄扬起，向$n踢去！"
	}),

	//猫科/鸟/白骨精
	"claw"	: ({
		"$N一跃而起扑向$n，利爪迎面抓去。",
		"$N腾空而起，利爪如钩，对$n当头抓下。"
	}),

	//熊
	"palm"		: ({
		"$N站立起来，轮起右掌向$n重重拍下。"
	}),

	//螯
	"pincers"	: ({
		"$N挥舞着巨螯，如铁钳般向$n夹去。"
	})

	//鼻，卷


});

//攻击技能，大部分废了，该死的combatd
mapping _defense_act = ([

	"tail"		: ({
		"$n眼见来势凌厉，忙低身挥动尾巴，顺势将$N荡开。",
	});

	"horn"		: ({
		"$n已经无处可躲，忙侧头转角，将$N架住。",
	}),

	"hoof"		: ({
		"$N轻轻一纵四蹄腾空，躲过$n的攻势！",
	}),

	"wing"		: ({
		"$N煽动双翅，狂风顿起，$n不得不收回攻势。",
		"$N一飞冲天，$n鞭长莫及，攻势登时化解。",
	}),

	"palm"		: ({
		"$N挥掌相迎，硬生生将$n震开。"
	}),

	"pincers"	: ({
		"$N举螯格挡，$n当即被荡开。"
	})

	"shield"	: ({
		"$N移动身形，以厚甲相对，$n的攻势如触铁壁铜墙，电光交错。",
	}),

	"common"	: ({
		"$n就地一滚，$N的攻势当即落空。",
		"$n弓身急退，$N鞭长莫及。",
		"$n眼见招来不避不让，$N的进攻如中棉絮，无处着力。",
	}),
]);


//获取防守信息，目前没法提供种族独特的信息
string query_defense_msg()
{
	return random1(_defense_act["common"]) + "\n";
}

mapping _acts_tab = ([]);			//各个种族的攻击动作

//获取进攻信息
string query_attack_act(object who)
{
	string race_id = RACE_D->query(who, id);
	mapping* acts = _acts_tab[race_id];

	if(!acts) {
		string* weapons = RACE_D->find(race_id)->query_weapons();
		string* msgs = ({});
		foreach(string weapon in weapons) {
			msgs += ({_attack_act[weapon]});
		}
		acts = ({});
		foreach(string msg in msgs) {
			mapping act = ([
				"action"		: msg + "\n",
				"force"			: 120,
				"dodge"			: -30,
				"parry"			: -60,			//补偿combatd中的空手招架损失
				"damage_type"	: "抓伤",
			]),
			acts += ({act});
		}
		_acts_tab[race_id] = acts;
	}
	return random1(acts);
}

//击中附带动作
mixed act_hit_ob(object me, object victim, int damage_bonus)
{
	if( damage_bonus < 100 ) return 0;

	if( random(damage_bonus/2) > victim->query_str() ) {
		victim->receive_wound("kee", (damage_bonus - 100) / 4 );
		return "你听到「喀啦」一声轻响，竟似是骨碎的声音！\n";
	}
}
