

#include <xyj_x.h>

#define LEADER			0
#define VLEADER			1
#define TEAM_LEADER		2
#define MUMBER			3


#define G				gang()
#define GANG_ID			(G->query("id"))
#define GANG_NAME		(G->query("name"))

//获取帮派对象
object gang()
{
	string gid = path_file(path_dir(__DIR__));
	return GANG_GET(gid);
}

