//ȫ������ԭ���еľ��顣pkyou

#include <ansi.h>
inherit ROOM;

int do_reward(object who);


void create ()
{
	set ("short", "��������ɽ����");
	set ("long", @LONG

����ɽ���ϣ�����������һ���ķ�ʯ�ϡ�����ɽ�������Ϸ�
ԶԶ��ȥ������������ӲӵĴ���ҫ�����۶���������

LONG + HIY"            ������ء��ȡ��䡢�ˡ�\n\n"NOR
		);

	set("exits", ([
		"southdown" : __DIR__"shandi",
	]));
	set("outdoors", __DIR__);

	setup();
}

void init()
{
	add_action("do_open", "open");
}

int do_open(string arg)
{
	object env = this_object();
	object who = this_player();
	object letter = present("feng yin", who);
	object guard = present("shan shen", env);
	object shandi = load_object(__DIR__"shandi");
	object prisoner = letter ? find_player(letter->query("prisoner_id")) : 0;

	if( !arg || arg != "zhou" ) 
		return notify_fail("��Ҫ��ʲô��\n");

	if (!letter || letter->query("savior_id") != getuid(who))
		return notify_fail("��û�еõ�����ĵ㻯���޷�����ɽ�¶���Գ��\n");

	if (!prisoner || environment(prisoner) != shandi)
		return notify_fail("ɽ��û��ѹ���ˣ�\n");

	if(!guard && !who->query_temp("kill_guard")) {
		guard = new(__DIR__"guard");
		guard->move(env);
		guard->copy_status(who);
		message_vision(CYN"$N��Ҫȥ�ҿ������ͻȻ��ǰ������һ���ˡ�\n"NOR, who);
		who->set_temp("kill_guard", 1);
		return 1;
	}
	if(guard) {
		message_vision(CYN"$n��ס$N˵�������ɷ��������������������ϵ��¶�Ҫ���꣡\n"NOR, who, guard);
		return 1;
	}

	tell_object(prisoner, WHT"��ͻȻ�о������ظ�����������˺ܶࡣ\n"NOR);

	set ("short", "����ɽ��");

	message_vision("$NС��������ӡ����������\n", who);
	message_vision(HIY"��ӡͻȻ����һ��ǿ�ҵĽ�⣬�յ����������ۡ�\n"NOR, who);
	message_vision("�Ƚ����ȥ��$N����" + letter->name() + "��ʧ����Ӱ���٣�\n", who);
	destruct(letter);
	who->delete_temp("kill_guard");
	do_reward(who);
	return 1;
}

//������
int do_reward(object who)
{
	//��Ҹ�ȱǱ�ܣ����в��ý����˰ɣ�
	who->add("potential",1000);
	//����Ҫ����һ���������Եļ��ܻ���ָ����������޸ĵĴ����칬��10�����͵Ļ��۽���һ����
	//  tell_object(who,"�Ƚ����ȥ��\n");
	tell_object(who, sprintf("����һ��ʤ���߼���������ϲ�㣡��ѧ���ˡ��������Խ����䡿��\n"NOR) );

	
}


