
#include "stand.h"

void setup()
{
	set("exits", (["east" : __DIR__"standx"]));	
	::setup();
}
