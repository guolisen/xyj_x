#ifndef SYS_ALX_H_INCLUDED
#define SYS_ALX_H_INCLUDED
// by firefox 11/21/2009

#include "config.h"
#include <ansi.h>
#include <xyj_x.h>

/********************************常量定义***********************************/


#define TITLE					"狮驼岭会战"

//阵营
#define XIAN					1
#define	MO						2

//对象
#define HELL					ALX_DIR"map/hell"
#define MAP						ALX_DIR"map/map"

//ID定义
#define WAIT4R					"alx_wait4r"		//等待复活buff的ID
#define BG_NO_RES				"alx_no_res"		//该旗子暂时不能提供资源



/********************************变量定义***********************************/
mapping* _camps = ({0, 0, 0});					//参战阵营/玩家数据
int	_status;									//战场状态
int _start_time;								//启动时间

/********************************函数定义***********************************/
void rumor(string str);

int room_goto_hell(object who);
int room_get_out(object who);

varargs int score_query(object who, string item, int history);
void score_set(object who, string item, int value);
varargs int score_liveness(object who, int history);
varargs int score_add(object who, string item, int value, int history);
int score_add_exp(object who, int value);
varargs mapping score_entire(object who, int history);
varargs mapping score_clear(object who, int history);

void help_init();
void help_record_top(object who);
void help_allot_hair();


int camp_id(object ob);
int camp_same(object ob1, object ob2);
int set_camp(object ob, int c);
void camp_occupy(object flag, int camp, string color);
mapping camp_buff(object who);
string camp_name(mapping camp);
mapping camp_group(object* users);
void camp_init();
mapping camp_add_buff(object who, mapping camp);
void camp_leave(object who);
void camp_accept_all();
void camp_msg(mapping camp, string msg);
void camp_check_ip();

varargs object* sort_user(string cmp, int camp);
void broadcast_score(object* users);

#endif

