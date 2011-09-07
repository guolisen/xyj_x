
#define BUSY_MESSAGE				"����æ�š�\n"

//���ٶ���
int destruct2(object ob)
{
	ob->move(VOID_OB);
	destruct(ob);
	return 1;
}

//����Ƿ�ɴ���
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

//����Ʒ����Ϊ����
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

//�����ݼ���һ����Ʒ
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

//����������������һ����Ʒ
void add_item(object ob, string attr, mapping item)
{
	mixed* items = ob->query(attr + "/items");
	if(arrayp(items)) items += ({ item });
	else items = ({ item });	
	ob->set(attr + "/items", items);
}

//��Ʒ����������Ҫ��Ʒ��������(attrs)����һ��ƥ�����(arg)
int item_filter(mapping item, string arg, string* attrs)
{
	if(!arg || !attrs) return 1;
	foreach(string attr in attrs) {
		if(strsrch(item[attr], arg) >= 0) return 1;
	}
	return 0;
}

//��Ʒ�б�
string search_items(mapping data, string arg)
{ 
	mixed* items = data["items"];
	string msg = query("long_msg") + "�����ɴ��" + data["size"] + "����Ʒ��\n";
	string* attrs = ({"id", "name"});
	
	if(!sizeof(items)) return msg;
	
	msg += arg ? ("�롺" +arg + "����ص��У�\n") : "�����У�\n"; 
	for(int i = sizeof(items) - 1; i >= 0; --i) {
		if(item_filter(items[i], arg, attrs)) {			
			msg += sprintf("    %s\n", items[i]["short"]);
		}
	}
	msg += "\n"; 
	return msg;
}

//��Ʒ��������
int putin(mapping data, string arg) 
{ 
	object ob, who = this_player();
	object me = this_object();
	string name = query("name");

	if(!arg || !(ob = present(arg, who)))
		return notify_fail("��Ҫ��ʲô��Ʒ��\n");
	if(who->is_busy())
		return notify_fail(BUSY_MESSAGE);
	if(no_stock(ob) || ob == me)
		return notify_fail(name + "���ܷ��ⶫ����\n");
	if(sizeof(data["items"]) >= data["size"])
		return notify_fail(name + "�Ѿ�װ���ˡ�\n");
	else {
		mapping item = save_item(ob);

		data["items"] += ({ item });

		message_vision("$N��" + item["name"] + "����$n��\n", who, me);

		me->save();
		who->save();
		who->start_busy(2);

		destruct2(ob);
	}
	return 1; 
}

//��Ʒȡ������
int fetch(mapping data, string arg)
{
	mixed* items = data["items"];
	object who = this_player();
	object me = this_object();
	
	if(!arg) return notify_fail("��Ҫȡʲô��Ʒ?\n");
	if( who->is_busy() ) return notify_fail(BUSY_MESSAGE);

	for(int i = sizeof(items) - 1; i >= 0; --i) {
		if(strsrch(items[i]["name"], arg) >= 0
			|| strsrch(items[i]["id"], arg) >= 0)
		{
			object ob = load_item(items[i]);
			if(ob->move(who)) {
				string str = "һ" + ob->query("unit") + ob->query("name");
				items[i] = 0;
				data["items"] -= ({0});
				message_vision("$N��$n���ó�" + str + "��\n", who, me);
				
				me->save();
				who->save();
				who->start_busy(2); 
				return 1;
			}
			destruct2(ob);
			return notify_fail("�����ϷŲ��¸��ණ���ˡ�\n");
		}
	}
	return notify_fail("û�������Ʒ��\n");;
}

//����/dataĿ¼�µ��ļ���
string make_save_name(string dir, string name)
{ 
	if(name[0..0] == "/") name = name[1..];
	name = replace_string(name,"/","_"); 
	return DATA_DIR + dir + "/" + name; 
}

//������Ʒ���ݵ�ȱʡ����
mapping _data = (["items" : ({})]);

//��ȡ�洢���ݣ���д�ú�������ʹ���ݱ���������λ��
mapping items_data()
{
	mapping data = this_object()->query_data();
	return data ? data : _data;
}

//��Ʒ��������
int do_putin(string arg) 
{
	return putin(items_data(), arg);
}

//��Ʒȡ������
int do_fetch(string arg)
{
	return fetch(items_data(), arg);
}

//����
int do_search(string arg)
{
	write(search_items(items_data(), arg));
	return 1;
}
