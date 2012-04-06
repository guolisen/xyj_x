// by snowcat 7/5/1997

inherit ROOM;
inherit F_SAVE;

#include <xyj_x.h>

static int room_status = 0;
static int *big = allocate(2);
static int *res = allocate(2);

#define G		10000

static int _total = 0;
mapping _account = ([]);

int rdm0() { return random(6) + 1; }

int rdmx(int i)
{
	string* arr = ({"string", "mem", "nodes", "mappings", "objects", "callout"});
	int n = 0;

	if(_total < 1*G) return rdm0();
	else if(_total < 100*G) n = 1;
	else if(_total < 1000*G) n = 2;
	else if(_total < 2000*G) n = 3;
	else if(_total < 5000*G) n = 4;
	n = STATUS->query(arr[n + i]);
	return (random(6) + n) % 6 + 1;
}

string query_save_file()
{
	return DATA_DIR "npc/duchang2";
}

int remove()
{
	save();
	return 0;
}



mapping gutous = ([ "tc" : "ͷ��", "sd" : "˫��", "qx" : "����", "sx" : "ɢ��" ]); 

void create()
{
	restore();

	set("short", "������");
	set("long", @LONG

�������һ�����������м����һ�����̡��Ŀ������۾�������¶ġ�
��ϯ��һλ���ӣ����ﲻ����Ū��һ�������������������ׯ����

ǽ�Ϲ���һ���ң�����д�ţ�
    ͷ�ʣ�������ÿ�ο���ǰȷ����      ��һӮ��ʮ��
    ˫�ԣ���������ͬ����Ϊż����      ��һӮʮ��
    ���ǣ�����֮��Ϊ�ߣ�              ��һӮ��
    ɢ�ǣ�����֮��Ϊ�����壬�ţ�ʮһ����һӮ��

�ҽ���һ������(paizi)��

LONG);

	set("item_desc",([
		"paizi" : "Ѻͷ������ gutou tc <amount> <money>\n"+ 
			"Ѻ˫������ gutou sd <amount> <money>\n"+ 
			"Ѻ�������� gutou qx <amount> <money>\n"+ 
			"Ѻɢ������ gutou sx <amount> <money>\n" 
	])); 
	set("objects", ([ /* sizeof() == 1 */
		__DIR__"npc/zhuangd" : 1,
	]));
	set("exits", ([ /* sizeof() == 1 */
		"west" : __DIR__"clubup",
	]));
	set("light_up", 1);
	set("no_fight", 1);
	set("no_magic", 1);
	setup();
}

void init ()
{
	//add by ajax to avoid use dummy carry player in&out
	object me = this_player();
	if (me) me->delete_temp("gamble_gutou");

	add_action ("do_gutou","gutou");
	add_action ("do_bian","bian");
	add_action ("do_get","get");

	if(wizardp(me)) add_action ("do_state","state");

	if (room_status > 0)
		return;

	remove_call_out ("gamble_prepare");
	remove_call_out ("gamble_start");
	remove_call_out ("gamble_perform");
	remove_call_out ("gamble_finish");
	call_out ("gamble_prepare",2);
	room_status = 1;
}

int do_gutou (string arg)
{
	object me = this_player();
	string what;
	int amount, value;
	string money;
	object ob;

	if (! arg ||
		sscanf (arg,"%s %d %s",what,amount,money) != 3)
		return notify_fail("��ʹ�ã� gutou <Ѻ������> <��Ŀ> <����>\n");

	if (what != "tc" &&
		what != "sd" &&
		what != "qx" &&
		what != "sx")
		return notify_fail("��ҪѺʲô����\n");

	if ( money == "cash" ) money ="thousand-cash";
	ob = present (money+"_money", me);
	if (! ob)
		return notify_fail("������û�����ֻ��ҡ�\n");
	if (amount < 1)
		return notify_fail("���ѺһЩǮ��\n");
	if (amount > ob->query_amount())
		return notify_fail("�����ϵ�Ǯ����Ѻ��\n");

	if (me->query_temp ("gamble_gutou/amount") > 0)
		return notify_fail("���Ѿ�Ѻ���ˡ�\n");

	if (room_status > 1)
		return notify_fail("�������ڶ��أ��Ե�Ƭ�̡�\n");	

	me->set_temp("gamble_gutou/kind",what);
	me->set_temp("gamble_gutou/amount",amount);
	me->set_temp("gamble_gutou/money",money);
	message_vision (sprintf("$N�ó�%s%s%s��Ѻ��%s�ϡ�\n",
		chinese_number(amount),
		ob->query("base_unit"),
		ob->query("name"),
		gutous[what]),
		me);
	
	value = ob->query("base_value") * amount / 100;				//firefox 2012-4-1
	_total += value;
	_account[getuid(me)] -= value;

	if (amount == ob->query_amount())
		destruct (ob);
	else
		ob->add_amount(-amount);

	return 1;
}

int valid_leave(object me, string dir)
{
	if (dir == "west")
	{
		if (me->query_temp ("gamble_gutou/amount") > 0) 
			message_vision ("$N����Ѻ����Ǯ��\n",me);
		me->delete_temp("gamble_gutou");
	}
	return ::valid_leave(me,dir);
}

