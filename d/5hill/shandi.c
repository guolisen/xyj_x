
#include <ansi.h>
inherit ROOM;

#define DNTG11			"dntg11"	//dtng 11�ر��
#define DNTG12			"dntg12"	//dtng 12�ر��

#define IN_PRISON		(5*3600/100)	//����ʱ��
#define SEND_LETTER		600/10			//���ż��

#define TERM			"prison_term"



//����̫��δ�������壬����ͨ�����׺�
//��ô��ʱ��̫��ĥ���ˣ���������������

string* _verbs = ({			//����ָ��
	"chat", "tell", 
	"look", "inventory", "hp",
	"exert", "exercise", "meditate", "eat",
	"quit",
	"call", "update",
});

void check_time(object who);
int do_break(string arg);
int do_say(string arg);
void send_letter(object who);
string name_id(object who);
void show_pusa(object who);

void create ()
{
	set ("short", "��������ɽ��");
	set ("long", @LONG

̫��ɽ����������ɽ����ĸɽ��Ů�ɽ����˵�������ǰ
�������潫��ָ������ľ��ˮ������������ɽ������
������ɽ���������칬��������ѹ����ָɽ�£�ֻ����崣
�𣬹�ʯ��ᾣ����﷼�����£���ľ������ 


LONG);

	set("exits", ([
		"east"		: __DIR__"shandi",
		"west"		: __DIR__"shandi",
		"northup"	: __DIR__"shanding",
	]));

	set("outdoors", __DIR__);
	set("valid_startroom", 1);

	setup();
}

void init()
{
	object who = this_player();

	add_action("exec_cmd", "", 1);

	if((who->query(DNTG11) == "done") && (who->query(DNTG12) != "done")) {
		who->set("startroom", base_name(this_object()));
		who->set(TERM"/start", time());

		who->set_temp("apply/short", ({ name_id(who) + HIR" <��ѹ��ɽʯ��>"NOR }));

		who->set_temp("apply/long", ({ @LONG

��ѹ��ɽʯ�У�¶��ͷ�������֡�ͷ�϶�̦޺��������޵
�ܡ��ޱ��ٷ�����ݣ������������ɯ��ü�������ǰ���
ʮ���Ǳ���ָͷ�֣����ƺ񣬳�����ࡣ

LONG }));
		check_time(who);
	}
}

//���δ��������
int exec_cmd(string arg)
{
	object who = this_player();
	string verb = query_verb();

	if(!who->query(TERM)) return 0;

	check_time(who);
	if(member_array(verb, _verbs) >= 0) return 0;

	if(verb == "break") return do_break(arg);
	if(verb == "say") return do_say(arg);
	write("����ɽ����ѹס�������ɼ���\n");
	return 1;
}

//�������ʱ��
void check_time(object who)
{
	//�ۼ�����ʱ��
	int elapse = time() - who->query(TERM"/start");
	who->add(TERM"/elapse", elapse);
	who->set(TERM"/start", time());

	if(wizardp(who))
		printf("[bebug]:ʱ������: %d��\n", who->query(TERM"/elapse"));

	//�����ͷ�
	if(who->query(TERM"/elapse") > IN_PRISON
		&& !who->query_temp(TERM"/sending"))
	{
		who->set_temp(TERM"/sending", 1);
		show_pusa(who);
	}
}

//���������
void send_letter(object who)
{
	object letter = new(__DIR__"letter");
	object* players = users();
	object savior;

	if(!who || !who->query(TERM)) return 0;

	while(1) {
		savior = players[random(sizeof(players))];
		if (savior && savior != who					//��wiz���ڲ��ԣ�Ҳûʲô���˵�
			&& savior->query("combat_exp") > 500) break;
	}
	if(letter->move(savior)) {
		letter->set("savior_id", getuid(savior));
		letter->set("prisoner_id", getuid(who));		

		tell_object(who, HIG"������ѹ������ɽ�׶������á�\n",);
		tell_object(who, HIG"ֻ��" + name_id(savior) + "���ܽ������ɽ�ķ��䡣\n"NOR);

		tell_object(savior,  HIG + name_id(who) + "���ڱ�������ɽ�£�ֻ������ܵ�����ɽ������䡣\n"NOR);
		tell_object(savior,  HIY"һ���ƾ�������Ʈ����������ϡ�\n"NOR);
	}
	call_out("send_letter", SEND_LETTER, who);
}

