// by firefox 10/01/2010
// ����ɱ-���ɾ���

#include "xys.h"


/********************************��������***********************************/

//�����ڳ��������
int here_count()
{
	int n = 0;
	foreach(string id, mapping who in _chars) {
		if(is_dead(who) || who["state"][S_NOT_HERE]) continue;
		n++;
	}
	return n;
}

//��ȡ�����������
string weapon_type(mapping me)
{
	return me["cards"][C_WEAPON]["skill_type"];
}

//���ӻ������Ѫ
int add_kee(mapping me, int n)
{
	if(n >= 0) me["kee"] = min2(me["kee"] + n, 100);
	else me["kee"] += (100 - me["apply"]["armor"]) * n / 100;
	return me["kee"];
}


//���ӻ����hp����
int add_hp(mapping me, string prop, int n)
{
	me[prop] += n;
	me[prop] = min2(me[prop], 100);	
	return me[prop];
}

//��ȡ��Чskill
int eff_skill(mapping me, string skill)
{
	return me["skills"][skill] + me["apply"][skill];
}

//һ�㷨�������ж�
int cast_success(mapping card, mapping me, mapping target)
{
	int ap = eff_skill(me, "spells") * card["success"] / 100;
	int dp = eff_skill(target, "spells");
	
	if(target["state"][S_NO_CAST]) dp / 2;

	return ap / 2 >= random(dp);
}

/********************************��ͨ��������***********************************/

mapping _attack_spells = ([	
	
	//				 name			success	d_type	damage	cost	cd
	"bighammer"	: ({ "������ħ��",	120,	3,		30,		45,		3,
		"��ɱֹɱ��ǿ����",
		HIC"$N�������˼������ģ�������ֳ����У���Ҷ�����ߣ���ִ��ħ����$n��ͷ���£�\n"NOR,
		HIC"����Ҹ����ţ����û��$n�ұ⣡\n"NOR,
		HIC"����$n��ǧ��һ��֮�ʶ��˿�����\n"NOR,
	}),
	
	"light"		: ({ "�����",		120,	1,		30,		30,		3,
		"���繥��",
		HIC"$N�������˾����ģ�����߳���ĸ��ͭ����ת����������һ���������$n��\n"NOR,
		HIR"������͡���һ��������$n����͸��������ϳ�һ��Ѫ�����䵽�������⣡\n"NOR,
		HIC"����ͣ���һ��$n�ŵ���һ�ɽ�ζ������ֻ�յ��˼���ͷ����\n"NOR,
	}),

	"thunder"	: ({ "������",		120,	2,		30,		30,		3,
		"���׺䶥",
		HIC"$N�������˾����ģ�����߳��׹�����׶�������$n��ͷ��ը��һƬ���ף�\n"NOR,
		HIR"���$n�����������ð���ǣ����񲻶����������ڵأ�\n"NOR, 
		HIC"˭֪$n���޷�Ӧ�����������Ƶġ�\n"NOR, 
	}),

	"zhenhuo"	: ({ "̫�����",		120,	3,		20,		20,		3,
		"��������",
		HIC"$N����ָͷѸ������ͻȻ����һ�磡��Ȼ��������������һ����$n��ȥ��\n"NOR,
		HIC"���$n���յý�ͷ�ö\n" NOR, 
		HIC"����$n����һ���Ͷ��˿�����\n" NOR, 
	}),

	"zouxiao"	: ({ "��������",		120,	2,		30,		30,		3,
		"�����������������ã���",
		HIM"$N����$n������һ������������������̾Ϣ�����ƿ�����\n"NOR,
		YEL"��$n������ţ���Ϊ������\n"NOR,
		HIG"$n��������������Ī������ĸе�һ�������������������ˮ�������¡�\n"NOR,
	}),

	"gouhun"	: ({ "������",		120,	2,		30,		30,		3,
		"û��������Ҳ�¹����",
		HIC"$N��$n������Ц�ţ������������������������㵽���������\n" NOR,
		HIC"$n�ܵ�$NӰ�죬��Ȼ�е�겻�����ˣ�\n" NOR,
		HIC"����$n����רע����$N������\n" NOR, 
	}),

	"tuntian"	: ({ "ħ������",		120,	1,		30,		30,		3,
		"Ѫ���ڣ�����ʮ�����",
		HIC"$N�������˾����ģ��������һֻ���������ʨ�ӣ��ſ�Ѫ������$nҧȥ��\n"NOR,
		HIR"���$n��ҧ�˸����ţ�\n"NOR,
		HIC"$n��æһ��������һ�ԡ�\n"NOR,
	}),
	
	"jieti"		: ({ "��ħ�����",	20,		1,		100,	50,		3,
		"Ѫ���ڣ�����ʮ�����",
		HIC"$N�������˼������ģ���Ȼ��$N���Լ���ͷ����һҧ��һ��Ѫ����$n���˹�ȥ��\n"NOR,
		HIR"���$n��Ѫ����ס����ʱ����һ���ҽУ���$NҲ����һ̱�����ڵ��ϡ�\n"NOR,
		HIR"���Ѫ��$n����������������ס��$N��$N��̾һ��������һ̱�����ڵ��ϡ�\n"NOR,
		([ "kee" : -100 ]),
	}),

	"love"		: ({ "�����",		150,	4,		30,		30,		3,
		"��ͯ����...",
		HIM"\n$N���������$n�������ﲨĿ�����룬���������...\n\n"NOR,
		HIM"$n�������ĵ��������Գ֡�\n"HIC"$N����һ��������\n"NOR,
		HIM"$n�·𲻽���飬��$N�����޶á�\n\n"NOR,
	}),
]);

