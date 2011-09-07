// by firefox 10/01/2010
// 西游杀-门派绝技

#include "xys.h"


/********************************辅助函数***********************************/

//计算在场玩家数量
int here_count()
{
	int n = 0;
	foreach(string id, mapping who in _chars) {
		if(is_dead(who) || who["state"][S_NOT_HERE]) continue;
		n++;
	}
	return n;
}

//获取玩家武器类型
string weapon_type(mapping me)
{
	return me["cards"][C_WEAPON]["skill_type"];
}

//增加或减少气血
int add_kee(mapping me, int n)
{
	if(n >= 0) me["kee"] = min2(me["kee"] + n, 100);
	else me["kee"] += (100 - me["apply"]["armor"]) * n / 100;
	return me["kee"];
}


//增加或减少hp属性
int add_hp(mapping me, string prop, int n)
{
	me[prop] += n;
	me[prop] = min2(me[prop], 100);	
	return me[prop];
}

//获取有效skill
int eff_skill(mapping me, string skill)
{
	return me["skills"][skill] + me["apply"][skill];
}

//一般法术命中判定
int cast_success(mapping card, mapping me, mapping target)
{
	int ap = eff_skill(me, "spells") * card["success"] / 100;
	int dp = eff_skill(target, "spells");
	
	if(target["state"][S_NO_CAST]) dp / 2;

	return ap / 2 >= random(dp);
}

/********************************普通攻击法术***********************************/

mapping _attack_spells = ([	
	
	//				 name			success	d_type	damage	cost	cd
	"bighammer"	: ({ "大力降魔杵",	120,	3,		30,		45,		3,
		"以杀止杀的强大法术",
		HIC"$N口中念了几句咒文，半空中现出阿傩，迦叶二尊者，各执降魔杵向$n当头砸下！\n"NOR,
		HIC"结果砸个正着，差点没把$n砸扁！\n"NOR,
		HIC"但是$n在千钧一发之际躲了开来。\n"NOR,
	}),
	
	"light"		: ({ "苍灵箭",		120,	1,		30,		30,		3,
		"闪电攻击",
		HIC"$N口中念了句咒文，半空走出电母，铜镜相转，忽的闪出一道金光射向$n！\n"NOR,
		HIR"结果「嗤」地一声，金光从$n身上透体而过，拖出一条血箭，射到两三丈外！\n"NOR,
		HIC"结果嗤！地一声$n闻到了一股焦味。还好只烧掉了几根头发。\n"NOR,
	}),

	"thunder"	: ({ "五雷咒",		120,	2,		30,		30,		3,
		"五雷轰顶",
		HIC"$N口中念了句咒文，半空走出雷公，斧锥相击，在$n的头顶炸起一片响雷！\n"NOR,
		HIR"结果$n被雷声震得眼冒金星，心神不定，差点跌倒在地！\n"NOR, 
		HIC"谁知$n毫无反应，就象聋子似的。\n"NOR, 
	}),

	"zhenhuo"	: ({ "太乙真火",		120,	3,		20,		20,		3,
		"玄门烈焰",
		HIC"$N几个指头迅速捻动，突然张嘴一喷！红橙黄三道火焰呼！地一声向$n卷去！\n"NOR,
		HIC"结果$n被烧得焦头烂额！\n" NOR, 
		HIC"但是$n轻轻一跳就躲了开来。\n" NOR, 
	}),

	"zouxiao"	: ({ "箫声箫声",		120,	2,		30,		30,		3,
		"西游众生堪比林妹妹，唉",
		HIM"$N对着$n奏起了一曲，箫声凄凉，似是叹息，又似哭泣。\n"NOR,
		YEL"可$n冲耳不闻，不为所动。\n"NOR,
		HIG"$n听了箫声，心中莫名其妙的感到一阵酸楚，悲从中来，泪水正涔涔落下。\n"NOR,
	}),

	"gouhun"	: ({ "勾魂术",		120,	2,		30,		30,		3,
		"没做亏心事也怕鬼叫门",
		HIC"$N对$n阴阴地笑着：阎王叫你三更死，不敢留你到五更。。。\n" NOR,
		HIC"$n受到$N影响，显然有点魂不守舍了！\n" NOR,
		HIC"但是$n神情专注，对$N理都不理。\n" NOR, 
	}),

	"tuntian"	: ({ "魔兽吞天",		120,	1,		30,		30,		3,
		"血盆大口，可吞十万天兵",
		HIC"$N口中念了句咒文，半空闪出一只青面獠牙的狮子，张开血盆大口向$n咬去！\n"NOR,
		HIR"结果$n被咬了个正着！\n"NOR,
		HIC"$n连忙一侧身闪在一旁。\n"NOR,
	}),
	
	"jieti"		: ({ "天魔解体大法",	20,		1,		100,	50,		3,
		"血盆大口，可吞十万天兵",
		HIC"$N口中念了几句咒文，忽然间$N将自己舌头狠命一咬，一道血雾向$n喷了过去！\n"NOR,
		HIR"结果$n被血雾罩住，顿时发出一声惨叫！而$N也身子一瘫，倒在地上。\n"NOR,
		HIR"结果血雾被$n法力反激，反而罩住了$N！$N长叹一声，身子一瘫，倒在地上。\n"NOR,
		([ "kee" : -100 ]),
	}),

	"love"		: ({ "催情大法",		150,	4,		30,		30,		3,
		"儿童不宜...",
		HIM"\n$N深情的望着$n，满眼秋波目光迷离，轻吟催情大法...\n\n"NOR,
		HIM"$n不禁春心荡漾难以自持。\n"HIC"$N打了一个寒颤。\n"NOR,
		HIM"$n仿佛不解风情，对$N视若无睹。\n\n"NOR,
	}),
]);

