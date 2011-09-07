// by firefox 11/21/2009

inherit __DIR__"skill_book";

void create()
{
	set(SKILL_PROP, "skyriver-rake");
	::create();
	set("is_monitored",1);
}

