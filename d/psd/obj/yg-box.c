// by firefox 02/21/2010

#include <xyj_x.h>
#include <ansi.h>

inherit ITEM;
inherit F_LOADABLE;

#define DEST		X_DIR"d/psd/yard"

void create()
{
	set_name("�¹ⱦ��", ({"yueguang baohe", "baohe", "box"}));
	set_weight(100);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", @LONG

һֻ�����εĺ��ӣ�����д�š����������⻪���Դ���ʱ�ա�������һ��
���ģ������������ܡ���

LONG);
		set("unit", "ֻ");
		set("value", 10);
	}

	setup();
}

void init()
{
	add_action("do_say", ({ "say", "nian" }) );	
}

int do_say(string arg)
{
	object env = environment(_player);
	object dest = load_object(DEST);
	string* arr = ({
		CYN"$N˵�����ۣ���������\n\n"NOR,
		CYN"$N˵�����ۣ�����������\n$N˵�����ţ� ��ΪʲôҪ˵���֡� �أ�\n\n"NOR,
	});

	if(arg != "����������"
		|| !at_night()
		|| !env->query("outdoors")
		|| _player->is_busy()
	) return 0;

	msv(CYN"$N���������������\n\n"NOR, _player);	
	msv(HIR"һ�������콵��$N��ʧ�ڿ��С�\n"NOR, _player);

	foreach(object who in all_inventory(env)) {
		if(who->query("race") == "����" && !userp(who) && living(who)) {
			msv(arr[random(3)> 0], who);			
			break;
		}
	}

	_player->move(DEST);
	_player->start_busy(2);
	
	msv(CYN"���������$N���ڵ��ϡ�\n"NOR, _player);
	return 1;
}

