
#include "stand.h"

void setup()
{
	set("short", "долЭ");
	set("exits", (["north" : iFCS_MAP_DIR "fcs"]));
	::setup();
}
