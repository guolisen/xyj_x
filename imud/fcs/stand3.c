
#include "stand.h"

void setup()
{
	set("short", "����");
	set("exits", (["south" : iFCS_MAP_DIR "fcs"]));
	::setup();
}
