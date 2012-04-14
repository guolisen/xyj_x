

int _dose = 0;

int set_dose(int dose) { _dose = dose; }
int query_dose() { return _dose; }


mixed hit_ob(object me, object victim, int damage_bonus)
{
	int diff;

	if(damage_bonus < 0) return 0;
	diff = random((int)me->query("force_factor")+1) - random((int)victim->query("force_factor")/2+1);
	//here we let force_factor determine who hurts who:)
	//the attacker has more chance of course.

	if(diff > 0)
	{
		victim->apply_condition("double_ice_poison", diff + (int)victim->query_condition("double_ice_poison") );
		message_vision("$N����һ�������˵��ϵĺ�����\n", victim);
	}
	else if(diff < -3)
	{//for very weak ppl or npc, also possible to "force back", this
	 //is to ensure it'll not happen.
		me->apply_condition("double_ice_poison", -diff + me->query_condition("double_ice_poison") );
		message_vision("$N����һ����ԭ���ǵ��Ϻ�����$n���˻��������˲��ɷ�������\n", me, victim);
	}
	else 
		message_vision("$N����һ����Ϯ����������˵��ϵĺ�����\n", victim);
}
