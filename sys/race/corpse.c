
/*
���Ǽ�������һ���֣������׹Ƿ��ˡ�
���ߵ��������Ǹ�Ǳ�����ֵĽ�ʬ

Ǳ�齩ʬ

�׹Ǿ�

�ٱ�ʬħ


 /d/changan/fendui
 /obj/corpse


$n��$N˵�������������ģ������ա��������������ˣ�


���֣�����ͻȻ���һֱ�֣�����$N��������������

ѱ����$N������˵�������ˣ���ԸΪ��Ч�ͣ���Ҫ�����ҡ�

int _index = 0;

mixed* _tab = ({
	({ "", "", "�׹Ƕ���", }),
	({ HIW, NOR, "ʬ��׹Ǿ�", }),
});
//�ı�����
private void change_name()
{
	string c1 = _tab[_index][0];
	string c2 = _tab[_index][1];
	set_name(c1 + "�׾���" + c2, ({ "bai jingjing", "bai", "jingjing" }));
}

	if(at_night() && is_full_moon())

void init()
{	
	object me = this_object();
	object who = this_player();
	object weapon = who->query_temp("weapon");

	string time = CHINESE_D->chinese_date(time());
	_index = (NATURE_D->query_current_day_phase() >= 6)	//��Բ֮ҹ
		&& (strsrch(time, "��ʮ����") >= 0);
	change_name();

	if(_index) {
		if(weapon) weapon->unequip();
		message_vision("$N��ͷ�׷������ƺ�ƣ��趯��ɭɭ����צ������$n��\n", me, who);
		me->kill_ob(who);		
	} else {
		if(!weapon) command("wield all");
	}

	::init();

	add_action("do_kiss", "kiss");

}

int do_kiss(string arg)
{
	if(arg) {
		object target = present(arg, environment());
		if(target == this_object()) {
			object who = this_player();
			target->remove_all_killer();
			who->remove_all_killer();
			message_vision("$N��æ��ס$n��������������$n����ư���۾�������������\n", who, target);
			who->start_busy(5);
			return 1;
		}
	}
	return 0;
}

*/

