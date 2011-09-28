#ifndef IMUD_FCS_DD_H_INCLUDED
#define IMUD_FCS_DD_H_INCLUDED
// firefox 04/16/2011


//玩家信息
#define PREADY					4					//玩家是否就绪
#define PBET					4					//玩家本轮投注额
#define PNUM					5					//玩家序号
#define PCARDS					6					//玩家的牌

//通知消息
#define MSG_STARTED				1
#define MSG_NOT_START			2
#define MSG_NOT_YOU				3
#define MSG_JOINED				4
#define MSG_NOT_JOIN			5
#define MSG_FULL				6

#define MSG_NOT_ENOUGH			11
#define MSG_AT_LEAST_1			12
#define MSG_TOO_LESS			13
#define MSG_TOO_MUCH			14
#define MSG_HOW_MONEY			15
	
#define MSG_BETTED				21
#define MSG_PLS_BET				22
#define MSG_CALL_OR_FOLD		23
#define MSG_NOT_LAST			24
#define MSG_NO_FOLD				25

#define MSG_NO_HAND_CARD		31




//字符串分解成数组，如果是元素可化为整数则转化成整数
mixed* spilt_t(string str, string del)
{

}


//字符串解析成数组
mixed* to_arr(string str)
{
	mixed* arr;
	if(rfind(str, '+') > -1) {
		string* strs = explode(str, "+");
		arr = alloc(sizeof(strs));
		for(int i = 0; i < sizeof(strs); ++i) {
			if(rfind(strs[i], ',') > -1) {
				
			}
		}
	} else {
		arr[i] = explode(strs[i], ',
	}
}


#endif

