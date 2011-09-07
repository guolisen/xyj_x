
#define BUSY_MESSAGE				"你正忙着。\n"

//销毁对象
int destruct2(object ob)
{
	ob->move(VOID_OB);
	destruct(ob);
	return 1;
}

//检查是否可储存
int no_stock(object ob) 
{ 
	string* list = ({"money_id", "no_drop", "no_stock", "no_give"});

	foreach(string str in list) {
		if(ob->query(str)) return 1;
	}
	return ob->is_corpse()
		|| ob->is_character()
		|| ob->query_max_encumbrance();
}

//把物品保存为数据
mapping save_item(object ob)
{
	mapping item = ([
		"name"	: ob->query("name"),
		"id"	: ob->query("id"),
		"short"	: ob->short(),
		"long"	: ob->long(),
		"file"	: base_name(ob),
		"dbase"	: ob->query_entire_dbase(),
		"amount": ob->query_amount(),
	]);
	return item;
}

//从数据加载一个物品
object load_item(mapping item)
{
	object ob = new(item["file"]);
	if(!ob) return 0;
	if(item["dbase"]) {
		foreach(mixed k, mixed v in item["dbase"]) {
			ob->set(k, v);
		}
	}
	if(item["amount"]) ob->set_amount(item["amount"]);
	return ob;
}

//给对象数据里增加一个物品
void add_item(object ob, string attr, mapping item)
{
	mixed* items = ob->query(attr + "/items");
	if(arrayp(items)) items += ({ item });
	else items = ({ item });	
	ob->set(attr + "/items", items);
}

//物品过滤器，需要物品的属性中(attrs)至少一个匹配参数(arg)
int item_filter(mapping item, string arg, string* attrs)
{
	if(!arg || !attrs) return 1;
	foreach(string attr in attrs) {
		if(strsrch(item[attr], arg) >= 0) return 1;
	}
	return 0;
}

//物品列表
string search_items(mapping data, string arg)
{ 
	mixed* items = data["items"];
	string msg = query("long_msg") + "，最多可存放" + data["size"] + "件物品。\n";
	string* attrs = ({"id", "name"});
	
	if(!sizeof(items)) return msg;
	
	msg += arg ? ("与『" +arg + "』相关的有：\n") : "里面有：\n"; 
	for(int i = sizeof(items) - 1; i >= 0; --i) {
		if(item_filter(items[i], arg, attrs)) {			
			msg += sprintf("    %s\n", items[i]["short"]);
		}
	}
	msg += "\n"; 
	return msg;
}

//物品放入容器
int putin(mapping data, string arg) 
{ 
	object ob, who = this_player();
	object me = this_object();
	string name = query("name");

	if(!arg || !(ob = present(arg, who)))
		return notify_fail("你要放什么物品？\n");
	if(who->is_busy())
		return notify_fail(BUSY_MESSAGE);
	if(no_stock(ob) || ob == me)
		return notify_fail(name + "不能放这东西。\n");
	if(sizeof(data["items"]) >= data["size"])
		return notify_fail(name + "已经装满了。\n");
	else {
		mapping item = save_item(ob);

		data["items"] += ({ item });

		message_vision("$N把" + item["name"] + "放入$n。\n", who, me);

		me->save();
		who->save();
		who->start_busy(2);

		destruct2(ob);
	}
	return 1; 
}

//物品取出容器
int fetch(mapping data, string arg)
{
	mixed* items = data["items"];
	object who = this_player();
	object me = this_object();
	
	if(!arg) return notify_fail("你要取什么物品?\n");
	if( who->is_busy() ) return notify_fail(BUSY_MESSAGE);

	for(int i = sizeof(items) - 1; i >= 0; --i) {
		if(strsrch(items[i]["name"], arg) >= 0
			|| strsrch(items[i]["id"], arg) >= 0)
		{
			object ob = load_item(items[i]);
			if(ob->move(who)) {
				string str = "一" + ob->query("unit") + ob->query("name");
				items[i] = 0;
				data["items"] -= ({0});
				message_vision("$N从$n里拿出" + str + "。\n", who, me);
				
				me->save();
				who->save();
				who->start_busy(2); 
				return 1;
			}
			destruct2(ob);
			return notify_fail("你身上放不下更多东西了。\n");
		}
	}
	return notify_fail("没有这个物品。\n");;
}

//生成/data目录下的文件名
string make_save_name(string dir, string name)
{ 
	if(name[0..0] == "/") name = name[1..];
	name = replace_string(name,"/","_"); 
	return DATA_DIR + dir + "/" + name; 
}

//保存物品数据的缺省变量
mapping _data = (["items" : ({})]);

//获取存储数据，重写该函数可以使数据保存于其他位置
mapping items_data()
{
	mapping data = this_object()->query_data();
	return data ? data : _data;
}

//物品放入容器
int do_putin(string arg) 
{
	return putin(items_data(), arg);
}

//物品取出容器
int do_fetch(string arg)
{
	return fetch(items_data(), arg);
}

//搜索
int do_search(string arg)
{
	write(search_items(items_data(), arg));
	return 1;
}
