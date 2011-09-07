// by firefox 11/21/2009
// 西游杀-主控服务

#include <xys.h>

string* _rooms = ({	"room0", "room1", "room2", "room3" });	//场地
string* _queue = ({});		//报名玩家id

int new_game();

/********************************初始化***********************************/

void create()
{
	seteuid(getuid());	
}

/********************************玩家报名***********************************/
int do_join(object npc, object who)
{
	string id = getuid(who);

	if(member_array(who, _queue) != -1) 
		return msvx(CYN"$N对$n说道：你已经报名了。\n"NOR, npc, who);

	msvx(CYN"$N对$n说道：漫漫西行路，多少无名骨。\n"NOR, npc, who);
	
	_queue += ({ id });

	if(sizeof(_queue) == MAX_CHAR) new_game();
	
	return 1;
}

/********************************启动阶段***********************************/

//要到一个空场地
object find_room()
{
	foreach(string rid in _rooms) {
		object room = load_object(__DIR__ + rid);
		if(room->state() == 0) return room;
	}
	return 0;
}

//开始一场新战斗
int new_game()
{
	for(int i = 0; i < sizeof(_queue); ++i) {
		object who =  find_player(_queue[i]);
		if(!who) _queue[i] = 0;
	}
	_queue -= ({ 0 });
	if(sizeof(_queue) < MAX_CHAR) return 0;
	
	//玩家入场，开始
	find_room()->invite_all(_queue);
	_queue = ({});
}

/********************************启动阶段***********************************/

//兑现奖励
int do_reward(object npc, object who)
{
	
	return 1;
}
