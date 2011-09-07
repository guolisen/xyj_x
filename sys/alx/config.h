// by firefox 11/21/2009
// 战场配置

//限制
#define MATE_PER_ROOM			4		//房间内同方人数上限
#define ID_PER_IP				5		//同IP的char上限

#define MIN_EXP					10		//经验下限(K)
#define MIN_MANA				2000	//内力法力下限

#define MOVE_BUSY				4		//移动点数耗尽的busy时间

//结束条件上限
#define MAX_RES					40000	//资源上限
#define MAX_TIME				1800	//时间上限
#define ACCEPT_TIME				1000	//战斗进行前期允许玩家加入的时间

//奖惩设定
#define MAX_TOTAL_POT			99000	//奖励上限
#define MIN_TOTAL_POT			30000	//奖励下限
#define KILL_POT				4000	//杀死一个人的奖励		***
#define MIN_RATIO				25		//杀人奖励比率下限
#define MAX_RATIO				400		//杀人奖励比率上限

#define DIE_PER					-30		//死亡的损失，相对于KILL_POT的百分比		***

#define WIN_POT					10000	//胜利方人均奖励
#define FLAG_RES				12		//每个旗子，每刻贡献的资源数		***
#define OCCUPY_POT				4000	//占领据点奖励		***
#define OCCUPY_THR				10		//最大有效占领据点次数
#define NO_RES_TIME				10		//占领据点后，据点无资源产出时间

//状态
#define INVITE					1
#define BATTLE					2
#define DONE					3


//其他设定
#define PULSE					4		//战场脉搏
#define CLIMB_DURATION			15		//爬旗杆/夺取据点的时间
#define WAIT4DURATION			10		//死亡后再地狱中的等待时间

#define INVITE_USER				44		//邀请玩家间隔，必须是PULSE的倍数

#define ALLOT_HAIR				28		//分发救命毫毛间隔，必须是PULSE的倍数
#define HAIR_HP_MULT			3		//救命毫增加hp的倍数
#define HELPER_LIFE				120		//召唤护法的生存时间
#define HELPER_RATIO			60		//召唤护法相对于最高玩家的强度

#define HP_CURE					600		//每次治疗的kee/sen

#define DEAD_RECOVER			2000	//死亡回复的内力法力


