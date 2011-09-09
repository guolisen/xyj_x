// by firefox 09/14/2010

#include <xyj_x.h>

inherit TT_QUEST;
inherit TDB_SIMPLE;

void create()
{
	init_param(990, 600, 780, 100);		//最高7花平均收益：990*7*150% = 10.3K 最大：14.5K
	tdb_load(X_DATA_DIR + "task/quest/_" + id());
}


