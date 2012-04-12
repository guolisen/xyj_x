// by firefox 02/21/2010
// ����ģ��

#include <xyj_x.h>
#include <ansi.h>

inherit F_DATA_OF;
inherit F_FOT;


#define GANG_JOIN		"g_join"

#define LEADER			0
#define VLEADER			1
#define TEAM_LEADER		2
#define MUMBER			3

static string* _ranks = ({"����", "������", "����", "����"});
static mapping _props;			//��������

//������Ϣ����
void create()
{
	_props = ([
		"id"		: "ftb",
		"name"		: "��ͷ��",
		"color"		: HIW,
		"location"	: "����������",
		"slogan"	: "ɽ������ǰ;��ְҵ��",
		
		"npc"		: ([
		]),

		"street"	: ([
			"short"		: "�¶�",
			"long"		: "\nɽ����ľ��ï�Դ䣬�����Ǽž������ɽ�ȣ�����һ��С·������\nͨ��һ��ɽկ��\n\n",
		]),

		"leave"		: ([
			"dst"	: "/d/westway/yinma",
			"verb"	: "down",
			"msg1"	: "$N����һ�е������������¡�",
			"msg2"	: "����һ���ҽУ�$N��ɽ���Ϲ�����������ͬһ̲����˦�ڵ��档",
		]),

		"arrive"		: ([
			"dst"	: "/d/westway/yinma",
			"msg1"	: "$N������������ɽ������ȥ��",
			"msg2"	: "$N������������������ͷ��������ɽ��м��",
		]),
	]);
}


/********************************��������***********************************/

int setup()
{
	set_data_prop(GANG_PROP);
}

//��ȡ����
mixed query(string prop)
{
	return _props[prop];
}

//��������
void set(string prop, mixed value)
{
	_props[prop] = value;
}

//��������
string name()
{
	return _props["color"] + _props["name"] + NOR;
}

//�Ƿ��Ǳ����Ա
int is_mumber(object who)
{
	return data_of(who, "id") == _props["id"];
}

//�ǲ��Ǳ���߹�
int is_executive(object who)
{
	mapping m = data_of(who);
	return m && m["id"] == _props["id"] && m["rank"] <= VLEADER;
}

//��ȡ���г�Ա
object* mumbers()
{
	object* arr = ({});
	foreach(object user in children("/obj/user")) {
		if(is_mumber(user))	arr += ({ user });
	}
	return arr;
}

//��ȡ���᷿��
object_f room(string name)
{
	return GANG_DIR + _props["id"] + "/" + name;
}


//����������Ϣ
int msg(string msg)
{
	foreach(object who in mumbers()) {
		tell_object(who, msg);
	}
	return 1;
}


//����ͷ��
varargs int set_title(object who, string title)
{
	mapping m = data_of(who);
	m["title"] = title ? title : _ranks[m["rank"]];
	who->set("title", m["color"] + m["name"] + " " + m["title"] + NOR);
	return 1;
}

/********************************xxxxӦ����***********************************/

//���ճ�Ա
int recruit(object who, int rank)
{
	mapping m = ([
		"id"	: _props["id"],
		"name"	: _props["name"],
		"color"	: _props["color"],
		"rank"	: rank,
	]);
	who->set(GANG_PROP, m);
	set_title(who);
	return 1;
}

//�Ƴ���Ա
int expel(object who)
{
	mapping m = data_of(who);
	if(m && m["rank"] != LEADER) {
		msg(HIY + name_id(who) + "�뿪�˰�ᡣ\n"NOR);
		who->set("title", m["name"] + "��ͽ");
		who->delete(GANG_PROP);
		return 1;
	}
	return 0;
}

//�������פ��
int enter(object who)
{
	mapping m = query("arrive");
	string room = base_name(environment(who));

	if(room == m["dst"]) {
		message_vision(HIC + m["msg1"] + "\n\n"NOR, who);
		who->move(room("street"));
		if(!who->is_busy()) who->start_busy(3);
		message_vision(HIC"\n" + m["msg2"] + "\n"NOR, who);
		return 1;
	}
	return 0;
}



//�����ڽ���
int talk(object who, string msg)
{
	if(!msg) msg = "...";
	msg = HIY"�����ɡ�" + name_id(who) + "��" + msg + NOR"\n";
	msg(msg);

	return 1;
}

//�ı�ĳ�˵ȼ�
int chg_rank(object me, object who, int level)
{
	mapping g1 = GANG->data(me);
	mapping g2 = GANG->data(who);

	if(g1 && g1["rank"] <= VLEADER
		&& g2 && g1["id"] == g2["id"]
		&& g2["rank"] > g1["rank"])
	{
		g2["rank"] += level;
		if(g2["rank"] > MUMBER) g2["rank"] = MUMBER;
		set_title(who);
		if(g2["rank"] == LEADER) {	//������λ
			g1["rank"] += 1;
			set_title(me);
			return 2;
		}
		return 1;
	}
	return 0;
}