//һ�㷨����������
int cast(mapping card, mapping me, mapping target)
{
	int damage = card["damage"];
	
	if(!cast_success(card, me, target)) return 0;
	
	if(card["d_type"] & 1) add_kee(target, -damage);
	if(card["d_type"] & 2) add_hp(target, "sen", -damage);
	if(card["d_type"] & 4) add_hp(target, "force", -damage);
	if(card["d_type"] & 8) add_hp(target, "mana", -damage);
	return 1;
}

//������ͨ��������
mapping attack_spell(string id)
{
	mixed* a = _attack_spells[id];
	mapping card = ([
		"type"			: "����",
		"name"			: a[0],
		"comment"		: a[6],

		"cd_prop"		: S_NO_CAST,
		"cd"			: a[5],
		"cost_prop"		: "mana",
		"cost"			: a[4],
		"dist"			: 1,

		"fun"			: (: cast :),
		"success"		: a[1],
		
		"msg_start"		: a[7],
		"msg_ok"		: a[8],
		"msg_fail"		: a[9],
		
		"d_type"		: a[2],
		"damage"		: a[3],
	]);

	return card;
}

/********************************����ǿ������***********************************/

mapping _powerup_spells = ([
	
	//				 name			a_type		a_num	cost	cd
	"lianhua"	: ({ "��������",		"spells",	20,		20,		6,
		"�û����������γɷ�������",
		HIC"$N΢һ���񣬱���ó�һ���������ɫ�������֡�\n"NOR,
	}),
	
	"jingxin"	: ({ "���ľ�",		"dodge",	20,		20,		6,
		"���繥��",
		HIW"$N΢һ���������ľ�����ʱ��ƽ���ȣ�����Χһ�о����мӡ�\n"NOR,
	}),

	"hell_pu"	: ({ "������������",	"damage",	20,		20,		4,
		"�����ڰ�������ǿ���Լ�",
		HIR"$N΢һ��������������������ͷ��ð��һ�������������ֳ�һ�����Ρ�����\n",
	}),

	"shield"	: ({ "���ۻ���",		"armor",	20,		20,		6,
		"�������ۣ������Լ�",
		HIC"$N΢һ�������������ķ����������¶�ʱ�������ɫ�����ۡ�\n"NOR,
	}),
]);

//һ����ǿ����
int powerup(mapping card, mapping me, mapping target)
{
	mapping buff = ([
		"id"		: "powerup",
		"duration"	: card["cd"] / 2,
		"apply"		: card["buff"],
	]);
	return buff_add(me, buff);
}

