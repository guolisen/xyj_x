
#include "stand.h"

void setup()
{
	set("short", "����");
	set("exits", (["north" : iFCS_MAP_DIR "fcs"]));
	::setup();
}