//一般法术攻击绝招
int cast(mapping card, mapping me, mapping target)
{
	int damage = card["damage"];
	
	if(!cast_success(card, me, target)) return 0;
	
	if(card["d_type"] & 1) add_kee(target, -damage);
	if(card["d_type"] & 2) add_hp(target, "sen", -damage);
	if(card["d_type"] & 4) add_hp(target, "force", -damage);
	if(card["d_type"] & 8) add_hp(target, "mana", -damage);
	return 1;
}

//创建普通攻击法术
mapping attack_spell(string id)
{
	mixed* a = _attack_spells[id];
	mapping card = ([
		"type"			: "法术",
		"name"			: a[0],
		"comment"		: a[6],

		"cd_prop"		: S_NO_CAST,
		"cd"			: a[5],
		"cost_prop"		: "mana",
		"cost"			: a[4],
		"dist"			: 1,

		"fun"			: (: cast :),
		"success"		: a[1],
		
		"msg_start"		: a[7],
		"msg_ok"		: a[8],
		"msg_fail"		: a[9],
		
		"d_type"		: a[2],
		"damage"		: a[3],
	]);

	return card;
}

/********************************自身强化法术***********************************/

mapping _powerup_spells = ([
	
	//				 name			a_type		a_num	cost	cd
	"lianhua"	: ({ "莲花护体",		"spells",	20,		20,		6,
		"幻化出莲花，形成法力保护",
		HIC"$N微一凝神，背后幻出一朵白莲，五色毫光闪现。\n"NOR,
	}),
	
	"jingxin"	: ({ "静心诀",		"dodge",	20,		20,		6,
		"闪电攻击",
		HIW"$N微一凝神，运起静心诀，登时心平气稳，于周围一切警觉有加。\n"NOR,
	}),

	"hell_pu"	: ({ "反五行摄气诀",	"damage",	20,		20,		4,
		"借助黑暗的力量强化自己",
		HIR"$N微一凝神，运起反五行摄气诀，头上冒出一股青气，脸部现出一个鬼形。。。\n",
	}),

	"shield"	: ({ "龙鳞护体",		"armor",	20,		20,		6,
		"生出龙鳞，保护自己",
		HIC"$N微一凝神，运起龙神心法，浑身上下顿时结出了青色的龙鳞。\n"NOR,
	}),
]);

//一般增强绝招
int powerup(mapping card, mapping me, mapping target)
{
	mapping buff = ([
		"id"		: "powerup",
		"duration"	: card["cd"] / 2,
		"apply"		: card["buff"],
	]);
	return buff_add(me, buff);
}