//������ͨ��������
mapping powerup_spell(string id)
{
	mixed* a = _powerup_spells[id];
	mapping card = ([
		"type"			: "����",
		"name"			: a[0],
		"comment"		: a[5],

		"no_target"		: 1,
		"cd_prop"		: S_NO_POWERUP,
		"cd"			: a[4],
		"cost_prop"		: "mana",
		"cost"			: a[3],
		
		"fun"			: (: powerup :),
		"msg_start"		: a[6],		
		"buff"			: ([ a[1] : a[2] ]),
	]);

	return card;
}

/********************************��ͨ��������***********************************/

mapping _attack_perform = ([
	
	//				      name			success	damage	cost	cd		weapon
	"pili"			: ({ "��������",		80,		50,		50,		6,		"stick",
		"��ɱֹɱ��ǿ����",
		HIC"\n$N���㾫������һת��������������$n���������У�\n"NOR,
		"$n�������������ذ������£�\n",
		"$n����һ����û�˵��ֺ���\n",
	}),

	"sanban"		: ({ "�޵����師",	120,	30,		30,		6,		"axe",
		"�޵����師",
		CYN"$Nһ�����ȣ����ϣ��������Ͷ��䣡����һ���ǳɣ�\n"NOR,
		"$n��ͼ����ܿ�����Ϊʱ���������ڼ��ϣ�����һ����ɼ��ǵ��˿ڣ�\n",
		"$n����һ�����󸫴���һ�󾢷�����ն�£���û�˵�$n�ֺ���\n",
	}),

	"huima"			: ({ "����ǹ",		120,	20,		20,		3,		"spear",
		"����ȡʤ��ǹ������",
		YEL"$N���һǹ��ͷ���ߣ�$n��׷���ᣬ����$N���淴���̣�"NOR,
		WHT"��$N�Ĺ�����Ȼ������ȴ������գ�˿��û���ܶ�$n����κ���в��\n"NOR,
		WHT"��$n���ɿ���$N�Ĺ�ƣ�������$N�ĵ�������һ����������$N����ǰ��\n"NOR,
	}),

	"chaofeng"		: ({ "���񳯷�",		120,	20,		20,		3,		"sword",
		"͵Ϯ����������ٲ���ɥ��",
		HIW"ֻ��$N���н��������ó����콣â�����������������Ͷ�ְ���$n������\n"NOR,
		HIW"$n��æ����һת�����������������������컨����һ����\n"NOR,
		HIW"$n���������������������˽�����\n"NOR,
	}),

	"qixiu"			: ({ "����",			120,	20,		20,		3,		"sword",
		"���޾���",
		"$N�趯���н�����ʱ�������������޹⡣�谵��$n���ֽ���ֱָǰ�ģ�\n",
		"$n��æ����ȴ��Ϊʱ������ǰ"HIR"һ��Ѫ��"NOR"�紺�������š�\n",
		"$n��æ����"HIC"����"NOR"մ�¶�������������һ���亹��\n"NOR,
	}),

]);


//һ������������
int perform(mapping card, mapping me, mapping target)
{
	string skill = weapon_type(me);
	int damage = me["apply"]["damage"] * card["damage"] / 100;

	int ap = eff_skill(me, skill) * card["success"] / 100;
	int dp = eff_skill(target, "dodge");
	int pp = eff_skill(target, "parry");

	if(target["state"][S_BUSY]) {
		dp /= 3;
		pp /= 3;
	}
	if(ap < random(dp + pp)) return 0;
	
	add_kee(target, -damage);

	return 1;
}

//������ͨ��������
mapping attack_perform(string id)
{
	mixed* a = _attack_perform[id];
	mapping card = ([
		"type"			: "����",
		"name"			: a[0],
		"comment"		: a[6],

		"need_weapon"	: a[5],
		"cd_prop"		: S_NO_MOVE,
		"cd"			: a[4],
		"cost_prop"		: "mana",
		"cost"			: a[3],
		"dist"			: 1,

		"fun"			: (: perform :),
		"success"		: a[1],
		"damage"		: a[2],
		"msg_start"		: a[7],
		"msg_ok"		: a[8],
		"msg_fail"		: a[9],
	]);
	return card;
}

