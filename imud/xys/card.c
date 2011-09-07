
// by firefox 10/01/2010
// 西游杀-装备

#include "xys.h"

/*

mapping card = ([		//card数据结构

	"type"			:	//类别
	"name"			:	//名称
	"comment"		:	//说明

	//使用属性

	"cd_prop"		:	//冷却属性
	"cd"			:	//冷却时间

	"cost_prop"		:	//消耗属性
	"cost"			:	//消耗数值
	
	"no_target"		:	//无需指定目标
	"need_weapon"	:	//要求玩家使用指定类型的武器
	
	"add"			:	//使用时玩家属性数值增加
	
	"fun"			:	//功能函数
	"dist"			:	//有效距离
	"success"		:	//技能命中系数

	"msg_start"		:	//初始提示信息
	"msg_ok"		:	//成功提示信息
	"msg_fail"		:	//失败提示信息
	"msg_eff"		:	//生效时提示，如aoe,dot

	"d_type"	:	//法术伤害类型，1-气血，2-精神，3-两者
	"damage"		:	//伤害值
	"aoe_all"		:	//aoe伤害所有人，包括施法者

	"use_once"		:	//一次性，用过就销毁

	//武器或装备属性

	"slot"			:	//安装位置
	EQU_PROP		:	//附加属性
	"skill_type"	:	//武器的对应技能
]);

*/

//搜索一个空位置
private int empty_slot(mapping who)
{
	for(int i = BASIC_CARDS; i < CARDS_SIZE; ++i) {
		if(!who["cards"][i]) return i;
	}
	return CARDS_SIZE;
}

//卸下武器或盔甲
int unequip(mapping who, int n)
{
	mapping cards = who["cards"];
	mapping card = cards[n];
	int slot = card["slot"];
	
	if(slot != n) return 0;		//没有装备
	
	//移除apply
	foreach(string k, int v in card[EQU_PROP]) {
		who["apply"][k] -= v;
	}	
	cards[empty_slot(who)] = card;
	cards[n] = 0;
	return 1;
}


//装备武器或盔甲
int equip(mapping who, int n)
{
	mapping cards = who["cards"];
	mapping card = cards[n];
	int slot = card["slot"];					//装备安装位置
	mapping old = cards[slot];
	
	if(card == old) return 1;
	if(!card[EQU_PROP]) return 0;			//不可装备

	if(old) unequip(who, slot);

	cards[slot] = card;

	//增加apply
	foreach(string k, int v in card[EQU_PROP]) {
		who["apply"][k] += v;
	}
	return 1;
}

//计算玩家机动性
private int movement(mapping who)
{
	int* s = who["state"];
	if(s[S_NO_MOVE] || s[S_BUSY] || s[S_NO_CONTROL]) return 0;
	return who["apply"]["movement"];
}

//计算玩家间距离
private int dist(mapping who, mapping target)
{
	int n = (target["order"] - who["order"] + MAX_CHAR) % MAX_CHAR;
	
	if(n > MAX_CHAR / 2) n = MAX_CHAR - n;
	return n;	
}

//使用卡片
mixed use(mapping who, int n, mapping target)
{
	mapping cards = who["cards"];
	mapping card = cards[n];
	mapping add = card["add"];						//增加属性属性药物
	function fun = card["fun"];						//函数
	int ok = 0;
	int cdp = card["cd_prop"];
	string cop = card["cost_prop"];

	//检查目标
	if(!card["no_target"] && !target) return "未指定目标。";
	//检查CD
	if(cdp && who["state"][cdp]) return card["name"] + "暂时不可用。";
	//检查武器类型
	if(card["need_weapon"] && card["need_weapon"] != weapon_type(who))
		return "缺少合适的武器。";
	//检查消耗	
	if(cop) {
		if(who[cop] < card["cost"]) return "你状态不佳。";		
		who[cop] -= card["cost"];
	}
	msv1(card["msg_start"], who, target, card);

	//治疗或削弱自身属性
	if(add) {
		foreach(string k, int v in add) {
			who[k] = min2(who[k] + v, 100);
		}
		ok = 1;
	}
	//有特殊功能的物品
	if(fun) {		
		int d = dist(who, target) + movement(who) - movement(target);
		
		if(!card["no_target"] && card["dist"] < d) return "距离目标太远。";
		ok = evaluate(fun, card, who, target);	//返回技能是否成功
	}
	//开始CD
	if(cdp) who["state"][cdp] = card["cd"];

	if(ok) {
		if(card["use_once"]) cards[n] = 0;	//销毁一次性物品		
		msv1(card["msg_ok"], who, target, card);
	} else {
		msv1(card["msg_fail"], who, target, card);
	}
	return 0;
}