//创建普通攻击法术
mapping powerup_spell(string id)
{
	mixed* a = _powerup_spells[id];
	mapping card = ([
		"type"			: "法术",
		"name"			: a[0],
		"comment"		: a[5],

		"no_target"		: 1,
		"cd_prop"		: S_NO_POWERUP,
		"cd"			: a[4],
		"cost_prop"		: "mana",
		"cost"			: a[3],
		
		"fun"			: (: powerup :),
		"msg_start"		: a[6],		
		"buff"			: ([ a[1] : a[2] ]),
	]);

	return card;
}

/********************************普通攻击绝招***********************************/

mapping _attack_perform = ([
	
	//				      name			success	damage	cost	cd		weapon
	"pili"			: ({ "霹雳三打",		80,		50,		50,		6,		"stick",
		"以杀止杀的强大法术",
		HIC"\n$N运足精神，身形一转，霹雳间连续向$n攻出了三招！\n"NOR,
		"$n躲闪不及，重重挨了三下！\n",
		"$n轻轻一闪，没伤到分毫。\n",
	}),

	"sanban"		: ({ "无敌三板斧",	120,	30,		30,		6,		"axe",
		"无敌三板斧",
		CYN"$N一声暴喝：开瓜！剔牙！掏耳朵！三招一气呵成！\n"NOR,
		"$n试图侧身避开，但为时已晚。大斧劈在肩上，留下一道深可见骨的伤口！\n",
		"$n轻轻一闪，大斧带着一阵劲风从身边斩下，但没伤到$n分毫。\n",
	}),

	"huima"			: ({ "回马枪",		120,	20,		20,		3,		"spear",
		"败中取胜的枪法绝技",
		YEL"$N虚晃一枪掉头便走，$n紧追不舍，不料$N仰面反身急刺！"NOR,
		WHT"但$N的攻势虽然凌厉，却招招落空，丝毫没有能对$n造成任何威胁。\n"NOR,
		WHT"但$n轻松看破$N的诡计，并不上$N的当，反而一个翻身档在了$N的面前。\n"NOR,
	}),

	"chaofeng"		: ({ "百鸟朝凤",		120,	20,		20,		3,		"sword",
		"偷袭绝技，令多少菜鸟丧命",
		HIW"只见$N手中剑急颤，幻出满天剑芒，无数剑气有如百鸟投林般向$n扑来！\n"NOR,
		HIW"$n连忙身行一转，连退数步，闪过了这满天花雨般的一击。\n"NOR,
		HIW"$n躲闪不及，身上三处中了剑气！\n"NOR,
	}),

	"qixiu"			: ({ "七修",			120,	20,		20,		3,		"sword",
		"七修绝技",
		"$N舞动手中剑，顿时阴风四起，日月无光。昏暗中$n发现剑已直指前心！\n",
		"$n慌忙侧身，却已为时已晚，眼前"HIR"一道血光"NOR"如春花般绽放。\n",
		"$n慌忙侧身，"HIC"剑光"NOR"沾衣而过，不禁惊出一身冷汗。\n"NOR,
	}),

]);


//一般物理攻击绝招
int perform(mapping card, mapping me, mapping target)
{
	string skill = weapon_type(me);
	int damage = me["apply"]["damage"] * card["damage"] / 100;

	int ap = eff_skill(me, skill) * card["success"] / 100;
	int dp = eff_skill(target, "dodge");
	int pp = eff_skill(target, "parry");

	if(target["state"][S_BUSY]) {
		dp /= 3;
		pp /= 3;
	}
	if(ap < random(dp + pp)) return 0;
	
	add_kee(target, -damage);

	return 1;
}

//创建普通攻击绝招
mapping attack_perform(string id)
{
	mixed* a = _attack_perform[id];
	mapping card = ([
		"type"			: "武术",
		"name"			: a[0],
		"comment"		: a[6],

		"need_weapon"	: a[5],
		"cd_prop"		: S_NO_MOVE,
		"cd"			: a[4],
		"cost_prop"		: "mana",
		"cost"			: a[3],
		"dist"			: 1,

		"fun"			: (: perform :),
		"success"		: a[1],
		"damage"		: a[2],
		"msg_start"		: a[7],
		"msg_ok"		: a[8],
		"msg_fail"		: a[9],
	]);
	return card;
}

