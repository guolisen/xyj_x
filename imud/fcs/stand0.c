
#include "stand.h"

void setup()
{
	set("exits", (["west" : __DIR__"standx"]));	
	::setup();
}
