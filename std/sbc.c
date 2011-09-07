// by firefox 04/02/2010
// ������

#define ADMX_D                  "/adm/daemons/admxd"

#define AUCTION_TIME            (31*24*3600)            //ʱ��
#define AUCTION_TAX             1                       //����˰(%)
#define AUCTION_MIN_PRICE       1                       //��ͼ�(�ƽ�)
#define AUCTION_MAX_PRICE       9999                    //��߼�(�ƽ�)

inherit ROOM;
inherit F_SAVE;

#include <ansi.h> 
#include "stock.h"

int sell(object ob, object who, int price);
int do_list(string arg);
int do_goumai(string arg);


mapping _items = ([]);                      //��¼���������
int _serial = 0;                            //��Ʒ���к�

/*
void create1()
{	
	set("short", "ʾ��������");
	set("long", "

����һ��ʾ����æ�У���ʵ��æ�пɼ̳��Դˣ���дcreate��������
(gaoshi)��д�����������������Ϣ�����Ժ�ͺ��Ѹ��ˣ���Ϊ�޸ĵ�
���ݻᱻrestore�������ݸ��ǡ�

");

	setup();
}*/

//�õ��̴���ļ�·��������
string query_save_file()
{
	return make_save_name("salesroom", base_name(this_object())); 
} 

void setup()
{
	::setup(); 
	seteuid(getuid());
	restore();
	set("no_fight", 1);
	set("no_magic", 1);
}

void init()
{
	object who = this_player();

	if(userp(who)) {
		add_action("do_sale", ({"sell", "jishou"}) ); 
		add_action("do_goumai", ({"goumai", "mai"}) ); 
		add_action("do_list", "list"); 
		add_action("do_look", "look"); 
	}
	if(wizardp(who))
		add_action("do_timeout", "timeout");
}

int do_sale(string arg) 
{ 
	object ob, who = this_player();
	int price;

	if(!arg || sscanf(arg, "%s %d", arg, price) != 2) 
		return notify_fail("ָ���ʽ��sell <��Ʒ> <�۸�>\n");
	if(!(ob = present(arg, who))) 
		return notify_fail("��Ҫ����ʲô��\n"); 
	if(who->is_busy())
		return notify_fail(BUSY_MESSAGE);
	if(no_stock(ob))
		return notify_fail("�ⶫ�����ǲ��ա�\n");
	if(price < AUCTION_MIN_PRICE)
		return notify_fail("Ҫ�۹��͡�\n");
	if(price > AUCTION_MAX_PRICE)
		return notify_fail("Ҫ�۹��ߡ�\n");     
	price *= 10000; //����
	if(who->query("balance") < price*AUCTION_TAX/100) 
		return notify_fail("��Ĵ���֧�������ѡ�\n");
	return sell(who, ob, price); 
}

int sell(object who, object ob, int price) 
{ 
	int sn = ++_serial;
	mapping item = save_item(ob);
	{
		item["sid"] = getuid(who);
		item["sname"] = who->query("name");
		item["price"] = price;
		item["time"] = time();
		item["sn"] = sn;
	}
	_items[sn + ""] = item;

	message_vision("$N��" + item["name"] + "�����˴��ۣ����Ϊ"HIR + sn + NOR"��\n", who);

	who->add("balance", -price*AUCTION_TAX/100);    // ���������ѣ��Ӵ��۳�
	who->save();
	who->start_busy(2);

	destruct2(ob);
	save(); 
	return 1; 
}

//ʱ��
private string time_str(int t)
{
	int d = t / 3600 / 24;
	int h = t / 3600;
	int m = t / 60;
	if(d) return d + "��";
	if(h) return h + "Сʱ";
	if(m) return m + "����";
	return "����";
}

//�����ʼ�
int send_mail(mapping mail)
{
	object mbx = new(MAILBOX_OB);
	mbx->set_owner("vendor_sale");
	mbx->send_mail(mail["to"], mail, 1);
	destruct(mbx);
	return 1;
}

