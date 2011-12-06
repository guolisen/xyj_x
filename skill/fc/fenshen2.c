// firefox 2011.12

inherit F_CLEAN_UP;

#include <xyj_x.h>

#define CD			30
#define DURATION	60

int cast(object me, object target)
{
	int dao = me->query_skill("dao", 1);
	int num = min2(3, dao / 50);
	int real = random(num + 1);
	int cost = 10 + dao * num / 2;
	
	if(num < 1) return  notify_ok("��ĵ����ɷ�̫�͡�\n");
	if(me->query("mana") < cost) return notify_ok("��ķ������㣡\n");
	if(!cd_start(me, "invoke", CD)) return notify_ok("��ոշֹ����ٷ����Σ�գ�\n");

	message_vision("$N���º�ë���ڿ��У����ȥ�������䣡����\n", me);

	me->add("mana", -cost);

	for(int i = 0; i < num + 1; ++i) {
		if(i == real) {
			me->move(environment(me), 1);
		} else {
			object guard = GUARD->clone_jiashen(me);
			mapping db = guard->query_entire_dbase();

			db["chat_chance_combat"] = 20;
			db["chat_msg_combat"] = ({
				(: call_other, guard, "perform_action", "stick", "qiankun" :),
			});
			db["cps"] = 1;								//�����޶���	
			db["combat_exp"] += 40000;					//��������
			
			GUARD->weaken(guard, num);

			SKI->set_level(guard, dao);
			guard->reset_action();
			guard->set_life(DURATION / num, "$N����һ�Σ�����һ����ë���Ʈ�䡣\n");
		}
	}
	return 1;
}
