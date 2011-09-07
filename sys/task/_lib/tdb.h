// by firefox 04/10/2010
// 任务数据库

//加载任务列表，可被重写
int tdb_load(string file);

//获取任务列表
mapping tdb_data(object who);

//获取任务索引列表
int* tdb_keys(object who);