/********************************������Ӧ����***********************************/

//�г����ɳɼ�
string* list(object* users)
{
	string* lines = ({});
	
	lines += ({ LINE1 });
	lines += ({ "   ����   ���                ְλ          �ȼ� ����  ս��  \n" });
	lines += ({ LINE1 });
	for(int i = 0; i < sizeof(users); ++i) {
		string family = FAMILY->short(users[i]);
		mapping g = GANG->data(users[i]);
		lines += ({
			sprintf("%-3d%-7s%-20s%-14s%-5d%-6d%-6d\n",
				i + 1,
				family ? family : "����",
				name_id(users[i]),
				g["title"],
				g["rank"],
				g["score"],
				g["ba"],
			)
		});
	}
	lines += ({ LINE1 });
	return lines;
}

//���ɳ�Ա�б�
int who()
{
	string* arr = list(mumbers());
	foreach(string line in arr) {
		write(line);
	}
	return 1;
}

//�Ƴ����ɳ�Ա
int quit(object me)
{
	if(!expel(this_player())) return notify_fail("�㲻���˳����ɡ�\n");;
	return 1;
}
	
//������������
int join(object me)
{	
	me->set_temp(GANG_JOIN, query("id"));
	write("���������" + query("name") + "��\n");
	msg(HIY + name_id(me) + "������\n"NOR);
	return 1;
}

//��������Ҽ�������
int accept(object me, object who)
{		
	mapping g = GANG->data(me);

	if(g["rank"] > VLEADER) return notify_fail("���������ϲ���Ȩ���롣\n");
	if(!who) return notify_fail("��˭��\n");

	if(GANG->id(who)) return notify_fail("�Է��Ѿ������ᡣ\n");
	if(who->query_temp(GANG_JOIN) != g["id"]) return notify_fail("�Է�������\n");
	
	recruit(who, MUMBER);	
	msg(HIY + name_id(me) + "ͬ��" + name_id(who) + "���뱾�\n"NOR);
	who->delete_temp(GANG_JOIN);	
	return 1;
}

//��������Ա
int promote(object me, object who)
{
	if(!who) return notify_fail("����˭��\n");
	else {		
		int ret = chg_rank(me, who, -1);
		string str = ret == 1 ? "����" : "��λ��";
		
		if(!ret) return notify_fail("����ʧ�ܡ�\n");
		return msg(HIY + name_id(me) + str + name_id(who) + "��\n"NOR);
	}
	return 1;
}

//��������Ա
int	demote(object me, object who)
{
	if(!who) return notify_fail("��ְ˭��\n");
	else {
		int ret = chg_rank(this_player(), who, 1);
		if(!ret) return notify_fail("��ְʧ�ܡ�\n");
		return msg(HIY + name_id(me) + "��ְ" + name_id(who) + "��\n"NOR);
	}
	return 1;
}

#define TITLE_MSG			HIY"%s����%sΪ%s��\n"NOR

//���ó�Աͷ��
int title(object me, object who, string title)
{
	if(title && sizeof(title) > 10) notify_fail("ͷ�ι�����\n");
	if(!who) notify_fail("����˭��ͷ�Σ�\n");
	else {
		mapping g1 = GANG->data(me);
		mapping g2 = GANG->data(who);
			if(g1 && g2 && (g1["id"] == g2["id"])
				&& (g1["rank"] < g2["rank"] || g1["rank"] == 0))
			{
				set_title(who, title);
				return msg(sprintf(TITLE_MSG, name_id(me), name_id(who), title));
			}
	}
	return notify_fail("�޷�����ͷ�Ρ�\n");
}

//���ð������
int leader(object who)
{
	if(!who) return notify_fail("��˭Ϊ������䣿\n");
	
	recruit(who, LEADER);
	return msg(HIY + name_id(who) + "��Ϊ������䡣\n"NOR);
}

/********************************���ɵ�ͼ����***********************************/

//����npc������
void npc_setup(object npc, string type)
{
	mapping m = _props["npc"][type];
	mapping db;

	npc->set_name(m["name"], m["ids"]);

	recruit(npc, MUMBER);
	set_title(npc, m["title"]);

	db = npc->query_entire_dbase();		//dbû��setǰ����Ϊ��
	foreach(string k, mixed v in m["props"]) {
		db[k] = v;
	}

	db["str"]		= 500;

	db["max_kee"]	= 50 * K;
	db["max_sen"]	= 50 * K;

	db["max_force"]	= 3 * K;
	db["max_mana"]	= 3 * K;

	db[CEXP]		= 2 * K * K;
	db[DEXP]		= 2 * K * K;

	SKI->set_list2(npc, FAMILY->skills_of(or2(m["family"], "������")), 180);

	HP->full(npc);

	npc->setup();

	if(m["cloth"]) npc->carry_object(m["cloth"])->wear();
	if(m["weapon"]) npc->carry_object(m["weapon"])->wield();
}
