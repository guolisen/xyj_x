// by firefox 11/21/2009

inherit ITEM;

#include <xyj_x.h>
#include <ansi.h>

void create()
{
	set_name("��������", ({"seller"}));
	set("env/invisibility", 1);

	set("long", "����Ϊ����ṩ������\n");
	set("value", 1);
	set("no_get", 1);
	set("no_give", 1);

	set("has_box", 1);
	
	seteuid(getuid());
	setup();
}

/*****************************�¹ⱦ��*****************************/

void init()
{
	add_action("do_dig", ({"dig", "wa"}));
}

int do_dig(string arg)
{
	string* items = ({
		({ "һ������",	"/d/southern/jinghe/obj/qiuyin" }),
		({ "һֻ����",	__DIR__"yg-box" }),
	});
	string str = CYN"$N����������ϵĸ���......��%sӳ��������\n"NOR;
	int i = query("has_box");

	if(cannot_move(_player)) return notify_fail("����æ�ţ�\n");	
	_player->start_busy(3);

	if(random(5)) {
		message_vision(CYN"$N����������ϵĸ���......\n"NOR, _player);
	} else {
		object ob = new(items[i][1]);
		if(ob->move(_player)) {
			message_vision(CYN"$N�ڵ���" + items[i][0] + "��\n"NOR, _player);
			set("has_box", 0);
		}
	}
	return 1;
}

/*****************************�Ĵ�����*****************************/

string* rooms = ({
	"/d/dntg/hgs/shifang",
	"/d/dntg/hgs/shifang",
});

void debut()
{
	//���ѡ��һ���������趨��ǰ����

	//ѡ��һ���������ֵ�λ��

	//��ָ��λ�ã��ȴ���Ե��

	//��Ե������������Ҫ�������շ����������˵õ���Ʒ����ԭ�ϣ�

	//���������Ǳޣ����

	_this->move(random1(rooms));
}

