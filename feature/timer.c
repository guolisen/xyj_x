// by firefox 11/21/2009
// ��ʱ����heart_beat�������Ǳ������������

#include <xyj_x.h>

int _timer_interval;
int _timer_end_time;
int _timer_arg;

void create()
{
	seteuid(getuid());
}

//ֹͣ��ʱ��
int timer_stop()
{
	remove_call_out("timer_on_timer");
}

//��ʼ��ʱ��
varargs string timer_start(int interval, int duration, mixed arg)
{
	_timer_interval = max2(interval, 1);
	_timer_end_time = duration ? time() + duration : 0x7fffffff;
	_timer_arg = arg;

	timer_stop();
	call_out("timer_on_timer", _timer_interval);
}



//�麯������ʱ�����̣���ʱ���ã��������-1��ʱ��ֹͣ
int timer_process(mixed arg)
{
}

private void timer_on_timer()
{
	if(time() <= _timer_end_time && timer_process(_timer_arg) != -1)
		call_out("timer_on_timer", _timer_interval);
}

