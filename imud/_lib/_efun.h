// firefox 04/16/2011
// iMUD-simul_efun����

#ifndef IMUD_LIB_EFUN_H
#define IMUD_LIB_EFUN_H

#include <imud.h>

/********************************���ñ���***********************************/
#define ALIVE_INERVAL				180		//�ڵ�aliveʱ����
#define VERB_INERVAL				3		//����ʱ����


/********************************��ҳ���***********************************/
#define PNAME						0		//�����
#define PID							1		//���ID
#define PMUD						2		//���MUD
#define PSCORE						3		//��ҷ���
#define PDATA						3		//�������
#define NOBODY						({"", "", ""})		//�����

/********************************���ú�***********************************/
#define object_f		string							//�ļ�������������ͨ�ַ���
#define _this			this_object()
#define _player			this_player()
#define assert(_exp)	if(!(_exp)) error("assert: _exp\n")
#define swap2(a, b)		{mixed t = a; a = b; b = t;}
#define MUD_ID			(iMUD_NET_D->mud_id())
#define SERVER_ID		(iMUD_NET_D->server_id())

/********************************��ѧ����***********************************/
///�ϴ�ֵ
mixed max2(mixed a, mixed b);
///��Сֵ
mixed min2(mixed a, mixed b);
///���ֵ
mixed max3(mixed a, mixed b, mixed c);
///��Сֵ
mixed min3(mixed a, mixed b, mixed c);
///�����������ѡ��һ��Ԫ��
mixed random1(mixed* arr);
///ϴ��
int* shuffle(int* arr);

/********************************�߼�����***********************************/
///���a�ǿ���a������b��
mixed or2(mixed a, mixed b);
///���a����a������b
mixed and2(mixed a, mixed b);

/********************************�ַ�������***********************************/
///���䶨���ַ���
string allocate_str(int n);
///��������ָ���ַ�λ��
int rfind(string str, int ch);
///ȫ·���е��ļ���
string path_file(string path);
///ȫ·���е�·����
string path_dir(string path);
///������
string neg_direction(string d);
///base64����
string to_base64(int* arr);
///base64����
int* from_base64(string str);

/********************************������***********************************/
///���ұ�����Ҷ���
object player_object(mixed* who);
///���ȫ��ID
string player_gid(mixed* who);
///��ȫ��ID���������Ϣ
mixed* gid_player(string gid);
///Ŀ����ļ���������·����ȱʡΪ��ǰ����
varargs string file_leaf(object ob);
///Ŀ������Ŀ¼�������ļ���
string file_dir(object ob);

/********************************��Ϣ����***********************************/
///��wiz�����������
varargs int trace(string msg, object who);
///��ʾ��Ϣ�������سɹ�
int notify_ok(string msg);
///��ʾ��Ϣ��������̨
varargs int msg_rooms(mixed* rooms, string str, mixed* me, mixed* target);

/********************************���ػ�����***********************************/
//�������+ID
string name_id(mixed* who);


#endif

