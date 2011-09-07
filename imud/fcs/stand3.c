
#include "stand.h"

void setup()
{
	set("exits", (["south" : __DIR__"standx"]));	
	::setup();
}
