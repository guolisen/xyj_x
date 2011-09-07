
#include <xyj_x.h>
#include <ansi.h>

#define MSG_PAT				"$n���������$N��ͷ��"
#define MSG_HUG				"$n����$N������غ���ҡ������"
#define MSG_LICK			"$n���������$N��ë��"
#define MSG_PUSH			"$n����Ĺ���$Nһ�£�$Nҡҡ�λε�վ��������"


#define ANIMAL_LIMBS	({ "ͷ��", "����", "����", "��", "��Ƥ", "ǰצ", "��צ", "β��"})
#define CATTLE_LIMBS	({ "ͷ��", "����", "����", "��", "��Ƥ", "ǰ��", "����", "β��"})
#define BIRD_LIMBS		({ "ͷ��", "����", "����", "��", "��Ƥ", "��צ", "��צ", "β��"})
#define SNAKE_LIMBS		({ "ͷ��", "����", "����", "��Ƥ", "β��"})


mapping _subs;			//��������
mapping _traits;		//��������
string* _weapons;		//����
mapping _born;			//������Ϣ

void init_var();

void create()
{
	seteuid(getuid());

	init_var();

	//��ȫ�������Ϣ(�û�����ʡ��color/short/unit/long)
	foreach(string name, mapping m in _subs) {
		m["name"]	= color_name(name, m["color"]);
		m["unit"]	= or2(m["unit"], "��");
		m["long"]	= or2(m["long"], "һ" + m["unit"] + name + "��");		
	}
	if(!_traits["limbs"]) _traits["limbs"] = ({ "ͷ��", "����" });
}

//�õ��������
string random_name()
{
	return random1(keys(_subs));
}

//����
int born(object who)
{
	if(who->move(_born["place"])) {
		object env = environment(who);
		object sb = new(_born["sb."]);
		object ob = present(sb->query("id"), env);
		if(ob) {
			destruct(sb);
			sb = ob;
		} else {
			sb->move(env);
		}
		who->delete_temp("block_msg/all");
		msv(_born["msg"] + "\n"NOR, who, sb);
	}
}

//��ѯ����
string* query_weapons()
{
	return _weapons;
}

#define ZS_BONUS		10			//ת��һ���������ܵİٷֱ�

//��ȡ��������Ҫ��buff
mapping make_buff(object who)
{
	int ratio = 100 + RACE_D->query(who, "num") * ZS_BONUS;
	int skill = who->query_skill("spells", 1) * ratio / 100;
	int kee =  _traits["kee"] * skill/ 100;
	int sen =  _traits["sen"] * skill/ 100;
	int name = RACE_D->query(who, "name");
	mapping sub = _subs[name];

	mapping buff = ([
		"comment"	: "�ָ�����չ��ԭʼ��ò��",
		"class"		: "������",
		"temp"		: ([
			"apply/name"	: ({ name }),
			"apply/id"		: sub["ids"],
			"apply/long"	: ({ sub["long"] + "\n" }),
			"No_Wield"		: 1,
			"powerup"		: 1,
		]),
		"add_apply"	: _traits["add_apply"],
		"replace"	: ([
			"limbs"			: _traits["limbs"],
		]),
		"add"		: ([
			"max_kee"		: kee,
			"eff_kee"		: kee,
			"kee"			: kee,
			"max_sen"		: sen,
			"eff_sen"		: sen,
			"sen"			: sen,
		]),

		"post_act"	: function(mapping buff) {
			object me = buff["me"];
			string* props = ({"kee", "eff_kee", "sen", "eff_sen"});			
			foreach(string prop in props) {		//��ֹ����
				me->set(prop, max2(me->query(prop), 1));
			}
		},
		"interval"	: _traits["interval"],
		"timer_act"	: _traits["timer_act"],
	]);

	//������Щ���հٷֱ�����������
	foreach(string k, int v in _traits["add_apply_x"]) {
		buff["add_apply"][k] += v * skill / 100;
	}
	//���㼼���׺�
	foreach(string k in ({"unarmed", "dodge", "force", "spells"}) ) {
		string mapped = who->query_skill_mapped(k);
		int v = _traits["skill_bonus"][mapped];
		buff["add_apply"][k] += v * skill / 100;
	}

	//����force_factor
	buff["replace"]["force_factor"] = who->query_skill("force") / 2
		+ buff["add_apply"]["force"] / 2;

	return buff;
}

