// by firefox 11/21/2009

inherit NPC;

#include "arena.h"
#include "cmds.c"


mapping* _camps = ({0, ([]), ([]),});


void create()
{
	seteuid(getuid());
	_status	= DONE;
}


//开始比赛
void start()
{

	if(_status != DONE) return -1;

	_status = INVITE;

	chat(HIG TITLE + "即将开始，请各帮会前来报名。");

	remove_call_out("battle_start");
	call_out("battle_start", 2*60);

	//报名阶段
	//检查选手资格，通告结果
	
	//开始

	//淘汰分组赛
	//决赛
	//奖励

	//比赛，调整出场顺序


}

//小组赛开始
int group_start(int n)
{
	if (_status != INVITE) return -1;

	//初始化阵营
	_camps[XIAN] = ([
		"name"		: "仙界",
		"index"		: XIAN,
		"color"		: HIG,
	]);
	_camps[MO] = ([
		"name"		: "魔道",
		"index"		: MO,
		"color"		: HIR,
	]);

	_status = BATTLE;
	_start_time = time();
	_time = 0;
	
	rumor("小组赛第1轮开始。\n");

	help_init();
	camp_init();
	camp_accept_all();

	set_heart_beat(PULSE);

	//判断是否决出前两名

	if()
		group_start(n++);
	else
		final_start();

	return 1;
}

//决赛开始
int final_start()
{
	//开始两个帮派的比赛
	battle_start(mapping );
}

//两队开战，战斗结束回送结果
int battle_start(mapping team1, mapping team2);
{

}

//两队战斗结束，汇报胜利者
int battle_end()
{}


//控制战斗流程
int process()
{
	//当前比赛是否结束，没结束则等待

	if(_status == GROUP)
	//小组赛是否结束？
		//安排小组赛
	
	if(_status == FINAL)
	//决赛是否结束？
		//安排决赛

	//发放奖励
}


//终止比赛
void stop()
{
	chat(TITLE + "正式落幕。");
	//清除比赛
}




mapping _teams = ([			//参赛报名队伍
	"nmj"		: ([
		"firefox"	: 1000,
		"laipi"	: 1000,
		"laipi"	: 1000,
	])
]);

mixed* _table = ({});		//赛程安排

int do_join(string arg)
{
	string* arr = str_split(arg, ' ');
	foreach(string id in arr) {
		object player = find_player(id);
		//检查帮派，记录起来
	}
	
}

//检查工资帽
void valid()
{	
	mapping exps = ([]);		//各队平均exp
	int sum = 0;				//各队平均exp之和
	int avg = 0;				//各队平均exp的均值

	foreach(string tid, mapping team in _teams) {
		int s = 0;
		foreach(string id, int exp in team) {
			s += exp;
		}
		exps[tid] = s / MAX_NUMBER;
		sum += exps[tid];
	}
	avg = sum / sizeof(_teams);

	{	//筛选超过经验帽的队伍
		int max_exp = avg * MAX_EXP_RATIO / 100;
		foreach(string tid, int exp in exps) {
			if(exp > max_exp) {
				string* arr = keys(_teams[tid]);
				string uid = random1(arr);
				object player = find_player(uid);
				map_delete(_teams[tid], uid);
				if(player) {
					_this->command("chat 删除");
				}
				
			}
		}
	}

	{	//排赛程
		int n = sizeof(_teams);
		string* arr = shuffle(_teams);	//随机排列个队
		string* places = shuffle(places);	//排练比赛场地
		string winners = ({});
		mapping schedule = ();

		if(n % 2) {	//奇数，则出线一个
			winners += ({arr[n - 1]});
		}
		for(int i = 0; i < n/2; ++i) {
			schedule[places[i]] = ({arr[i*2], arr[i*2+1]})
		}
	}
	{
		//创建擂台对象

		//擂台对象，开始，检查位置，结束，超时平局
		
		//每局比赛结束，检查本轮是否结束
		
	}

}
