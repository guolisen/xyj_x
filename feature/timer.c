// by firefox 11/21/2009
// 定时器，heart_beat的限制是必须有玩家在线

#include <xyj_x.h>

int _timer_interval;
int _timer_end_time;
int _timer_arg;

void create()
{
	seteuid(getuid());
}

//停止定时器
int timer_stop()
{
	remove_call_out("timer_on_timer");
}

//开始定时器
varargs string timer_start(int interval, int duration, mixed arg)
{
	_timer_interval = max2(interval, 1);
	_timer_end_time = duration ? time() + duration : 0x7fffffff;
	_timer_arg = arg;

	timer_stop();
	call_out("timer_on_timer", _timer_interval);
}



//虚函数，定时器过程，定时调用，如果返回-1则定时器停止
int timer_process(mixed arg)
{
}

private void timer_on_timer()
{
	if(time() <= _timer_end_time && timer_process(_timer_arg) != -1)
		call_out("timer_on_timer", _timer_interval);
}