/********************************���Ʒ���***********************************/

mapping _heal_spells = ([
	
	//				 name			h_type		h_num	cost	cd
	"heal"		: ({ "������",		"sen",		30,		30,		3,
		"�÷������⾫���˺�",
		HIY"$N���������˶����ţ�����������$n��̨�������ؽ���������$n����....\n\n" +
		"���˲��ã�$N��ͷ��ð������ĺ��飬$n�³�һ�����������������ö��ˡ�\n" NOR,
	}),
	
	"suliao"	: ({ "����",			"kee",		30,		30,		4,
		"�÷������˿ڿ�������",
		HIY"$N˫�־�����ǰ����������״�����˼����䡣\n"NOR +
		HIY"�漴��$N��˫����ȫ�����²���һ�飬˫�ֵ������˿ھ�Ȼ���˴�룡\n"NOR,
	}),

]);

//�������Ʒ���
mapping heal_spell(string id)
{
	mixed* a = _heal_spells[id];
	mapping card = ([
		"type"			: "����",
		"name"			: a[0],
		"comment"		: a[5],

		"no_target"		: 1,
		"cd_prop"		: S_NO_CAST,
		"cd"			: a[4],
		"cost_prop"		: "mana",
		"cost"			: a[3],
		
		"msg_start"		: a[6],		
		"add"			: ([ a[1] : a[2] ]),
	]);
	return card;
}

/********************************AOE����***********************************/

mapping _aoe_spells = ([
	
	//				  name			success	d_type	d_num	cost	cd
	"roar"		: ({ "����",			120,	2,		10,		30,		4,
		"�����������С�Ķ���",
		HIR"\n$N�˺��������������һ��������Ȼ��������ɽ����Х���������\n\n",
		"$n������ǰһ�������ð������ʹ������Ҫ�ѿ�һ����\n",
	}),
	
	"sanmei"	: ({ "�������",		120,	3,		10,		50,		4,
		"���ƶ����ƾ���",
		"\n$N���Լұ����ϴ�����ȭ��������������𣬱���ð�̣���̼䣺\n\n" +
		HIR"��������ӯ���ǣ��պ�������غ졣ȴ�ƻ��ַ����£�����̿м��������\n\n"NOR,
		"$n���յý�ͷ�ö\n",
	}),

]);

//Ⱥ�巨����������
int aoe(mapping card, mapping me, mapping target)
{
	int damage = card["damage"];

	foreach(string k, mapping who in _chars) {
		int dp = eff_skill(who, "spells");

		if(!card["aoe_all"] && who == me) continue;
		if(who["state"][S_NOT_HERE]) continue;
		if(!cast_success(card, me, target)) continue;
	
		if(card["d_type"] & 1) add_kee(who, -damage);
		if(card["d_type"] & 2) add_hp(who, "sen", -damage);
		msv1(card["msg_eff"], me, who);
	}
	return 1;
}

//����aoe����
mapping aoe_spell(string id)
{
	mixed* a = _aoe_spells[id];
	mapping card = ([
		"type"			: "����",
		"name"			: a[0],
		"comment"		: a[6],

		"no_target"		: 1,
		"cd_prop"		: S_NO_CAST,
		"cd"			: a[5],
		"cost_prop"		: "mana",
		"cost"			: a[4],

		"d_type"		: a[2],
		"damage"		: a[3],
		"fun"			: (: aoe :),
		
		"msg_start"		: a[7],
		"msg_eff"		: a[8],
	]);

	return card;
}

/********************************���Ʒ���***********************************/

