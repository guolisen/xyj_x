// by firefox 11/21/2009

inherit SSERVER;

#include <xyj_x.h>
#include <ansi.h>

#define ID				"gouhun2"
#define NAME			HIB"����"NOR
#define DURATION		30
#define CD				20

#define BUFF_ID			"shlp"
#define BUFF_NAME		"ʧ������"

mapping po_tab = ([
	"dodge"			: ({ "����", HIW, "ƽ��֮��/�Ṧ",}),
	"karma"			: ({ "����", HIG, "����֮��/��Ե",}),
	"intelligence"	: ({ "����", HIM, "�ǻ�/����",}),
	"attack"		: ({ "����", HIY, "Ʒ��/����",}),
	"strength"		: ({ "����", HIC, "����",}),
	"composure"		: ({ "����", HIB, "����/����",}),
	"courage"		: ({ "����", HIR, "а��/��ʶ",}),
]);

void po_lost(object target, int n);

int cast(object me, object target)
{
	int success = 0;
	int skill = me->query_skill("gouhunshu", 1);
	int mana = 25 + 2*(int)me->query("mana_factor");
	mapping req = ([
		"skill1"	: ([ "gouhunshu"	: 250]),
		"prop"		: ([ "mana"			: mana,		"sen"			: 50]),
	]);
	mapping cmp_parm = ([
		"prop"		: ([ "mana" : 2, "daoxing" : 2, "mana_factor" : 2 ]),
		"skill"		: ([ "spells" : 4]),
	]);

	target = BTL->get_victim(me, target);
	if(!objectp(target)) return notify_ok("��Ҫ��˭�Ļ��ǣ�\n");

	if(!BTL->require(me, NAME, req)) return 1;
	if(!cd_start(me, ID, CD)) return notify_fail("����ʱ������ʹ��"NAME"��\n");
	BTL->pay(me, req["prop"]);

	message_vision(HIC"$N��$n������Ц�ţ������������������������㵽���������\n"NOR, me, target);

	success = BTL->cmp_parm(me, target, cmp_parm);
	trace("gouhun2 success = " + success);
	success = MATH->random_pct(success, 30);	//����30%�������
	success = (success - 50)/20;		//ƽ��2.5������
	success = min2(success, 7);			//���7
	if(success > 0) {
		int damage = target->query("max_sen") * success / 10;
		target->receive_damage("sen", damage, me);
		target->receive_wound("sen", damage, me);
		po_lost(target, success);
		COMBAT_D->report_sen_status(target);
	} else {		
		message_vision(HIC"����$n����רע����$N������\n"NOR, me, target);
	}
	BTL->fight_enemy(target, me);
	me->start_busy(2);
	return 1;
}

//Ŀ��ʧȥn������
void po_lost(object target, int n)
{	
	mapping flags = target->query_temp(BUFF_ID);	//�Ѿ�ɢȥ�ġ��ǡ��ı�Ǽ���
	string* remains = keys(po_tab) - (mapp(flags) ? keys(flags) : ({}));	//ʣ�µġ��ǡ��ļ���
	int size = sizeof(remains);
	n = min2(n, size);
	
	if(size) {
		string colors = "";
		foreach(string key in MATH->random_elem(remains, n)) {
			string color = po_tab[key][1];
			string name = color + po_tab[key][0] + NOR;
			mapping buff = ([
				"id"		: BUFF_ID + key,
				"name"		: BUFF_NAME + "-" + name,
				"comment"	: name + "�������ˣ�ʧȥ��" + po_tab[key][2] + "��",
				"duration"	: 1 + random(DURATION * 2),
				"temp"		: ([ BUFF_ID + "/" + key : 1 ]),
				"add_apply" : ([ key : -BTL->query_attr(target, key) ]),
				"stop_msg"	: "һ��" + color + "����"NOR"����Ʈ��$N��������û��$N��ͷ����\n\n",
			]);
			if(size < 3 && !target->query_temp("no_move")) {
				buff["temp"]["no_move"] = 1;
				//message_vision("$Nʧ�����ǣ�����ľ����\n", target);
			}
			BUFF->add(target, buff);
			colors += color + COLOR->ch(color);
		}
		//message_vision(colors + NOR + chinese_number(n) + "������"NOR"��$N�������������ɢ��ȥ��\n"NOR, target);
		message_vision(chinese_number(n) + "������"NOR"��$N�������������ɢ��ȥ��\n"NOR, target);
	} else {	//���ǹ��ˣ�����ʧȥ�����Ҫ����		
		message_vision(YEL"������$Nͷ��ɢ����$N�Ѿ����꾡ʧ�����ǽ�ɢ......\n"NOR, target);
	}
}