/********************************治疗法术***********************************/

mapping _heal_spells = ([
	
	//				 name			h_type		h_num	cost	cd
	"heal"		: ({ "疗神术",		"sen",		30,		30,		3,
		"用法力缓解精神伤害",
		HIY"$N坐了下来运动法门，将手掌贴在$n灵台，缓缓地将法力输入$n体内....\n\n" +
		"过了不久，$N额头上冒出豆大的汗珠，$n吐出一口浊气，精神看起来好多了。\n" NOR,
	}),
	
	"suliao"	: ({ "速疗",			"kee",		30,		30,		4,
		"用法术令伤口快速愈合",
		HIY"$N双手举在胸前，做个火焰状，念了几句咒。\n"NOR +
		HIY"随即，$N将双手在全身上下擦了一遍，双手到处，伤口居然好了大半！\n"NOR,
	}),

]);

//创建治疗法术
mapping heal_spell(string id)
{
	mixed* a = _heal_spells[id];
	mapping card = ([
		"type"			: "法术",
		"name"			: a[0],
		"comment"		: a[5],

		"no_target"		: 1,
		"cd_prop"		: S_NO_CAST,
		"cd"			: a[4],
		"cost_prop"		: "mana",
		"cost"			: a[3],
		
		"msg_start"		: a[6],		
		"add"			: ([ a[1] : a[2] ]),
	]);
	return card;
}

/********************************AOE法术***********************************/

mapping _aoe_spells = ([
	
	//				  name			success	d_type	d_num	cost	cd
	"roar"		: ({ "龙吟",			120,	2,		10,		30,		4,
		"噪声冲击波，小心耳朵",
		HIR"\n$N退后两步，深深地吸一口气，猛然发出股如山崩海啸般的龙吟！\n\n",
		"$n觉得眼前一阵金星乱冒，耳朵痛得像是要裂开一样！\n",
	}),
	
	"sanmei"	: ({ "三昧真火",		120,	3,		10,		50,		4,
		"火云洞招牌绝技",
		"\n$N往自家鼻子上捶了两拳，念个咒语，口中喷火，鼻子冒烟，顷刻间：\n\n" +
		HIR"炎炎烈烈盈空燎，赫赫威威遍地红。却似火轮飞上下，犹如炭屑舞西东。\n\n"NOR,
		"$n被烧得焦头烂额！\n",
	}),

]);

//群体法术攻击绝招
int aoe(mapping card, mapping me, mapping target)
{
	int damage = card["damage"];

	foreach(string k, mapping who in _chars) {
		int dp = eff_skill(who, "spells");

		if(!card["aoe_all"] && who == me) continue;
		if(who["state"][S_NOT_HERE]) continue;
		if(!cast_success(card, me, target)) continue;
	
		if(card["d_type"] & 1) add_kee(who, -damage);
		if(card["d_type"] & 2) add_hp(who, "sen", -damage);
		msv1(card["msg_eff"], me, who);
	}
	return 1;
}

//创建aoe法术
mapping aoe_spell(string id)
{
	mixed* a = _aoe_spells[id];
	mapping card = ([
		"type"			: "法术",
		"name"			: a[0],
		"comment"		: a[6],

		"no_target"		: 1,
		"cd_prop"		: S_NO_CAST,
		"cd"			: a[5],
		"cost_prop"		: "mana",
		"cost"			: a[4],

		"d_type"		: a[2],
		"damage"		: a[3],
		"fun"			: (: aoe :),
		
		"msg_start"		: a[7],
		"msg_eff"		: a[8],
	]);

	return card;
}

/********************************控制法术***********************************/

