
#include "stand.h"

void setup()
{
	set("exits", (["north" : __DIR__"standx"]));	
	::setup();
}