mapping _control_spells = ([
	
	//				 name			success	cost	cd		type	state
	"mihun"		: ({ "�Ի�",			120,	30,		4,		"����",	S_NO_MOVE,
		"Ӣ���ѹ����˹�",

		HIC"$N��ͷ�������˾����ģ���̧��ͷ����$n���ĵ�һЦ��\n"NOR,
		HIR"$n������ؿ���$N������ϧ��֮����Ȼ���𣬾�Ȼ�����Լ���ս��֮�С�\n"NOR,
		HIR"$n���ĵؿ���$Nһ�ۣ�����Ϊ������\n"NOR,
	}),

	"huimeng"	: ({ "����",			120,	30,		4,		"����",	S_NO_CONTROL,
		0,

		HIM"$N������$n��˫�ۣ���$n�����������ţ���С��������˯����������\n"NOR,
		HIM"$n��֪�����Ĺ�Ƿ��������Ƥ���أ�����֧�ֲ�ס��������˫�ۡ�\n"NOR,
		HIM"$n���һ����˫Ŀһ�ţ��������䣡$N⧲�����������һ����\n"NOR,
	}),

	"fengbo"	: ({ "�޾��粨",		120,	30,		6,		"����",	S_BUSY,
		0,

		HIC"$N��չ��������һ�棬��һ�棬�ó�������С�⻷��$n��ȥ��\n\n"NOR,
		HIR"$N��Ȼ����⻷��ס����ʱĿ�ɿڴ�����֪���룡\n"NOR,
		HIR"����ȴ��$N���ƣ����䲻����$n�������˸����ֲ�����\n"NOR,
	}),

	"pozhan"	: ({ "����",			120,	30,		4,		"����",	S_BUSY,
		0,

		CYN"$N����ʽͻȻһ�䣬���ȫ���·����������������ٳ���\n"NOR,
		CYN"$n�빥��ȴ������١�����������˸����ֲ�����\n"NOR,
		CYN"����$n������$N����ͼ����û���ϵ���\n" NOR,
	}),

	"bone-fire"	: ({ "�����׹ǻ�",	120,	30,		4,		"����",	S_BUSY,
		0,

		"$N������$nһָ����㲻�ײ����"HIB"�׹�"NOR"��$n��������...\n"NOR,
		HIC"$n��%sͻȻ��𣬾���ʧ�룬ƴ���˴�\n"NOR,
		HIC"$nһ�����׹����Ʈɢ��...\n"NOR,
	}),

	"sheng"		: ({ "�Ͻ���",		150,	30,		4,		"����",	S_NO_MOVE,
		"̫���Ͼ�������",

		"$N������������ͳ��Ͻ�����$n�׽���ȥ��\n",
		"$n�������������˸������������������ã�\n",
		"$n���һ�������˹�ȥ��\n",
	}),

	"qiankun"	: ({ "����Ǭ��",		150,	50,		4,		"����",	S_NOT_HERE,
		"��ԭ���ɵľ����������Ҳ����",

		HIR"$N�૵����˼������ͻȻ����һ�ӳ�$n���˹�ȥ��\n"NOR,
		HIR"���ವ�һ��$n��װ�˽�ȥ��\n"NOR,
		HIR"�����$n����һ�ƣ������ס$N�Լ����Դ���\n"NOR,

		"$N��$n�����̽���Դ����κ��������˳�����\n",
	}),

	"hulu"		: ({ "�Ͻ��«",		120,	30,		4,		"����",	S_NOT_HERE,
		"̫���Ͼ�װ�ɵ��ĺ�«",

		"$N������������ͳ��Ͻ��«�׶����ϣ��䲻���ض�$nһ����$n��\n",
		"$n˳�ڴ�����ڣ�\n���֮��$n���Ͻ��«�ȵ�һ�����˽�ȥ��\n",
		"$n֪����թ���տڲ�����ʲô��û������\n",

		"$N���Ͻ���«��̽���Դ����κ��������˳�����\n",
	}),

	"jingping"	: ({ "��֬��ƿ",	120,	30,		4,		"����",	S_NOT_HERE,
		"һֻ����͸������֬��ƿ",

		"$N������������ͳ���֬��ƿ�׶����ϣ��䲻���ض�$nһ����$n��\n",
		"$n˳�ڴ�����ڣ�\n���֮��$n����֬��ƿ�ȵ�һ�����˽�ȥ��\n",
		"$n֪����թ���տڲ�����ʲô��û������\n",

		"$N����֬��ƿ�����ͷ�������������˳�����\n",
	}),
	
]);

