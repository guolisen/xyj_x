// by firefox 09/14/2010

#include <xyj_x.h>

inherit TT_QUEST;
inherit TDB_SIMPLE;

void create()
{
	init_param(800, 500, 600, 100);		//���7��ƽ�����棺800*7*150% = 8.4K�����16.5
	tdb_load(X_DATA_DIR + "task/quest/_" + id());
}


