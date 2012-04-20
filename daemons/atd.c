// by firefox 11/21/2009
// 定时执行服务

#include <xyj_x.h>
#include <localtime.h>

//常量定义
#define DOR				__DIR__"dor"

/********************************数据定义***********************************/
int _tick = 0;

//需要启动就加载的对象
mixed* _load = ({
	ACTOR_D,
	//HOLIDAY,
});

//指定时间启动的对象，精度1分钟（对象，启动时间，例外时间）
mixed* _time = ({
	
	//每日零点，检查节日
	//({ HOLIDAY,	([ LT_HOUR : 0, LT_MIN : 0, ]),	0 }),

	//从第2分钟开始，每20分启动一次，修复buff
	({ BUFF,	({ 20, 2 }),	0 }),

	({ ACTOR_D,	({ 20, 6 }),	0 }),

	//每天20:50，除周六
	//({ ALX,		([ LT_HOUR : 20, LT_MIN : 55 ]),	([ LT_WDAY : 6 ]) }),
	//周六20:50
	//({ ARENA,	([ LT_HOUR : 20, LT_MIN : 50, LT_WDAY : 6 ]),	0 }),

	//({ ALX,		([ LT_MIN : 55 ]),	0 }),
	({ ALX,		([ LT_HOUR : 12, LT_MIN : 15 ]),	0 }),
	({ ALX,		([ LT_HOUR : 20, LT_MIN : 55 ]),	0 }),
	
	//测试
	
});

//todo:加入只执行一次的任务(key,过期时间)，或许只执行一次的任务，由节日本身处理？
mixed* _once = ({});

/********************************函数定义***********************************/

void create()
{
	mixed* lt = localtime(time());
	
	seteuid(getuid());
	set_heart_beat(7);	//7减少和其他心跳重合
	
	_tick = lt[LT_MIN];
	
	//启动需要立即加载的对象
	foreach(string file in _load) {
		object ob = load_object(file);
		if(ob) ob->start();
	}
}

//匹配时间的各子项
private int time_match(mixed* lt, mixed time)
{
	if(!time) return 0;
	if(mapp(time)) {			//定点
		foreach(int k, int v in time) {
			if(lt[k] != v) return 0;
		}
	} 
	else if(arrayp(time)) {		//定间隔(分钟)
		if(_tick % time[0] != time[1]) return 0;
	}
	return 1;
}

//触发定时器
void heart_beat()
{
	mixed* lt = localtime(time());

	if((_tick - lt[LT_MIN]) % 60 == 0) return;
	
	_tick++;
	
	foreach(mixed* arr in _time) {
		if(time_match(lt, arr[1]) && !time_match(lt, arr[2])) {
			object ob = load_object(arr[0]);
			if(ob) ob->start();
		}
	}
}

//测试
void start()
{
	trace("atd.c tick " + _tick, D_WIZ);
}