void display_gutou (object room, int i)
{
	string str;
	switch (i)
	{
	case 1:
		{
			str = 
				"����������\n"+
				"����������\n"+
				"�����񡡩�\n"+
				"����������\n"+
				"����������\n";

			break;
		} 
	case 2:
		{
			str = 
				"����������\n"+
				"����������\n"+
				"���񡡡�\n"+
				"����������\n"+
				"����������\n";
			break;
		} 
	case 3:
		{
			str =
				"����������\n"+
				"���񡡡���\n"+
				"�����񡡩�\n"+
				"��������\n"+
				"����������\n";
			break;
		} 
	case 4:
		{
			str = 
				"����������\n"+
				"���񡡡�\n"+
				"����������\n"+
				"���񡡡�\n"+
				"����������\n";
			break;
		} 
	case 5:
		{
			str =
				"����������\n"+
				"���񡡡�\n"+
				"�����񡡩�\n"+
				"���񡡡�\n"+
				"����������\n";
			break;
		} 
	case 6:
		{
			str = 
				"����������\n"+
				"���񡡡�\n"+
				"���񡡡�\n"+
				"���񡡡�\n"+
				"����������\n";
			break;
		} 
	}
	tell_room (room,str);
}

void gamble_prepare ()
{
	object room = this_object();
	tell_room (room,"ׯ���������¿��̣�Ԥ��ͷ�ʣ�\n");
	tell_room (room,"ׯ������ö������������һ����\n");
	big[0] = rdm0();
	big[1] = rdm0();										//firefox 2012-4-1

	_total = 0;

	// keep two numbers different for a probability == 1/36
	while (big[0] == big[1]) {
		reset_eval_cost();
		big[1] = rdm0();
	}
	display_gutou (room,big[0]);
	display_gutou (room,big[1]);
	tell_room (room,"ׯ���е���ͷ������"+chinese_number(big[0])+
		chinese_number(big[1])+"��\n");
	tell_room (room,"����ׯ��������˳�ֽ������������ջأ����ڿ���ѺǮ��\n");
	room_status = 1;
	call_out ("gamble_start",24);
}

void gamble_start ()
{
	object room = this_object();
	tell_room (room,"ׯ������������ͣѺ��\n");
	tell_room (room,"�ֲ���������ͷ��������"+chinese_number(big[0])+
		chinese_number(big[1])+"��\n");
	tell_room (room,"Ȼ����ö�����ӽ��������ѣ�һ�ֳ�һ��ҡ��������\n");
	room_status = 2;
	call_out ("gamble_perform",6,0);
	call_out ("gamble_perform",12,1);
	call_out ("gamble_finish",18);
}

void gamble_perform (int i)
{
	object room = this_object();

	tell_room (room,"���ѵ����������ϣ��������˳�����\n");
	res[i] = rdmx(i);											//firefox 2012-4-1	 
	display_gutou (room,res[i]);
}

void player_wins (object who, int total)
{
	object money = new ("/obj/money/"+who->query_temp("gamble_gutou/money"));
	int amount = who->query_temp("gamble_gutou/amount");
	total = total * amount;
	money->set_amount(total);
	message_vision (sprintf("$NӮ��%s%s%s��\n",
		chinese_number(total),
		money->query("base_unit"),
		money->query("name")),
		who);
	
	_account[getuid(who)] += money->value() / 100;				//firefox 2012-4-1
	
	money->move(who);
}

void player_loses (object who, int total)
{
	object money = new ("/obj/money/"+who->query_temp("gamble_gutou/money"));
	total = who->query_temp("gamble_gutou/amount");
	message_vision (sprintf("ׯ����$NѺ�������е�%s%s%s���ߡ�\n",
		chinese_number(total),
		money->query("base_unit"),
		money->query("name")),
		who);
	destruct (money);
}

void gamble_finish ()
{
	string win;
	int total, i;
	object room = this_object();
	object *list = all_inventory(room);
	if (res[0]==big[0] && res[1]==big[1])
	{
		total = 36;
		win = "tc";
	}
	else if (res[0]==res[1] && (res[0]/2*2 == res[0]))
	{
		total = 12;
		win = "sd";
	}
	else 
	{
		int r = res[0]+res[1];
		if (r==7)
		{
			total = 6;
			win = "qx";
		}
		else if (r==3 || r==5 || r==9 || r==11) 
		{
			total = 3;
			win = "sx";
		}
		else
		{
			total = 0;
			win = "none of them";
		}
	}
	if (total == 0)
		tell_room (room,"ׯ���е���"+chinese_number(res[0])+
		chinese_number(res[1])+"�������̣�\n");
	else
		tell_room (room,"ׯ���е���"+chinese_number(res[0])+
		chinese_number(res[1])+"����"+gutous[win]+"��\n");
	i = sizeof(list);
	while (i--)
	{
		if (!userp(list[i]))
			continue;
		if (list[i]->query_temp("gamble_gutou/kind") == win)
			player_wins(list[i],total);
		else if (list[i]->query_temp("gamble_gutou/kind"))
			player_loses(list[i],total);
		list[i]->delete_temp("gamble_gutou");
	}
	tell_room (room,"\n");
	if(sizeof(filter_array(all_inventory(this_object()), (:userp:))))
		call_out ("gamble_prepare",5);
	else
		room_status=0;
}


int do_bian(string arg)
{
	tell_object(this_player(), "�벻Ҫ�����귿�������ȥ��\n");
	return 1;
}

int do_get(string arg)
{
	object ob;
	object who=this_player();
	if (arg) ob=present(arg, environment(who));
	if (ob && userp(ob))
	{
		tell_object(this_player(), "���귿���ܱ��˵����¡�\n");
		return 1;
	}
	return 0;
}

int do_state(string arg)
{
	if(arg == "clear") {
		_total = 0;
		_account = ([]);
	} else {
		int s = 0;
		printf("��ͽ�ɼ�����\n");
		foreach(string k, int v in _account) {
			printf("%-16s    %d\n", k, v / 100);
			s += v / 100;
		}
		printf("����:%d ��ǰ��ע:%d\n", s, _total / 100);
	}
	return 1;
}