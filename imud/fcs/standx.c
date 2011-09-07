
inherit ROOM;

mapping _exits = ([
	"east"		: __DIR__"stand0",
	"south"		: __DIR__"stand1",
	"west"		: __DIR__"stand2",
	"north"		: __DIR__"stand3",
]);

void create()
{
	string localizer = __DIR__"localizer";	

	localizer->setup_corridor(this_object());
	set("exits", _exits + query("exits"));

	setup();
}