mapping _control_spells = ([
	
	//				 name			success	cost	cd		type	state
	"mihun"		: ({ "迷魂",			120,	30,		4,		"法术",	S_NO_MOVE,
		"英雄难过美人关",

		HIC"$N低头轻声念了句咒文，又抬起头来朝$n妩媚地一笑！\n"NOR,
		HIR"$n神不守舍地看着$N，怜香惜玉之心由然而起，竟然忘了自己在战斗之中。\n"NOR,
		HIR"$n鄙夷地看了$N一眼，毫不为所动！\n"NOR,
	}),

	"huimeng"	: ({ "回梦",			120,	30,		4,		"法术",	S_NO_CONTROL,
		0,

		HIM"$N凝视着$n的双眼，在$n耳边轻声唱着：“小宝宝，快睡觉。。。”\n"NOR,
		HIM"$n不知不觉的哈欠连连，眼皮沉重，终于支持不住，合上了双眼。\n"NOR,
		HIM"$n大喝一声，双目一张，精光四射！$N猝不及防，吓了一跳！\n"NOR,
	}),

	"fengbo"	: ({ "无尽风波",		120,	30,		6,		"法术",	S_BUSY,
		0,

		HIC"$N挥展开来，左一叉，右一叉，幻出无数大小光环向$n绕去！\n\n"NOR,
		HIR"$N果然被这光环套住，当时目瞪口呆，不知所措！\n"NOR,
		HIR"不料却被$N看破，攻其不备，$n反被打了个措手不及！\n"NOR,
	}),

	"pozhan"	: ({ "破绽",			120,	30,		4,		"法术",	S_BUSY,
		0,

		CYN"$N的招式突然一变，变得全无章法，浑身上下破绽百出。\n"NOR,
		CYN"$n想攻，却不辨真假。结果反被攻了个措手不及！\n"NOR,
		CYN"可是$n看破了$N的企图，并没有上当。\n" NOR,
	}),

	"bone-fire"	: ({ "三昧白骨火",	120,	30,		4,		"法术",	S_BUSY,
		0,

		"$N用手向$n一指，点点不易察觉的"HIB"磷光"NOR"从$n脚下升起...\n"NOR,
		HIC"$n的%s突然起火，惊慌失措，拼命扑打。\n"NOR,
		HIC"$n一挥手磷光随风飘散了...\n"NOR,
	}),

	"sheng"		: ({ "幌金绳",		150,	30,		4,		"法宝",	S_NO_MOVE,
		"太上老君的腰带",

		"$N口中念着咒语，掏出幌金绳对$n抛将过去！\n",
		"$n躲闪不及被捆了个起来，几乎动弹不得！\n",
		"$n向后一闪，躲了过去。\n",
	}),

	"qiankun"	: ({ "袖里乾坤",		150,	50,		4,		"法术",	S_NOT_HERE,
		"镇原大仙的绝技，孙悟空也难逃",

		HIR"$N喃喃地念了几句咒语，突然大袖一挥朝$n罩了过去！\n"NOR,
		HIR"结果嗖的一声$n被装了进去。\n"NOR,
		HIR"结果被$n法力一逼，差点罩住$N自己的脑袋。\n"NOR,

		"$N从$n袖口里探出脑袋，晕乎乎地爬了出来。\n",
	}),

	"hulu"		: ({ "紫金葫芦",		120,	30,		4,		"法宝",	S_NOT_HERE,
		"太上老君装仙丹的葫芦",

		"$N口中念着咒语，掏出紫金葫芦底儿朝上，冷不丁地对$n一喊：$n！\n",
		"$n顺口答道：在！\n倾刻之间$n被紫金葫芦叭地一声吸了进去！\n",
		"$n知道有诈，闭口不语，结果什么都没发生。\n",

		"$N从紫金红葫芦里探出脑袋，晕乎乎地爬了出来。\n",
	}),

	"jingping"	: ({ "羊脂玉净瓶",	120,	30,		4,		"法宝",	S_NOT_HERE,
		"一只几乎透明的羊脂玉净瓶",

		"$N口中念着咒语，掏出羊脂玉净瓶底儿朝上，冷不丁地对$n一喊：$n！\n",
		"$n顺口答道：在！\n倾刻之间$n被羊脂玉净瓶叭地一声吸了进去！\n",
		"$n知道有诈，闭口不语，结果什么都没发生。\n",

		"$N从羊脂玉净瓶里伸出头，昏昏沉沉地爬了出来。\n",
	}),
	
]);

