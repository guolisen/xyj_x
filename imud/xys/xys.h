#ifndef SYS_ALX_H_INCLUDED
#define SYS_ALX_H_INCLUDED
// by firefox 10/01/2010
// 

#include <ansi.h>
#include <xyj_x.h>

/********************************常量定义***********************************/

#define TITLE					"西行幻境"

#define	PULSE					2					//心跳

#define BATTLE					1
#define DONE					2


#define	MIN_CHAR				4					//最少玩家数
#define	MAX_CHAR				6					//最多玩家数
#define INIT_CARD				4					//开始玩家具有的牌数

#define INIT_TIME				5					//初始发牌后，玩家的思考时间
#define	CHAR_TIME				8					//玩家思考时间

#define REWARD_GOLD				10					//胜利奖励的黄金
#define BAN_TIME				600					//中途退场，禁止报名的时间

#define CARDS_SIZE				16					//牌数组容量
#define BASIC_CARDS				6					//基本牌数
#define FLOW_CARDS				5					//最大流动牌数


/********************************对象***********************************/

#define FAMILY_SKILLS			__DIR__"family-skill"

/********************************玩家手牌***********************************/

#define C_ROLE					0					//
#define C_WEAPON				4					//
#define C_CLOTH					5					//
#define C_HORSE					6					//
#define EQU_PROP				"equ_prop"

/********************************玩家角色***********************************/

#define VIP						256					//主公标志
#define ZHONG					1					//忠臣
#define ZHU						(ZHONG + VIP)		//主公
#define	JIAN					2					//奸臣
#define	FAN						4					//反贼

mapping _roles = ([
	ZHU			: "取经人",
	ZHONG		: "徒弟",
	JIAN		: "假徒弟",
	FAN			: "妖怪",
]);

/********************************玩家状态***********************************/

#define S_BUSY					0
#define S_NO_MOVE				1
#define S_NO_CAST				2
#define S_NO_WIELD				3
#define S_NO_CONTROL			4
#define S_NO_POWERUP			5
#define S_NOT_HERE				6

mixed* _states = ({
	({ "自顾不暇",	"不能攻击/施法的" }),
	({ "不能移动",	"不能移动/攻击" }),
	({ "不能施法",	"不能施法" }),
	({ "禁用兵器",	"不能使用兵器" }),
	({ "失控",		"处于失控状态" }),
	({ "禁止强化",	"不能使用强化技能" }),
	({ "脱离战场",	"不再战斗现场" }),
});


/********************************变量定义***********************************/

mapping _chars = ([]);								//玩家数据
string* _order = ({});								//玩家当前座次
int _char_no = -1;									//当前玩家编号
mapping _char;										//当前玩家数据

int _start_time;									//战斗启动时间

/********************************函数定义***********************************/

//显示信息
varargs int msv1(string msg, mapping me, mapping target, mixed arg);
//判断玩家是否死亡
int is_dead(mapping who);

//武器类型
string weapon_type(mapping me);

#define _who _chars[getuid(_player)]				//命令的当前用户的数据


//一般法术攻击绝招
int cast(mapping card, mapping me, mapping target);
//一般物理攻击绝招
int perform(mapping card, mapping me, mapping target);
/*

//一般增强绝招
int powerup(mapping card, mapping me, mapping target);
//群体法术攻击绝招
int aoe(mapping card, mapping me, mapping target);
//一般法术命中判定
int cast_success(mapping card, mapping me, mapping target);
*/


//添加一个buff
int buff_add(mapping who, mapping buff);
//刷新并返回buff的剩余时间
int buff_refresh(mapping buff);
//移除一个buff
int buff_remove(mapping buff);
//刷新某人的全部buff，移除过期buff
void buff_refresh_all(mapping who);


//卸下武器或盔甲
int unequip(mapping who, int n);
//装备武器或盔甲
int equip(mapping who, int n);

//查找下一个玩家
mapping find_next(mapping who);
//查找前一个玩家
mapping find_prevous(mapping who);

//随机选择门派，返回其技能
mapping skill_of_random();
//技能注解
string skill_comment(string skill);

#endif


/*

_chars的数据结构


	//玩家数据结构

	name				//名字
	id					//id
	order				//序号
	camp				//阵营
	turn				//轮数
	[hp]
		max_kee/kee
		max_sen/sen
		max_mana/mana
		max_force/force
	skills
		parry
		dodge	
		force
		spells
		unarmed	
		stick
	apply
		damage
		dodge
	state
		no_move		//不能躲闪，不能用马
		busy		//不能能
	buff
		+damage
		dot
	cards
		role
			vip			apply/max_kee	100
		family
			pili		weapon : stick, force : 20
			thuder		mana : 20,	success 50 damage 30
			ding		mana : 20,
		equip
			weapon		金箍棒(133)
			cloth		金甲圣衣(33)
			horse		白龙马(75)
		misc
			fabao
			drug
			
*/