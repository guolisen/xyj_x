
#include "stand.h"

void setup()
{
	set("short", "����");
	set("exits", (["west" : iFCS_MAP_DIR "fcs"]));	
	::setup();
}