int do_break(string arg)
{
	object env = this_object();
	object who = this_player();
	object shanding = load_object(__DIR__"shanding");
	int str = who->query("force_factor")*5 + who->query("str");

	if(!who->query(TERM)) return 0;
	if(shanding->query("short") != "����ɽ��")
		return notify_fail("���������������ɽʯѹ�������ġ�\n");

	message_vision("$Nʹ�����̵������������ɽ�����������\n", who);

	if( str > 300)
		tell_room(env, "����ɽ��ʼ�ζ�������\n");
	else if( str > 200)
		tell_room(env, "����ɽ�������죬�ƺ���Ҫ�����ˡ�\n");
	else if( str > 100)
		tell_room(env, "����ɽ�����ѿ���һ������ӡ�����\n");
	else
		tell_room(env, "ֻ������ɽ��¡¡����ȴ������˿��ҡ����\n");

	env->add("break", str);
	who->receive_damage("kee", 30);
	who->add("force", - who->query("force_factor"));
	if( who->query("force") < 0 )who->set("force", 0);

	if ( env->query("break") > 3000 ){
		tell_room(env,"����ɽ�����ѿ���һ������ӣ����ǿ�Ҫ�����ˡ�\n");
		env->delete("break");
		set("long", @LONG

�����ɳ���죬������������ʯ���У���������۶ϵ���ָһ����ɽ���������˵Ľ����š�

LONG);
		shanding->set("short", "��ʯ��");
		shanding->set("long", @LONG

����ֱ����������ָɽ�Ѿ�����������ֻʣһ����ʯ��

LONG);
		tell_room(shanding, HIW"һ�����쾪�춯�أ�������ָɽ��Ȼ������\n"NOR);
		message_vision(HIW"һ�����쾪�춯�أ�������ָɽ��Ȼ������$N��ʯ������\n\n"NOR, who);

		who->delete_temp("apply/short");
		who->delete_temp("apply/long");		
		who->set(DNTG12, "done");
		who->delete(TERM);
		//todo:����12�سɹ�
		who->command("chat "HIY"500�����������ճ����ˣ���л��������̨...");
		who->command("chat "HIY"���Ӵ�����ҷ�̤��ȡ��·��");
	}
	return 1;
}

//�û�����ID
string name_id(object who)
{
	return who->query("name") + "(" + capitalize(who->query("id")) + ")";
}

object _pusa;
object _huian;

void show_pusa(object who)
{
	object env = this_object();

	_pusa = new(__DIR__"pusa");
	_huian = new(__DIR__"huian");

	_pusa->move(env);
	_huian->move(env);

	tell_room(env, CYN + @LONG

��ɽ����������һ��ʫ��


          ��̾���ﲻ������������Ӣ�ۡ�
          ���Ľ�����һᣬ��˽�ж��ʹ���
          ʮ������޵��֣��������������硣
          �����ҷ��������������������Թ���


���������ͻݰ�������ɽ���������¡�

���������ϵ���ô��
LONG + NOR);


	who->set_temp("pusa/stage", ({1, ({"�ϵ�", "��"})}));
}

private int say(object who, string msg)
{
	message_vision(CYN"$N˵����" + msg + "\n"NOR, who);
}

int do_say(string arg)
{
	object who = this_player();
	mixed* stage = who->query_temp("pusa/stage");
	int answer_ok = 0;

	if(!arg || !stage) return 0;

	//�ж�ʱ����ȷ�Ļش���ָ���Ĺؼ���
	foreach(string word in stage[1]) {
		if(strsrch(arg, word) >= 0) answer_ok = 1;
	}
	if(!answer_ok) return 0;
	if(wizardp(who)) printf("[bebug]:stage[0]:%d\n", stage[0]);

	switch(stage[0]) {
	case 1:		
		say(who, "�ϵã����ǹ�����������ѹ�ڴ�ɽ������꣬��֪���ˣ�������������һ�ȣ�");
		say(_pusa, "����д��ģ�����Ѱȡ�����������������㣬��������ͽ�ܡ�");
		say(_pusa, "����ţ�����������Σ�");
		who->set_temp("pusa/stage", ({2, ({"��", "Ը"})}));
		break;
	case 2:
		say(who, "�ã�Ըȥ��Ըȥ��");
		_pusa->command("nod");
		message_vision(HIY"$N�������һ���������$nͷ�������ɢȥ��$nͷ�϶���һ���𹿡�\n"NOR, _pusa, who);
		message_vision(CYN"$N�ͻݰ����߲������ƣ��������ա�\n"NOR, _pusa);
		send_letter(who);
		destruct(_pusa);
		destruct(_huian);
		who->delete_temp("pusa/stage");
		//todo:����
		break;
	}		
	return 1;
}
