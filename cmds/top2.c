#include <ansi.h>
#include <xyj_x.h>

inherit F_CLEAN_UP;

#define SIZE		20
#define INTERVAL	911

#define	ID			0
#define	TITLE		1
#define	OBJ			2
#define	TIME		3
#define	LIST		4

mixed* _tops = ({
	({ "gs",	"ʵ����",				"uforce",	0, 0}),
	({ "pt",	"ʵ����-����",		"uforce",	0, 0}),
	({ "fc",	"ʵ����-����",		"uforce",	0, 0}),
	({ "wzg",	"ʵ����-��ׯ��",		"uforce",	0, 0}),
	({ "moon",	"ʵ����-�¹�",		"uforce",	0, 0}),

	({ "jjf",	"ʵ����-������",		"uforce",	0, 0}),
	({ "lg",	"ʵ����-����",		"uforce",	0, 0}),
	({ "hell",	"ʵ����-�ظ�",		"uforce",	0, 0}),
	
	({ "xs",	"ʵ����-ѩɽ",		"uforce",	0, 0}),
	({ "wdd",	"ʵ����-�޵׶�",		"uforce",	0, 0}),
	({ "hyd",	"ʵ����-���ƶ�",		"uforce",	0, 0}),
	({ "psd",	"ʵ����-��˿��",		"uforce",	0, 0}),
	
	//"skill"		: ({ "���ּ��ܰ�",		"uforce",	0}),
	
	({ "rich",	"������",				"udata",	0, 0}),
	({ "killer","ɱ�ְ�",				"udata",	0, 0}),
	({ "nk",	"NK��",				"udata",	0, 0}),
	({ "mieyao","������",				"udata",	0, 0}),
	({ "quest",	"���հ�",				"udata",	0, 0}),
	({ "age",	"���ǰ�",				"udata",	0, 0}),
	({ "wx",	"��ѧ��",				"udata",	0, 0}),
	({ "dx",	"���а�",				"udata",	0, 0}),
	({ "force",	"������",				"udata",	0, 0}),
	({ "mana",	"������",				"udata",	0, 0}),
	({ "kee",	"��Ѫ��",				"udata",	0, 0}),
	({ "sen",	"�����",				"udata",	0, 0}),
	({ "stl",	"ʨ���빦ѫ��",		"udata",	0, 0}),

	({ "mp",	"�������а�",			"stat",		0, 0}),
	({ "sforce","�ڹ����а�",			"stat",		0, 0}),
	({ "spells","�������а�",			"stat",		0, 0}),
	({ "dodge",	"�Ṧ���а�",			"stat",		0, 0}),
	({ "wq",	"�������а�",			"stat",		0, 0}),
	({ "tf",	"�츳���а�",			"stat",		0, 0}),
	
	/*


	
	"zj"		: ({ "stl",			"ʨ����ս����" }),*/
	
	/*"bang"		: ({ "bang",		"���ս����" }),
	"weapon"	: ({ "bang",		"������" }),
	"pat"		: ({ "pat",			"���ް�" }),
	"pat"		: ({ "pat",			"�����" }),

	"star"		: ({ "special",		"���ǰ�" }),		//��һɫ�ǣ���ͽ�ӣ����»ݣ���һ��å��ս��
	*/
});

mixed* find(string id)
{
	if(!id) id = "gs";
	foreach(mixed* arr in _tops) {
		if(arr[ID] == id) return arr;
	}
	return 0;
}


int main(object me, string arg)
{
	mixed* info = find(arg);
	object_f ob;
	mapping list;

	if(!info) return notify_fail("ָ���İ񵥲����ڡ�\n");
	if(!cd_start(me, "cmd", 5)) return notify_fail("�벻Ҫ����ʹ�ø�ָ�\n");

	ob = X_DIR"cmds/top/" + info[OBJ];

	//ˢ������
	if(info[TIME] + INTERVAL < time()) {
		info[LIST] = ob->query(info[ID], SIZE);
		info[TIME] = time();
	}

	//��ȡ����ʾ����
	list = info[LIST];
	write(info[TITLE] + "��\n" + LINE1);
	write(list["header"]);
	write(NOR + LINE1);
	foreach(string line in list["lines"])
		write(line);
	write(NOR + LINE1);

	return 1;
}

int help(object me)
{
	write("ָ���ʽ : top [����д]\n\n��ѡ��д���£�\n");
	
	foreach(mixed* arr in _tops)
		printf("    %-10s      %s\n", arr[ID], arr[TITLE]);
    return 1;
}