//状态/控制法术
int state(mapping card, mapping me, mapping target)
{
	if(!cast_success(card, me, target)) return 0;
	if(!buff_add(target, card["buff"])) return 0;

	if(card["buff"]["state"][S_NO_WIELD]) unequip(target, C_WEAPON);
	return 1;
}

//创建法术
mapping state_spell(string id)
{
	mixed* a = _control_spells[id];
	mapping card = ([
		"type"			: a[4],
		"name"			: a[0],
		"comment"		: a[6],

		"cd_prop"		: S_NO_CAST,
		"cd"			: a[3],
		"cost_prop"		: "mana",
		"cost"			: a[2],
		"dist"			: 1,

		"fun"			: (: state :),
		"success"		: a[1],
		
		"msg_start"		: a[7],
		"msg_ok"		: a[8],
		"msg_fail"		: a[9],
		
		"buff"			: ([ 
			"id"			: "control",
			"duration"		: a[3] / 2,
			"state"			: ([ a[5] : a[3] / 2 ]),
			"msg_remove"	: (sizeof(a) > 10 ? a[10] : 0),
		]),
	]);

	return card;
}

/********************************dot法术***********************************/

mapping _dot_spells = ([	
	
	//				 name			success	cost	cd		d_type	damage
	"shiyue"	: ({ "蚀月",			120,	60,		6,		3,		10,
		"最毒月宫人",

		"$N低头默默念起咒文，手中渐渐聚起一团光球，雪白的脸庞似乎发射出柔和的光芒。\n",
		HIR"$n见到$N祥宁之态，娇美不可方物，心中一荡，却不防那光球一闪，突然射向$n。\n"NOR,
		HIR"$N脸色苍白，似乎体力不支，光球在手中渐渐褪去。！\n"NOR,
		
		HIR"$N脸色苍白，越来越虚弱。\n"NOR,
	}),

	"inferno"	: ({ "地狱火",		120,	40,		4,		1,		20,
		0,

		HIB"$N双掌一搓，登时燃起一团蓝色的火焰，点点磷光飘向了$n！\n"NOR,
		HIB"「啪」地一团蓝色火焰在$N脚下燃起，如鬼魅缠身，将$N拢在中央。\n"NOR,
		HIB"「啪」地一团蓝色火焰在$N脚下燃起，$N纵身跳开。\n"NOR,

		HIB"一团蓝色火焰在$N身上静静的燃烧着。\n"NOR,
	}),	
]);

//dot法术
int dot(mapping card, mapping me, mapping target)
{
	mapping buff = ([
		"id"		: card["dot_id"],
		"duration"	: card["cd"],
		"dot"		: card["buff"],
		"msg_dot"	: card["msg_eff"],
	]);
	return buff_add(target, buff);
}

//创建法术
mapping dot_spell(string id)
{
	mixed* a = _dot_spells[id];
	mapping card = ([
		"type"			: "法术",
		"name"			: a[0],
		"comment"		: a[6],

		"cd_prop"		: S_NO_CAST,
		"cd"			: a[3],
		"cost_prop"		: "mana",
		"cost"			: a[2],
		"dist"			: 1,

		"fun"			: (: dot :),
		"success"		: a[1],
		
		"msg_start"		: a[7],
		"msg_ok"		: a[8],
		"msg_fail"		: a[9],
		"msg_eff"		: a[10],
		
		"buff"			: ([]),
	]);

	if(a[4] & 1) card["buff"]["kee"] = a[5];
	if(a[4] & 2) card["buff"]["sen"] = a[5];

	return card;
}

/********************************其他法术***********************************/

