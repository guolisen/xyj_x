// by firefox 06/21/2010

#include <xyj_x.h>
#include <ansi.h>

#define RACE_PROP		XYJ_X"/race"	//��������
#define BUFF_ID			"zhenshen2"
#define BUFF_NAME		"����"
#define CD				10


//��������ֵļ���
mapping _races = ([
	"cattle"		: 10,
	"centipede"		: 10,
	"corpse"		: 10,
	"dragon"		: 10,
	"mouse"			: 10,
	"phoenix"		: 10,
	"pig"			: 10,
	"scorpion"		: 10,
	"snake"			: 10,
	"spider"		: 10,
	"tortoise"		: 10,
	"weasel"		: 10,
	"wolf"			: 10,
]);

void create()
{
	seteuid(getuid());
}

//��ѯĿ���������Ϣ
varargs mixed query(object who, string prop)
{
	mapping m = DB->query_map(who, RACE_PROP);
	return prop ? m[prop] : m;
}

//��ȡָ��ID���������
object_f find(string id)
{
	return id ? (__DIR__ + "race/" + id) : 0;
}

//��ȡĿ����������
object_f race_of(object who)
{
	string id = query(who, "id");
	return find(id);
}

//��������
varargs int set(object who, string id, string name, int num)
{
	mapping m = query(who);
	m["id"] = id;
	m["name"] = name;
	m["num"] = or2(num, sizeof(REI_D->query(who)));
}

//����������һ��������֣��������ֶ���
object_f set_random(object who)
{
	string id = roulette(_races);
	object_f race = find(id);

	set(who, id, race->random_name());
	return race;
}

//��ȡĿ��������Ϣ
void info(object who)
{
	mapping m = query(who);
	string name = or2(m["name"], "����");
	printf("����%s ת��������%d��\n", name, m["num"]);	
}

//�ָ�����
int zhenshen(object who)
{
	object_f race = race_of(who);
	mapping req = ([
		"cd"		: ([ BUFF_ID	: 1 ]),
		"ex_temp"	: ([ "no_wield" : 1, "powerup" : 1, "d_mana" : 1]),
		"ex_class"	: ([ "������" : 1 ]),
	]);

	if(!race) return notify_fail("��û������״̬��\n");
	if(!BTL->require(who, BUFF_NAME, req)) return 1;
	else {
		mapping buff = race->make_buff(who);

		buff["id"]	= BUFF_ID;
		buff["name"]= BUFF_NAME;
	
		MSG->vison(HIC"$N�͵�һ������Ϊһ%s��", who, 0, buff["_unit"] + buff["_name"]);

		BUFF->add(who, buff);
		BUFF->start_cd2(who, buff, CD);
	}

	return 1;
}

//��ʱ����������Ч
int on_timer(mapping buff)
{
		/*object enemy = query_temp("last_damage_from");
	object weapon;
	if(enemy && weapon = enemy->query_temp("weapon")) {
		damage = weapon->query("weapon_prop/damage");
	}
	//�����ڻ���$N�������·�Ҫ��$n���ϵĻ����ڻ�/������set("material", "steel");
	//query("material") != "ice" ) "bone");*/

	return 1;
}

//��ȡ��������������
mapping query_trait(object who)
{/*
	mapping m;
	string spells = who->query_skill_mapped("spells");
	if(!spells || !trait[spells]) spells = "misc";
	if(spells == "pingtian-dafa") spells = "taiyi";

	m = trait[spells];
	if(!m["id"]) m["id"] = "dragon";
	if(!m["short"])
		m["short"] = m["color"] + m["name"] + NOR + "(Dragon)";
	return m;*/
}


//�������
int human(object who)
{
	mapping buff = BUFF->find(who, BUFF_ID);
	int mana = who->query("max_mana") / 10;

	if(!buff) return notify_fail("��û�д�������״̬��\n");
	if(who->is_busy()) return notify_fail("����æ�š�\n");
	if(mana > who->query("mana")) return notify_fail("��ķ��������Ա�����Ρ�\n");
	who->add("mana", -mana);
	msv(HIC"$Nҡ��һ�䣬�������Ρ�\n"NOR, who);
	BUFF->remove(buff);
	who->start_busy(1);
	return 1;
}

//ʩչ��������
void skill(object who, object target)
{
}

