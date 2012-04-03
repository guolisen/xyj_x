// by firefox 04/02/2010
// 寄卖行

#define AUCTION_TIME            (10*24*3600)            //时限
#define AUCTION_TAX             20                      //交易税(%)
#define AUCTION_MIN_PRICE       20                      //最低价(黄金)
#define AUCTION_MAX_PRICE       9999                    //最高价(黄金)
#define AUCTION_MAX_LIST        20                      //列表项上限

inherit ROOM;
inherit F_SAVE;

#include <ansi.h> 
#include "stock.h"

int sell(object ob, object who, int price);
int do_list(string arg);
int do_goumai(string arg);


mapping _items = ([]);                      //记录拍卖的物件
int _serial = 0;                            //物品序列号
mapping _sellers = ([]);                    //拍卖者

/*
void create1()
{	
	set("short", "示例寄卖行");
	set("long", "

这是一家示例拍忙行，真实拍忙行可继承自此，重写create。可以在
(gaoshi)上写清操作方法。描述信息上线以后就很难改了，因为修改的
内容会被restore的老内容覆盖。

");

	setup();
}*/

//该当铺存放文件路径和名称
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
	if(!_sellers) _sellers = ([]);
}

void init()
{
	object who = this_player();

	if(!userp(who)) return;

	add_action("do_sale", ({"sell", "jishou"}) ); 
	add_action("do_goumai", ({"goumai", "mai"}) ); 
	add_action("do_list", "list"); 
	add_action("do_look", "look"); 
	
	if(wizardp(who)) {
		add_action("do_timeout", "timeout");
		add_action("do_total", "total");
	}

	if(_sellers[getuid(who)] > 0) call_out("give_money", 1, who);
}

void give_money(object who)
{
	string id = getuid(who);
	who->add("balance", _sellers[id]);	
	who->save();
	tell_object(who, HIG"你寄卖所得" + (_sellers[id]/10000) + "两黄金已汇入钱庄帐户。\n"NOR);	
	map_delete(_sellers, id);
	
}

int do_sale(string arg) 
{ 
	object ob, who = this_player();
	string id;
	int price = 0;

	if(arg) {
		int i = rfind(arg, ' ');
		id = arg[0..i-1];
		price = to_int(arg[i+1..]);
	}
	if(!price)
		return notify_fail("指令格式：sell <物品> <价格>\n");
	if(!(ob = present(id, who))) 
		return notify_fail("你要寄卖什么？\n"); 
	if(who->is_busy())
		return notify_fail(BUSY_MESSAGE);
	if(no_stock(ob))
		return notify_fail("这东西我们不收。\n");
	if(price < AUCTION_MIN_PRICE)
		return notify_fail("要价过低。\n");
	if(price > AUCTION_MAX_PRICE)
		return notify_fail("要价过高。\n");
	price *= 10000; //换算
	if(who->query("balance") < price*AUCTION_TAX/100) 
		return notify_fail("你的存款不足支付手续费。\n");
	return sell(who, ob, price); 
}

int sell(object who, object ob, int price) 
{ 
	int sn = (_serial + 1) % 10000;
	mapping item = save_item(ob);
	{
		item["sid"] = getuid(who);
		item["sname"] = who->query("name");
		item["price"] = price;
		item["time"] = time();
		item["sn"] = sn;
	}
	_serial = sn;
	_items[sn + ""] = item;

	message_vision("$N把" + item["name"] + "托商人代售，标号为"HIR + sn + NOR"。\n", who);

	who->add("balance", -price*AUCTION_TAX/100);    // 拍卖手续费，从存款扣除
	who->save();
	who->start_busy(2);

	destruct2(ob);
	save(); 
	return 1; 
}

//时间
private string time_str(int t)
{
	int d = t / 3600 / 24;
	int h = t / 3600;
	int m = t / 60;
	if(d) return d + "天";
	if(h) return h + "小时";
	if(m) return m + "分钟";
	return "到期";
}

//发送邮件
int send_mail(mapping mail)
{
	object mbx = new(MAILBOX_OB);
	mbx->set_owner("vendor_sale");
	mbx->send_mail(mail["to"], mail, 1);
	destruct(mbx);
	return 1;
}

//下架
int give_back(string* timeouts)
{
	mapping mail = ([
		"from"          : query("short"),
		"title"         : "拍品过期",
		"time"          : time(),
		"status"        : "N",
	]);
	foreach(string sn in timeouts) {
		mapping item = _items[sn];
		
		string text = "你寄售的『" + item["name"] + "』已经过期，被丢掉了。\n";
		mail["to"] = item["sid"];
		mail["text"] = text;
		send_mail(mail);

		map_delete(_items, sn);
		reset_eval_cost();
	}
	save();
	return 1;
}

// 正在拍卖的物品列表
int do_list(string arg)
{
	string* timeouts = ({});
	string* attrs = ({"id", "name", "sid", "sname"});
	int n = 0;

	if(!sizeof(_items))
		return notify_fail(query("short")+"目前没有任何货物在拍卖。\n"); 

	write(query("short") + NOR"在售物品如下(至多显示20个)：\n");
	write("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	write("序号    物品名称                  数量  价格  到期    拍卖者\n");
	write("------------------------------------------------------------------------\n");

	foreach(string sn, mapping item in _items) {
		int time_left = AUCTION_TIME - (time() - item["time"]);
		if(time_left < 0) {
			timeouts += ({ sn });
		} 
		else if(item_filter(item, arg, attrs)) {
			printf("%-6s  %-26s%4d  %4d  %-6s  %s\n",
				sn, 
				filter_color(item["name"]) + "(" + item["id"] + ")",
				item["amount"] = item["amount"] ? item["amount"] : 1,
				item["price"]/10000,
				time_str(time_left),
				item["sname"] + "(" + item["sid"]+")"
				);
			if(++n >= 20) break;
		}
		reset_eval_cost();
	}
	write("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	write("注：用 <mai 序号> 来购买物品。\n");

	give_back(timeouts);
	return 1;
}

int do_goumai(string arg)
{
	object who = this_player();
	object ob;
	mapping item;

	if(!arg) return notify_fail("指令格式：goumai <物品标号>\n");   
	if( who->is_busy() ) return notify_fail(BUSY_MESSAGE);

	item = _items[arg];

	if(!item) return notify_fail("物品不存在。\n");
	if(item["price"] > who->query("balance"))
		return notify_fail("您的存款不够，无法购买此物品。\n");

	ob = load_item(item);

	if(ob->move(who)) {
		int price = item["price"];
		object seller = find_player(item["sid"]);        // 调入在线/离线卖家档案
		if(seller) {
			seller->add("balance", price);
			seller->save();
			tell_object(seller, HIG"你寄卖的『" + item["name"] + "』已售出。\n"NOR);
		} else {
			_sellers[item["sid"]] += price;
		}
		who->add("balance", -price);
		map_delete(_items, arg);
		save();

		message_vision(
			sprintf("$N从寄卖行买下了%s(%s)，花费%d两黄金。\n",
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
		return notify_fail("你身上放不下更多东西了。\n");
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
		return notify_fail("让哪个商品超时？\n");

	_items[arg]["time"] -= AUCTION_TIME;
	printf("%s已经超时，准备下架。\n", _items[arg]["name"]);
	return 1;
}

int do_total(string arg)
{
	printf("商品总数：%d。\n", sizeof(_items));
	return 1;
}
