// by firefox 11/21/2009
// ����ɱ-���ط���

#include <xys.h>

string* _rooms = ({	"room0", "room1", "room2", "room3" });	//����
string* _queue = ({});		//�������id

int new_game();

/********************************��ʼ��***********************************/

void create()
{
	seteuid(getuid());	
}

/********************************��ұ���***********************************/
int do_join(object npc, object who)
{
	string id = getuid(who);

	if(member_array(who, _queue) != -1) 
		return msvx(CYN"$N��$n˵�������Ѿ������ˡ�\n"NOR, npc, who);

	msvx(CYN"$N��$n˵������������·�����������ǡ�\n"NOR, npc, who);
	
	_queue += ({ id });

	if(sizeof(_queue) == MAX_CHAR) new_game();
	
	return 1;
}

/********************************�����׶�***********************************/

//Ҫ��һ���ճ���
object find_room()
{
	foreach(string rid in _rooms) {
		object room = load_object(__DIR__ + rid);
		if(room->state() == 0) return room;
	}
	return 0;
}

//��ʼһ����ս��
int new_game()
{
	for(int i = 0; i < sizeof(_queue); ++i) {
		object who =  find_player(_queue[i]);
		if(!who) _queue[i] = 0;
	}
	_queue -= ({ 0 });
	if(sizeof(_queue) < MAX_CHAR) return 0;
	
	//����볡����ʼ
	find_room()->invite_all(_queue);
	_queue = ({});
}

/********************************�����׶�***********************************/

//���ֽ���
int do_reward(object npc, object who)
{
	
	return 1;
}
