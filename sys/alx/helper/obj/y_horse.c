//firefox 11/21/2009

inherit HORSE;

#include <ansi.h>

void create()
{
	set_name(YEL"����͸����"NOR, ({"yellow dragon", "dragon"}));

	set("long", "һƥ���½ý���ս��ͨ��Ȼƣ�ë����ɫ��\n\n");

	set("max_kee", 1000000);
	set("max_sen", 1000000);

	set("combat_exp", 2000);
	set("daoxing", 2000);


	set_skill("dodge", 1000);

	init_horse(35);
}

