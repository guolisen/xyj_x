// by firefox 04/10/2010
// 简单任务数据库

#include "tdb.h"

mapping _data;						//任务数据库
int* _keys;


//加载任务列表，可被重写
int tdb_load(string file)
{
	_data = ([]) + file->data();		//复制一份数据
	_keys = sort_array(keys(_data), 1);
}

//获取任务列表
mapping tdb_data(object who)
{
	return _data;
}

//获取任务索引列表
int* tdb_keys(object who)
{
	return _keys;
}

