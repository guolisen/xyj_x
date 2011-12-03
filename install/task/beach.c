
#include <xyj_x.h>
#include <ansi.h>

inherit ROOM;

string dest = __DIR__"beach-stone";

void flood();
void _flood(object);

void create ()
{
	set ("short", "东海海滩");
	set ("long", @LONG

夜间的大海，海水如墨，风平浪静。月光在海面上划出一道银光，给安静
的海面增加了一丝生机。然而就在这宁寂的表面下，海水深处暗涛汹涌，
水声隆隆，似乎要将一切生命吞噬。岸边崖壁上到处都是风化的乱石。

LONG);

	set("outdoors", 1);
	set("exits", ([
		"west" : __DIR__"eastseashore",
		"east" : this_object(),
	]));

	setup();
	call_out("flood", 21 + random(20));
}

void flood()
{
	call_out("flood", 61 + random(60));

	tell_room(this_object(), "涨潮了，海水发出震耳欲聋的巨吼声，万马奔腾般向你扑来！\n");
	foreach(object who in all_inventory())
		if(userp(who)) _flood(who);
}

void _flood(object me)
{
	object corpse;

	if(!me->query("life/live_forever")) {
		message_vision("$N被潮水冲走了。\n\n", me);
		me->set_temp("death_msg","掉进东海淹死了。\n");

		me->die();
		me->delete_temp("death_msg");
		corpse = present("corpse", this_object());
		if(corpse && corpse->move(dest))
			tell_room(environment(corpse),"潮水将"+corpse->name()+"冲上岸来。\n");
		return;
	}
	if(random(me->query_kar()) > 6) {
		message_vision("$N一提气，轻轻一跃，落在礁石上，海水呼啸着从$N脚下漫过，好险！\n\n", me);
		return;
	}
	message_vision("$N被潮水冲走了。\n\n", me);

	me->unconcious();
	if(me->move(dest))
		tell_room(environment(me), "潮水将"+me->name() + "冲上岸来。\n");
}

void init()
{
	add_action("do_fill", "fill");
}

int do_fill(string arg) 
{
	object me = this_player();
	int phase = NATURE_D->query_current_day_phase();
	int pot = me->query_skill("spells") / 10;

	if(!arg && arg!="hai" && arg!="sea") return notify_fail("你要填什么？\n");
	if(me->is_fighting() || me->is_busy()) return notify_fail("你正忙着呢。\n");	
	if(phase < 6) return notify_fail("白天天气太热了，晚上再来吧。”\n");

	message_vision("$N从岸边搬起一块石头投入海中，石块迅速沉入水中，连水花都没激起半点。\n",me);
	write("你累得腰酸背痛，连手臂都抬不起来。\n\n");
	//检查配额
	if(TASK_EXC->do_reward(me, "精卫", "填海", ([ PEXP : pot ]) ))
		me->add("potential", pot);
	me->start_busy(8/4);
	return 1;
}

