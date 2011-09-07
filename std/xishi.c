// by firefox 04/02/2010
// 长安西市

#include <xyj_x.h>

inherit ROOM_SBC;

void create ()
{	
	set("short", "西市");

	set("exits", ([
		"east" : __DIR__"beiyin1",
	]));

	setup();

	set("long", "

长安西市占地1600亩，220行，商贾云集，贸易兴隆，是世界的商业贸
易中心。“四方珍奇，皆所积集，北买党项马，西擒吐番鹦”。门口一张
告示(gaoshi)，想必是官家的规则。

");

	set("item_desc", ([	"gaoshi": "
诚信买卖，欺诈重罚：
--------------------------------------
查看：  list [名称 | ID | 物主ID]
购买：  mai 商店序号
寄售：  sell 物品ID 要价
"
	]) );
}
