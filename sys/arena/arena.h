#ifndef SYS_ARENA_H_INCLUDED
#define SYS_ARENA_H_INCLUDED

#include <ansi.h>
#include <xyj_x.h>

/********************************��������***********************************/


#define TITLE					"�������"

//��Ӫ
#define XIAN					1
#define	MO						2

#define MAX_NUMBER				3
#define MAX_EXP_RATIO			50

//״̬
#define INVITE					1		//����
#define GROUP					2		//С����
#define FINAL					3		//����
#define DONE					4		//��������

//����
#define HELL					ALX_DIR"map/hell"
#define MAP						ALX_DIR"map/map"

//ID����
#define WAIT4R					"alx_wait4r"		//�ȴ�����buff��ID
#define BG_NO_RES				"alx_no_res"		//��������ʱ�����ṩ��Դ



/********************************��������***********************************/
mapping* _camps = ({0, 0, 0});					//��ս��Ӫ/�������
int	_status;									//����״̬

/********************************��������***********************************/
void rumor(string str);

int room_goto_hell(object who);
int room_get_out(object who);

varargs int score_query(object who, string item, int history);
void score_set(object who, string item, int value);
varargs int score_liveness(object who, int history);
int score_add(object who, string item, int value);
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

