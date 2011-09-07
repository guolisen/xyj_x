// by firefox 02/21/2010
// 可保存容器
// todo:也需要重新设计

inherit ITEM;
inherit F_SAVE;
inherit __DIR__"file";

#define SAVE_INTERVAL	130
#define F				base_name(this_object())
#define FUN				"/d/sldh2/daemons/ufun"

//加载数据
int load_data()
{
	if(!clonep()) {
		restore();
		call_out("do_save", SAVE_INTERVAL, this_object());
	}
}
/*
void create()
{
	set_name("紫檀柜", ({ "zitan gui", "gui", "cabinet" }) );
	set_weight(500000);
	set_max_encumbrance(500000);
	set_max_items(20);

	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "个");
		set("long", "这是一个古色古香的紫檀柜，看来可以容纳很多东西。\n");
		set("value", 50);
		set("no_get", 1);
	}
	load_data();
}*/

int is_container() { return 1; }


//转换字符串
private string cvstr(string str)
{
	return replace_string(str, "/", "=");
}

//初始化容器的env和加载容器内数据
void init()
{
	object me = this_object();
	if(!query("env")) {
		object env = environment();
		string str = cvstr(base_name(env));
		if(!userp(env))	{
			mapping list = F->query("copies/" + str);
			if(list) {
				foreach(mapping m in list) {
					object ob = new(m["file"]);
					if(!ob) continue;
					if(m["amount"] > 0) ob->set_amount(m["amount"]);
					ob->move(me);
				}
			}
			set("env", str);
		}
	}
}

string query_save_file()
{
	return DATA_DIR"sldh2/container/" + file_name1(this_object());
}

//刷新子对象的信息
void refresh()
{
	foreach(object ob in children(F)) {
		string env = ob->query("env");
		if(env) set("copies/" + env, ob->items());
	}
}

//获取容纳的物品信息
mapping* items()
{
	mapping* arr = ({});
	foreach(object ob in all_inventory()) {
		if(FUN->can_save(ob))
			arr += ({ ([ "file" : base_name(ob), "amount" : ob->query_amount() ]) });
	}
	return arr;
}

//保存函数
int do_save(object me)
{
	if(me) {
		refresh();
		save();
		call_out("do_save", SAVE_INTERVAL, me);
	}
	return 1;
}

//对象析构，销毁所有子对象
int remove()
{
	F->refresh();
	if(!clonep()) F->save();
	::remove();
	return 0;
}
