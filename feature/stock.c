// by firefox 02/21/2010
// �ɱ�������
//todo:Ҫ������ƣ����stock��

inherit ITEM;
inherit F_SAVE;
inherit __DIR__"file";

#define SAVE_INTERVAL	130
#define F				base_name(this_object())
#define FUN				"/d/sldh2/daemons/ufun"

//��������
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
	set_name("��̴��", ({ "zitan gui", "gui", "cabinet" }) );
	set_weight(500000);
	set_max_encumbrance(500000);
	set_max_items(20);

	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ����ɫ�������̴�񣬿����������ɺܶණ����\n");
		set("value", 50);
		set("no_get", 1);
	}
	load_data();
}*/

int is_container() { return 1; }


string inventory_look(object obj, int flag)
{
	string str;

	str = obj->short();
	if( obj->query("equipped") )
		str = HIC "  ��" NOR + str;
	else if( !flag )
		str = "    " + str;
	else
		return 0;

	return str;
}

int look_item(object me, object obj)
{
	mixed *inv;

//	write(obj->long());
	me->start_more(obj->long());
	
	//added by weiqi for self-made fabao
	if( obj->query("series_no") && obj->query("fabao") ) 
	    write(obj->show_status());
	
	inv = all_inventory(obj);
	if( sizeof(inv) ) {
		inv = map_array(inv, "inventory_look", this_object() );
		message("vision", sprintf("�����У�\n  %s\n",
			implode(inv, "\n  ") ), me);
	}
	return 1;
}


//ת���ַ���
private string cvstr(string str)
{
	return replace_string(str, "/", "=");
}

//��ʼ��������env�ͼ�������������
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

//ˢ���Ӷ������Ϣ
void refresh()
{
	foreach(object ob in children(F)) {
		string env = ob->query("env");
		if(env) set("copies/" + env, ob->items());
	}
}

//��ȡ���ɵ���Ʒ��Ϣ
mapping* items()
{
	mapping* arr = ({});
	foreach(object ob in all_inventory()) {
		if(FUN->can_save(ob))
			arr += ({ ([ "file" : base_name(ob), "amount" : ob->query_amount() ]) });
	}
	return arr;
}

//���溯��
int do_save(object me)
{
	if(me) {
		refresh();
		save();
		call_out("do_save", SAVE_INTERVAL, me);
	}
	return 1;
}

//�������������������Ӷ���
int remove()
{
	F->refresh();
	if(!clonep()) F->save();
	::remove();
	return 0;
}
