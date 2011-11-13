// by firefox 03/27/2010

#ifndef __XYJ_X_H__
#define __XYJ_X_H__

// Directories

#define X_DIR				"/d/xyj_x/"
#define X_DATA_DIR			"/d/xyj_x/data/"

// Mixins

#define IMMORTAL_H			"/d/xyj_x/include/immortal.h"


// Daemons

#define ADMX_D				"/adm/daemons/admxd"
#define ACTOR_D				X_DIR"daemons/actord"
#define AT_D				X_DIR"daemons/atd"

// Clonable/Non-inheritable Standard Objects

#define CMD_HOOK			X_DIR"obj/fabao/cmd-hook"


// Inheritable Standard Objects

#define ROOM_SBC			X_DIR"std/sbc"
#define GUARD				X_DIR"std/guard"
#define BIAN				X_DIR"std/bian"

// Features

#define F_CMD				X_DIR"feature/cmd"
#define F_RDB				X_DIR"feature/rdb"
#define F_LOADABLE			X_DIR"feature/loadable"
#define F_TIMER				X_DIR"feature/timer"
#define F_FOT				X_DIR"feature/fot"
#define F_VECTOR			X_DIR"feature/vector"
#define F_DATA_OF			X_DIR"feature/data_of"
#define F_ELEMS				X_DIR"feature/elems"
#define F_MOVE_TO			X_DIR"feature/move_to"
#define F_IP2ID				X_DIR"feature/ip2id"
#define F_GREET				X_DIR"feature/greet"
#define F_LIFE				X_DIR"feature/life"
#define F_NO_CLEAN_UP		X_DIR"feature/no_clean_up"

// Constant

#define	XYJ_X				"xyj_x"
#define	K					1000
#define	M					1000000
#define MINUTE				30												//每分钟心跳数
#define HB2MS				2000											//每心跳毫秒数
#define SEC_PER_HB			2												//每心跳秒数
#define	CEXP				"combat_exp"
#define	DEXP				"daoxing"
#define	PEXP				"potential"
#define LINE1				"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
#define LINE2				"------------------------------------------------------------------------------\n"

// User IDs

#define ROOT_UID1			"Root"


// User Defined Functions
#define UFUN_DIR			X_DIR"ufun/"
#define BUFF				UFUN_DIR"buff"
#define BTL					UFUN_DIR"battle"
#define MSG					UFUN_DIR"message"
#define MATH				UFUN_DIR"math"
#define STRING				UFUN_DIR"string"
#define PLACE				UFUN_DIR"place"
#define GNAME				UFUN_DIR"gname"
#define COLOR				UFUN_DIR"color"
#define DB					UFUN_DIR"db"
#define HP					UFUN_DIR"hp"
#define SKI					UFUN_DIR"skill"
#define PY					UFUN_DIR"py"
#define FAMILY				UFUN_DIR"family"
#define DIRECTION			UFUN_DIR"direction"
#define UTIL				UFUN_DIR"util"
#define SCREEN				UFUN_DIR"screen"
#define TRANSLATOR			UFUN_DIR"translator"
#define LCALENDAR			UFUN_DIR"lcalendar"
// Sub Systems

//文档系统
#define DOC_D				X_DIR"daemons/docd"
#define FAQ_D				X_DIR"daemons/faqd"


//真身转世系统
#define RACE				X_DIR"sys/race"
#define REI					X_DIR"sys/rei"
#define FABAO				X_DIR"sys/fabao"


//声望系统
#define FAME_PROP			"sys_fame"

//任务系统
#define TASK_PROP			"sys_task"
#define TASK_DIR			X_DIR"sys/task/"
#define TASK				X_DIR"sys/task"
#define TASK_GET(gid, tid)	(TASK_DIR + (gid) + "/" + (tid))
#define EMPLOYER			TASK_DIR"_lib/employer"
#define TT_BASE				TASK_DIR"_lib/tt-base"
#define TT_Q4				TASK_DIR"_lib/tt-q4"
#define TT_QUEST			TASK_DIR"_lib/tt-quest"
#define TT_GROUP			TASK_DIR"_lib/tt-group"

#define TASK_EXC			TASK_GET("misc", "exchange")

#define TDB_SIMPLE			TASK_DIR"_lib/tdb-simple"
#define TDB_FAMILY			TASK_DIR"_lib/tdb-family"

//战场系统
#define ALX_PROP			"sys_alx"
#define ALX_DIR				X_DIR"sys/alx/"
#define ALX					ALX_DIR"alx"

//西游杀
#define XYS_PROP			"sys_xys"
#define XYS_DIR				X_DIR"sys/xys/"
#define XYS					XYS_DIR"xys"

//帮会
#define GANG_PROP			"sys_gang"
#define GANG_DIR			X_DIR"sys/gang/"
#define GANG				X_DIR"sys/gang"
#define GANG_GET(gid)		(GANG->find(gid))


//联赛
#define ARENA_PROP			"sys_area"
#define ARENA_DIR			X_DIR"sys/area/"
#define ARENA				ALX_DIR"area"

//节日
#define HOLIDAY				X_DIR"sys/holiday"

//引入常用宏
#include "macros.h"

#endif