//撞
mapping zhuang_spell()
{
	mapping card = ([
		"type"			: "法术",
		"name"			: "撞",
		"comment"		: "撞飞他！",

		"cd_prop"		: S_NO_CAST,
		"cd"			: 3,
		"cost_prop"		: "force",
		"cost"			: 20,
		"dist"			: 1,

		//改变临近目标位置
		"fun"			: function(mapping card, mapping me, mapping target)
			{
				mapping who;
				if(here_count() < 3) return 0;
				if(!cast_success(card, me, target)) return 0;

				if(target == find_next(me)) who = find_next(target);
				if(target == find_prevous(me)) who = find_prevous(target);
				if(!who) return 0;
				
				swap2(_order[target["order"]], _order[who["order"]]);
				swap2(target["order"], who["order"]);

				return 1;
			},
		"success"		: 120,
		
		"msg_start"		: HIC"$N猛然退后两步，一低头，呼地就向$n撞去！\n"NOR,
		"msg_ok"		: HIC"结果$n躲闪不及，被撞的象捆稻草般的飞了出去！\n"NOR,
		"msg_fail"		: HIC"结果被$n以法力一逼，$N没撞上去。\n"NOR,

	]);

	return card;
}


//移形换影
mapping yixing_spell()
{
	mapping card = ([
		"type"			: "法术",
		"name"			: "移形换影",
		"comment"		: "与目标交换肉身",

		"cd_prop"		: S_NO_CAST,
		"cd"			: 7,
		"cost_prop"		: "mana",
		"cost"			: 60,
		"dist"			: 1,

		//交换气血和流动牌
		"fun"			: function(mapping card, mapping me, mapping target)
			{
				if(!cast_success(card, me, target)) return 0;
				swap2(me["name"], target["name"]);
				swap2(me["kee"], target["kee"]);
				for(int i = BASIC_CARDS; i < BASIC_CARDS + 3; ++i) {
					unequip(me, i);
					unequip(target, i);					
				}
				for(int i = BASIC_CARDS + 3; i < CARDS_SIZE; ++i) {
					swap2(me["cards"][i], target["cards"][i]);
				}
				return 1;
			},
		"success"		: 90,
		
		"msg_start"		: "$N大喝："HIY"移形换影"NOR"！$N和$n如旋风一样转起来，分不清彼此。\n",
		"msg_ok"		: "片刻两人停下来，显得都很狼狈。\n",
		"msg_fail"		: "片刻两人停下来，显得都很狼狈。\n",

	]);

	return card;
}

//移魂大法
mapping yihun_spell()
{
	mapping card = ([
		"type"			: "法术",
		"name"			: "移魂大法",
		"comment"		: "控制别人的思想",

		"cd_prop"		: S_NO_CAST,
		"cd"			: 4,
		"cost_prop"		: "mana",
		"cost"			: 30,
		"dist"			: 1,

		//
		"fun"			: function(mapping card, mapping me, mapping target)
			{
				if(!cast_success(card, me, target)) return 0;
				//HIW"$N手扶着头，摇摇晃晃，清醒了过来。\n\n"NOR,
				target["state"][S_NO_CONTROL] = 2;
				return 1;
			},
		"success"		: 90,
		
		"msg_start"		: HIC"\n$N喊到『移魂大法』，只见$N目光如电，直射入$n眼中。\n"NOR,
		"msg_ok"		: "$n当即神情恍惚，迷失了心智。默默站到$N身后。\n\n"NOR,
		"msg_fail"		: "$n凝神静气，侧目躲过电光。\n\n"NOR,		
	]);

	return card;
}

//金刚琢
mapping zhuo_fabao()
{
	mapping card = ([
		"type"			: "法宝",
		"name"			: "金刚琢",
		"comment"		: "可收取敌人兵器",

		"cd_prop"		: S_NO_CAST,
		"cd"			: 7,
		"cost_prop"		: "mana",
		"cost"			: 30,
		"dist"			: 1,

		//
		"fun"			: function(mapping card, mapping me, mapping target)
			{
				mapping weapon = target["cards"][C_WEAPON];
				if(!cast_success(card, me, target)) return 0;
				if(weapon["skill_type"] == "unarmed") return 0;

				unequip(target, C_WEAPON);

				//todo
				return 1;
			},
		"success"		: 150,
		
		"msg_start"		: "$N中念念有词，忽地抛起金刚琢。"NOR,
		"msg_ok"		: "$n手中的兵器把持不定。已被金刚琢收去！\n\n"NOR,
		"msg_fail"		: "$n一纵身，躲开了空中的金刚琢。\n"NOR,
	]);

	return card;
}