//״̬/���Ʒ���
int state(mapping card, mapping me, mapping target)
{
	if(!cast_success(card, me, target)) return 0;
	if(!buff_add(target, card["buff"])) return 0;

	if(card["buff"]["state"][S_NO_WIELD]) unequip(target, C_WEAPON);
	return 1;
}

//��������
mapping state_spell(string id)
{
	mixed* a = _control_spells[id];
	mapping card = ([
		"type"			: a[4],
		"name"			: a[0],
		"comment"		: a[6],

		"cd_prop"		: S_NO_CAST,
		"cd"			: a[3],
		"cost_prop"		: "mana",
		"cost"			: a[2],
		"dist"			: 1,

		"fun"			: (: state :),
		"success"		: a[1],
		
		"msg_start"		: a[7],
		"msg_ok"		: a[8],
		"msg_fail"		: a[9],
		
		"buff"			: ([ 
			"id"			: "control",
			"duration"		: a[3] / 2,
			"state"			: ([ a[5] : a[3] / 2 ]),
			"msg_remove"	: (sizeof(a) > 10 ? a[10] : 0),
		]),
	]);

	return card;
}

/********************************dot����***********************************/

mapping _dot_spells = ([	
	
	//				 name			success	cost	cd		d_type	damage
	"shiyue"	: ({ "ʴ��",			120,	60,		6,		3,		10,
		"��¹���",

		"$N��ͷĬĬ�������ģ����н�������һ�Ź���ѩ�׵������ƺ��������͵Ĺ�â��\n",
		HIR"$n����$N����̬֮���������ɷ������һ����ȴ�����ǹ���һ����ͻȻ����$n��\n"NOR,
		HIR"$N��ɫ�԰ף��ƺ�������֧�����������н�����ȥ����\n"NOR,
		
		HIR"$N��ɫ�԰ף�Խ��Խ������\n"NOR,
	}),

	"inferno"	: ({ "������",		120,	40,		4,		1,		20,
		0,

		HIB"$N˫��һ�꣬��ʱȼ��һ����ɫ�Ļ��棬����׹�Ʈ����$n��\n"NOR,
		HIB"��ž����һ����ɫ������$N����ȼ������Ȳ�����$N£�����롣\n"NOR,
		HIB"��ž����һ����ɫ������$N����ȼ��$N����������\n"NOR,

		HIB"һ����ɫ������$N���Ͼ�����ȼ���š�\n"NOR,
	}),	
]);

//dot����
int dot(mapping card, mapping me, mapping target)
{
	mapping buff = ([
		"id"		: card["dot_id"],
		"duration"	: card["cd"],
		"dot"		: card["buff"],
		"msg_dot"	: card["msg_eff"],
	]);
	return buff_add(target, buff);
}

//��������
mapping dot_spell(string id)
{
	mixed* a = _dot_spells[id];
	mapping card = ([
		"type"			: "����",
		"name"			: a[0],
		"comment"		: a[6],

		"cd_prop"		: S_NO_CAST,
		"cd"			: a[3],
		"cost_prop"		: "mana",
		"cost"			: a[2],
		"dist"			: 1,

		"fun"			: (: dot :),
		"success"		: a[1],
		
		"msg_start"		: a[7],
		"msg_ok"		: a[8],
		"msg_fail"		: a[9],
		"msg_eff"		: a[10],
		
		"buff"			: ([]),
	]);

	if(a[4] & 1) card["buff"]["kee"] = a[5];
	if(a[4] & 2) card["buff"]["sen"] = a[5];

	return card;
}

/********************************��������***********************************/

//ײ
mapping zhuang_spell()
{
	mapping card = ([
		"type"			: "����",
		"name"			: "ײ",
		"comment"		: "ײ������",

		"cd_prop"		: S_NO_CAST,
		"cd"			: 3,
		"cost_prop"		: "force",
		"cost"			: 20,
		"dist"			: 1,

		//�ı��ٽ�Ŀ��λ��
		"fun"			: function(mapping card, mapping me, mapping target)
			{
				mapping who;
				if(here_count() < 3) return 0;
				if(!cast_success(card, me, target)) return 0;

				if(target == find_next(me)) who = find_next(target);
				if(target == find_prevous(me)) who = find_prevous(target);
				if(!who) return 0;
				
				swap2(_order[target["order"]], _order[who["order"]]);
				swap2(target["order"], who["order"]);

				return 1;
			},
		"success"		: 120,
		
		"msg_start"		: HIC"$N��Ȼ�˺�������һ��ͷ�����ؾ���$nײȥ��\n"NOR,
		"msg_ok"		: HIC"���$n������������ײ���������ݰ�ķ��˳�ȥ��\n"NOR,
		"msg_fail"		: HIC"�����$n�Է���һ�ƣ�$Nûײ��ȥ��\n"NOR,

	]);

	return card;
}


