
#include "stand.h"

void setup()
{
	set("short", "±±Ìü");
	set("exits", (["south" : iFCS_MAP_DIR "fcs"]));
	::setup();
}
