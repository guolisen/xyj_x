// by firefox 11/21/2009
// 生命函数计时

#include <xyj_x.h>

int _life_end;
string _life_msg;

varargs int life_start(int duration, string dest_msg)
{
	_life_end = time() + duration;
	_life_msg = dest_msg;
	return _life_end;
}

int life_check_end()
{
	if(time() > _life_end) {
		if(_life_msg) msv(_life_msg, _this);
		destruct(_this);
		return 1;
	}
	return 0;
}