//���λ�Ӱ
mapping yixing_spell()
{
	mapping card = ([
		"type"			: "����",
		"name"			: "���λ�Ӱ",
		"comment"		: "��Ŀ�꽻������",

		"cd_prop"		: S_NO_CAST,
		"cd"			: 7,
		"cost_prop"		: "mana",
		"cost"			: 60,
		"dist"			: 1,

		//������Ѫ��������
		"fun"			: function(mapping card, mapping me, mapping target)
			{
				if(!cast_success(card, me, target)) return 0;
				swap2(me["name"], target["name"]);
				swap2(me["kee"], target["kee"]);
				for(int i = BASIC_CARDS; i < BASIC_CARDS + 3; ++i) {
					unequip(me, i);
					unequip(target, i);					
				}
				for(int i = BASIC_CARDS + 3; i < CARDS_SIZE; ++i) {
					swap2(me["cards"][i], target["cards"][i]);
				}
				return 1;
			},
		"success"		: 90,
		
		"msg_start"		: "$N��ȣ�"HIY"���λ�Ӱ"NOR"��$N��$n������һ��ת�������ֲ���˴ˡ�\n",
		"msg_ok"		: "Ƭ������ͣ�������Եö����Ǳ���\n",
		"msg_fail"		: "Ƭ������ͣ�������Եö����Ǳ���\n",

	]);

	return card;
}

//�ƻ��
mapping yihun_spell()
{
	mapping card = ([
		"type"			: "����",
		"name"			: "�ƻ��",
		"comment"		: "���Ʊ��˵�˼��",

		"cd_prop"		: S_NO_CAST,
		"cd"			: 4,
		"cost_prop"		: "mana",
		"cost"			: 30,
		"dist"			: 1,

		//
		"fun"			: function(mapping card, mapping me, mapping target)
			{
				if(!cast_success(card, me, target)) return 0;
				//HIW"$N�ַ���ͷ��ҡҡ�λΣ������˹�����\n\n"NOR,
				target["state"][S_NO_CONTROL] = 2;
				return 1;
			},
		"success"		: 90,
		
		"msg_start"		: HIC"\n$N�������ƻ�󷨡���ֻ��$NĿ����磬ֱ����$n���С�\n"NOR,
		"msg_ok"		: "$n���������㱣���ʧ�����ǡ�ĬĬվ��$N���\n\n"NOR,
		"msg_fail"		: "$n����������Ŀ�����⡣\n\n"NOR,		
	]);

	return card;
}

//�����
mapping zhuo_fabao()
{
	mapping card = ([
		"type"			: "����",
		"name"			: "�����",
		"comment"		: "����ȡ���˱���",

		"cd_prop"		: S_NO_CAST,
		"cd"			: 7,
		"cost_prop"		: "mana",
		"cost"			: 30,
		"dist"			: 1,

		//
		"fun"			: function(mapping card, mapping me, mapping target)
			{
				mapping weapon = target["cards"][C_WEAPON];
				if(!cast_success(card, me, target)) return 0;
				if(weapon["skill_type"] == "unarmed") return 0;

				unequip(target, C_WEAPON);

				//todo
				return 1;
			},
		"success"		: 150,
		
		"msg_start"		: "$N�������дʣ���������������"NOR,
		"msg_ok"		: "$n���еı����ѳֲ������ѱ��������ȥ��\n\n"NOR,
		"msg_fail"		: "$nһ�����㿪�˿��еĽ������\n"NOR,
	]);

	return card;
}