//�¼�
int give_back(string* timeouts)
{
	mapping mail = ([
		"from"          : query("short"),
		"title"         : "��Ʒ����",
		"time"          : time(),
		"status"        : "N",
	]);
	foreach(string sn in timeouts) {
		mapping item = _items[sn];
		
		string text = "����۵ġ�" + item["name"] + "���Ѿ����ڣ��������ˡ�\n";
		mail["to"] = item["sid"];
		mail["text"] = text;
		send_mail(mail);

		map_delete(_items, sn);
	}
	save();
	return 1;
}

// ������������Ʒ�б�
int do_list(string arg)
{
	string* timeouts = ({});
	string* attrs = ({"id", "name", "sid", "sname"});
	string msg;
	if(!sizeof(_items))
		return notify_fail(query("short")+"Ŀǰû���κλ�����������\n"); 

	msg = query("short") + NOR"������Ʒ���£�\n";
	msg += "������������������������������������������������������������������������\n"; 
	msg += "���    ��Ʒ����                  ����  �۸�  ����    ������\n"; 
	msg += "------------------------------------------------------------------------\n"; 

	foreach(string sn, mapping item in _items) {
		int time_left = AUCTION_TIME - (time() - item["time"]);
		if(time_left < 0) {
			timeouts += ({ sn });
		} 
		else if(item_filter(item, arg, attrs)) {
			msg += sprintf("%-6s  %-26s%4d  %4d  %-6s  %s\n",
				sn, 
				filter_color(item["name"]) + "(" + item["id"] + ")",
				item["amount"] = item["amount"] ? item["amount"] : 1,
				item["price"]/10000,
				time_str(time_left),
				item["sname"] + "(" + item["sid"]+")"
				);
		}
		reset_eval_cost();
	}
	msg += "������������������������������������������������������������������������\n"; 
	msg += "ע���� <mai ���> ��������Ʒ��\n"; 

	this_player()->start_more(msg); 
	give_back(timeouts);
	return 1;
}

int do_goumai(string arg)
{
	object who = this_player();
	object ob;
	mapping item;

	if(!arg) return notify_fail("ָ���ʽ��goumai <��Ʒ���>\n");   
	if( who->is_busy() ) return notify_fail(BUSY_MESSAGE);

	item = _items[arg];

	if(!item) return notify_fail("��Ʒ�����ڡ�\n");
	if(item["price"] > who->query("balance"))
		return notify_fail("���Ĵ������޷��������Ʒ��\n");

	ob = load_item(item);

	if(ob->move(who)) {
		int price = item["price"];
		object seller = ADMX_D->global_find_player(item["sid"]);        // ��������/�������ҵ���
		if (seller) {
			seller->add("balance", price);
			seller->save();
			tell_object(seller, HIG"������ġ�" + item["name"] + "�����۳���\n"NOR);
			ADMX_D->global_destruct_player(seller);
		} else {
			//������ݼ���ʧ�ܣ������Ѿ���ɱ��
		}
		who->add("balance", -price);
		map_delete(_items, arg);
		save();

		message_vision(
			sprintf("$N�Ӽ�����������%s(%s)������%d���ƽ�\n",
				item["name"],
				item["id"],
				price/10000
			), 
			who
			);
		who->start_busy(2); 
		return 1;
	} else {
		destruct2(ob);
		return notify_fail("�����ϷŲ��¸��ණ���ˡ�\n");
	}
	return 1;
}

int do_look(string arg) 
{ 
	int num;
	if(!arg || sscanf(arg, "%d", num) != 1 || !_items[arg])
		return 0;

	write(_items[arg]["long"] + "\n");
	return 1; 
}

int do_timeout(string arg)
{
	int num;
	if(!arg || sscanf(arg, "%d", num) != 1 || !_items[arg])
		return notify_fail("���ĸ���Ʒ��ʱ��\n");

	_items[arg]["time"] -= AUCTION_TIME;
	printf("%s�Ѿ���ʱ��׼���¼ܡ�\n", _items[arg]["name"]);
	return 1;
}

