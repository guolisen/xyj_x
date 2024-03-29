
#define ADMX_D                  "/adm/daemons/admxd"
#define BOX                     "stock/bank"            //玩家仓库数据

#define AUCTION_TIME            (7*24*3600)             //时限
#define AUCTION_TAX             10                      //交易税(%)
#define AUCTION_MIN_PRICE       1                       //最低价(黄金)
#define AUCTION_MAX_PRICE       9999                    //最高价(黄金)
								
inherit ROOM;
inherit F_SAVE;

#include <ansi.h> 
#include "stock.h"

int sell(object ob, object who, int price);
//string filter_color(string s);
int do_list(string arg);
int do_goumai(string arg);


mapping _items = ([]);                      //记录拍卖的物件
int _serial = 0;                            //物品序列号

void create ()
{
/*
        set ("short", "示例寄卖行");
        set ("long", @LONG

这是一家示例拍忙行，真实拍忙行可继承自此，重写create。可以在
(paizi)上写清操作方法。描述信息上线以后就很难改了，因为修改的
内容会被restore的老内容覆盖。

LONG);
*/
  set ("short", "寄售拍卖行");
  set ("long", "
"BRED YEL"◎≡≡≡◎"NOR"寄售拍卖行紧靠长安当铺，所以生意非常兴隆"BRED YEL"◎≡≡≡◎"NOR"
"BRED YEL"‖      ‖"NOR"兼之价钱低廉，更是成了各大商家交易的首选"BRED YEL"‖      ‖"NOR"
"BRED YEL"‖  "HIY"寄"NOR""BRED YEL"  ‖"NOR"猪二肠是这的大掌柜，三教九流人等在此进进"BRED YEL"‖  "HIY"童"NOR""BRED YEL"  ‖"NOR"
"BRED  YEL"‖  "HIY"售"NOR""BRED YEL"  ‖"NOR"出出，络绎不绝，不时可以看到几位商人模样"BRED  YEL"‖  "HIY"叟"NOR""BRED YEL"  ‖"NOR" 
"BRED YEL"‖  "HIY"典"NOR""BRED YEL"  ‖"NOR"的人在低头交耳不知在说些什么。北边是长安"BRED YEL"‖  "HIY"无"NOR""BRED YEL"  ‖"NOR"
"BRED YEL"‖  "HIY"当"NOR""BRED YEL"  ‖"NOR"当铺，这里是长安城最大的交易中心，各商家"BRED YEL"‖  "HIY"欺"NOR""BRED YEL"  ‖"NOR"
"BRED YEL"◎≡≡≡◎"NOR"将家珍财宝各种宝贝儿拿到这里进行寄售拍卖"BRED YEL"◎≡≡≡◎"NOR"
"BRED YEL" ⅤⅤⅤⅤ "NOR"拍卖行正上方一块老字号的金匾额外醒目(paizi)。 "BRED YEL" ⅤⅤⅤⅤ "NOR"  

    "GRN"测试期间，如有任何问题请post土地处，利用程序漏洞获利者严惩！\n"NOR);

        set("item_desc", ([
                "paizi": @TEXT
这里是寄售典当铺，目前我们提供的服务有：
--------------------------------------
寄售服务：   paimai  (物品ID)  (要价)              

竞买服务:    goumai  (商店序号)

搜索查看：
list   (查看所有)
list   商品中文名
list   商店英文<id>
list   玩家名字<id>

TEXT
        ]) );

        set("exits", ([
                "north" : __DIR__"baihu-w1",
                "down":__DIR__"jicundian",
        ]));

        //set("objects", ([ __DIR__"npc/tiesuanpan" : 1 ]));

        setup();
}

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
}

void init()
{ 
        add_action("do_sale", ({"sell", "paimai"}) ); 
        add_action("do_goumai", ({"goumai", "mai"}) ); 
        add_action("do_list", "list"); 
        add_action("do_look", "look"); 

        if(wizardp(this_player())) add_action("do_timeout", "timeout"); 
}

int do_sale(string arg) 
{ 
        object ob, who = this_player();
        int price;

        if(!arg || sscanf(arg, "%s %d", arg, price) != 2) 
                return notify_fail("指令格式：sell <物品> <价格>\n");
        if(!(ob = present(arg, who))) 
                return notify_fail("你要拍卖什么？\n"); 
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

        message_vision("$N把" + item["name"] + "放入拍卖行开始拍卖，标号为"HIR + sn + NOR"。\n", who);

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
                object seller = ADMX_D->global_find_player(item["sid"]);
                if (seller) {
                        string text = "你拍卖的『" + item["name"] + "』已经过期，转入个人仓库。\n";
						tell_object(seller, HIG + text + NOR);
                        item["time"] = time();          //标记下架时间
                        add_item(seller, BOX, item);
                        seller->save();
                        ADMX_D->global_destruct_player(seller);
                        mail["to"] = item["sid"];
                        mail["text"] = text;
                        send_mail(mail);
                } else {
                        //买家数据加载失败，或许已经自杀了
                }
                map_delete(_items, sn);
        }
        save();
        return 1;
}

// 正在拍卖的物品列表
int do_list(string arg)
{
        string* timeouts = ({});
        string* attrs = ({"id", "name", "sid", "sname"});
        string msg;
        if(!sizeof(_items))
                return notify_fail(query("short")+"目前没有任何货物在拍卖。\n"); 

        msg = query("short") + NOR"正在拍卖的所有物品如下：\n";
        msg += "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"; 
        msg += "序号    物品名称                  数量  价格  到期    拍卖者\n"; 
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
        msg += "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"; 
        msg += "注：用 <goumai 序号> 来购买物品。\n"; 

        this_player()->start_more(msg); 
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
                object seller = ADMX_D->global_find_player(item["sid"]);        // 调入在线/离线卖家档案
                if (seller) {
                        seller->add("balance", price);
                        seller->save();
                        tell_object(seller, HIG"你拍卖的『" + item["name"] + "』已售出。\n"NOR);
                        ADMX_D->global_destruct_player(seller);
                } else {
                        //买家数据加载失败，或许已经自杀了
                }
                who->add("balance", -price);
                map_delete(_items, arg);
                save();

                message_vision(
                        sprintf("$N从拍卖行买下了%s(%s)，花费%d两黄金。\n",
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

