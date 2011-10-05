
#include "stand.h"

void setup()
{
	set("short", "¶«Ìü");
	set("exits", (["west" : iFCS_MAP_DIR "fcs"]));	
	::setup();
}
