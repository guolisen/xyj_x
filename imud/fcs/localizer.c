// by firefox 04/16/2011
// iFCS���ػ��ļ�

#include <imud-efun.h>

mapping _db = ([
	"prop_root"		: "imud/fcs",				//���Ը��ڵ�
	"ROE"			: (500*10000/1000),			//���ʣ����ƽ�������뻻1K����
	
	"dealer"		: (["id" : "dealer", "name" : "����Ů��", "title" : "����"]),
	"desk_name"		: "����",
	"desk_desc"		: "\n����һ�ſ��������ӣ����������Ϸ��ź�ľ���е��İ���â�����¼�\n"
					  "�Ѵ��������ӣ����г�ׯ�ص����ա������У�\n\n",
	"stand_name"	: "����",
	"stand_desc"	: "\n�������Ĵ�����װ�εý�̻Ի͡���������һ�������ӣ����м�һ��\n"
					  "���ɵ���̴ľ�����������У�\n\n",
	"corridor_name"	: "��¥",
	"corridor_desc"	: "\n¥���Եø������֣����������������������������������ӣ�Ǯ������\n"
					  "�����������������ӣ������Ƕĵ������ء�\n\n",
	"exits"			: ([
			"down"		: "/d/qujing/chechi/jiuguan",
	]),
]);

//��ȡ����
mixed get(string prop)
{
	return _db[prop];
}

/********************************��ȫ��֤***********************************/

//���ð�ȫ�������������Ϸ��ս��
int set_safety(object room)
{
	room->set("no_fight", 1);
	room->set("no_cast", 1);

	room->set("alternative_die", 1);
}

/********************************������ʾ***********************************/

//��ʽ��ѡ����Ϣ��������ʾ
string format_player(mapping who)
{
	string str = sprintf("  %s %s", who["title"], name_id(who));
	if(who["chip"]) str += "<�ֱ�" + who["chip"] + "����>";
	return str + "\n";
}

//ˢ����ҿ����ĳ�����������Ϸ�ҺͿ�̨
int refresh_look(mapping dealer, mapping g, mixed deskside, mixed stand)
{
	string desc = format_player(dealer);
	
	foreach(mapping who in g["players"]) {
		desc += format_player(who);
	}
	desc += "  ----------------------------------\n";
	foreach(mapping who in g["queue"]) {
		desc += format_player(who);
	}
	desc +="\n";

	deskside->set("short", get("desk_name"));
	deskside->set("long", get("desk_desc") + desc);
	if(stand) {
		stand->set("short", get("stand_name"));
		stand->set("long", get("stand_desc") + desc);
	}
}

//���ߵ���ҿ�������Ϣ
int deskside_look(object room)
{
	write(room->query("short") + " -\n");
	write(room->query("long"));
	return 1;
}

//��ʼ�����ȣ����ú������ĳ����
void setup_corridor(object room)
{
	room->set("short", get("corridor_name"));
	room->set("long", get("corridor_desc"));
	room->set("exits", get("exits"));
	set_safety(room);
}

/********************************����һ�***********************************/

//������
int exchange_chip(object who, int amount)
{
	int n = amount * get("ROE");
	if(who->query("balance") >= n) {
		who->add("balance", -n);
		who->save();
		return 1;
	}
	write("���д��㡣\n");
	return 0;
}

