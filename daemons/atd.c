// by firefox 11/21/2009
// ��ʱִ�з���

#include <xyj_x.h>
#include <localtime.h>

//��������
#define DOR				__DIR__"dor"

/********************************���ݶ���***********************************/
int _tick = 0;

//��Ҫ�����ͼ��صĶ���
mixed* _load = ({
	ACTOR_D,
	//HOLIDAY,
});

//ָ��ʱ�������Ķ��󣬾���1���ӣ���������ʱ�䣬����ʱ�䣩
mixed* _time = ({
	
	//ÿ����㣬������
	//({ HOLIDAY,	([ LT_HOUR : 0, LT_MIN : 0, ]),	0 }),

	//�ӵ�2���ӿ�ʼ��ÿ20������һ�Σ��޸�buff
	({ BUFF,	({ 20, 2 }),	0 }),

	({ ACTOR_D,	({ 20, 6 }),	0 }),

	//ÿ��20:50��������
	//({ ALX,		([ LT_HOUR : 20, LT_MIN : 55 ]),	([ LT_WDAY : 6 ]) }),
	//����20:50
	//({ ARENA,	([ LT_HOUR : 20, LT_MIN : 50, LT_WDAY : 6 ]),	0 }),

	//({ ALX,		([ LT_MIN : 55 ]),	0 }),
	({ ALX,		([ LT_HOUR : 12, LT_MIN : 15 ]),	0 }),
	({ ALX,		([ LT_HOUR : 20, LT_MIN : 55 ]),	0 }),
	
	//����
	
});

//todo:����ִֻ��һ�ε�����(key,����ʱ��)������ִֻ��һ�ε������ɽ��ձ�����
mixed* _once = ({});

/********************************��������***********************************/

void create()
{
	mixed* lt = localtime(time());
	
	seteuid(getuid());
	set_heart_beat(7);	//7���ٺ����������غ�
	
	_tick = lt[LT_MIN];
	
	//������Ҫ�������صĶ���
	foreach(string file in _load) {
		object ob = load_object(file);
		if(ob) ob->start();
	}
}

//ƥ��ʱ��ĸ�����
private int time_match(mixed* lt, mixed time)
{
	if(!time) return 0;
	if(mapp(time)) {			//����
		foreach(int k, int v in time) {
			if(lt[k] != v) return 0;
		}
	} 
	else if(arrayp(time)) {		//�����(����)
		if(_tick % time[0] != time[1]) return 0;
	}
	return 1;
}

//������ʱ��
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

//����
void start()
{
	trace("atd.c tick " + _tick, D_WIZ);
}

