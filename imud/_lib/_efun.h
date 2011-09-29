// firefox 04/16/2011
// iMUD-simul_efun定义

#ifndef IMUD_LIB_EFUN_H
#define IMUD_LIB_EFUN_H

#include <imud.h>

/********************************配置变量***********************************/
#define ALIVE_INERVAL				180		//节点alive时间间隔
#define VERB_INERVAL				3		//动作时间间隔


/********************************玩家常量***********************************/
#define PNAME						0		//玩家名
#define PID							1		//玩家ID
#define PMUD						2		//玩家MUD
#define PSCORE						3		//玩家分数
#define PDATA						3		//玩家数据
#define NOBODY						({"", "", ""})		//空玩家

/********************************常用宏***********************************/
#define object_f		string							//文件对象，区别于普通字符串
#define _this			this_object()
#define _player			this_player()
#define assert(_exp)	if(!(_exp)) error("assert: _exp\n")
#define swap2(a, b)		{mixed t = a; a = b; b = t;}
#define MUD_ID			(iMUD_NET_D->mud_id())
#define SERVER_ID		(iMUD_NET_D->server_id())

/********************************数学函数***********************************/
///较大值
mixed max2(mixed a, mixed b);
///较小值
mixed min2(mixed a, mixed b);
///最大值
mixed max3(mixed a, mixed b, mixed c);
///最小值
mixed min3(mixed a, mixed b, mixed c);
///从数组中随机选择一个元素
mixed random1(mixed* arr);
///洗牌
int* shuffle(int* arr);

/********************************逻辑函数***********************************/
///如果a非空则a，否则b。
mixed or2(mixed a, mixed b);
///如果a空则a，否则b
mixed and2(mixed a, mixed b);

/********************************字符串函数***********************************/
///分配定长字符串
string allocate_str(int n);
///反向搜索指定字符位置
int rfind(string str, int ch);
///全路径中的文件名
string path_file(string path);
///全路径中的路径名
string path_dir(string path);
///反方向
string neg_direction(string d);
///base64编码
string to_base64(int* arr);
///base64解码
int* from_base64(string str);

/********************************对象函数***********************************/
///查找本地玩家对象
object player_object(mixed* who);
///玩家全局ID
string player_gid(mixed* who);
///从全局ID产生玩家信息
mixed* gid_player(string gid);
///目标的文件名，不含路径，缺省为当前对象
varargs string file_leaf(object ob);
///目标所在目录，不含文件名
string file_dir(object ob);

/********************************消息函数***********************************/
///向wiz报告测试数据
varargs int trace(string msg, object who);
///显示信息，并返回成功
int notify_ok(string msg);
///显示信息，包括看台
varargs int msg_rooms(mixed* rooms, string str, mixed* me, mixed* target);

/********************************本地化函数***********************************/
//玩家名称+ID
string name_id(mixed* who);


#endif

