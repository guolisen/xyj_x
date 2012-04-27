
#include <skill.h>

//���κ��鶼�ᣬ���Ӷ���ʶ�֣�����Ҳ��������ѧ

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object env = environment(me);
	object book;
	mapping prop;
	int cost, skill, exp;

	if(env->query("no_fight") || env->query("no_magic") )
		return notify_fail("���ﲻ�Ƕ���ĵط���\n");
	if(me->is_fighting() || me->is_busy())
		return notify_fail("��������æ���ء�\n");
	if(!arg || !objectp(book = present(arg, me)))
		return notify_fail("��Ҫ��ʲô��\n");
	if(!mapp(prop = book->query("skill")))
		return notify_fail("���޷�����������ѧ���κζ�����\n");
	if(!me->query_skill("literate", 1))
		return notify_fail("���Ǹ���ä����ѧѧ����ʶ��(literate)�ɡ�\n");

	message_vision("$N��ר�ĵ��ж�$n", me, book);

	skill = me->query_skill(prop["name"], 1);
	
	exp = skill * skill /10 * skill;
	if(SKILL_D(prop["name"])->type() == "martial") {
		if(exp > me->query("combat_exp")) {
			write("�����ѧ��Ϊ��û��������磬�����û�õġ�\n");
			return 1;
		}
	}
	else if(SKILL_D(prop["name"])->type()=="magic" ) {
		if(exp > me->query("daoxing")) {
			write("��ĵ��л�û��������磬�����û�õġ�\n");
			return 1;
		}
	}
	
	if(!SKILL_D(prop["name"])->valid_learn(me))
		return notify_fail("����Ŀǰ����������û�а취ѧ������ܡ�\n");;

	cost = prop["sen_cost"] + prop["sen_cost"] * (prop["difficulty"] - me->query_int()) / 20;

	if (cost < 5) cost = 5;
	cost *= 2;                                                                      //firefox 2011.10

	if(me->query("sen") < cost) {
		write("�����ڹ���ƣ�룬�޷�ר�������ж���֪��\n");
		return 1;
	}
	if(me->query_skill(prop["name"], 1) > prop["max_skill"]) {
		write("���ж���һ��������Ƿ���������˵�Ķ�����Զ�̫ǳ�ˣ�û��ѧ���κζ�����\n");
		return 1;
	}

	me->receive_damage("sen", cost);

	if(!me->query_skill(prop["name"], 1)) me->set_skill(prop["name"], 0);
	me->improve_skill(prop["name"], me->query_skill("literate", 1) * 2 + 1);           //firefox 2011.10
	write("���ж��й�" + to_chinese(prop["name"]) + "�ļ��ɣ��ƺ��е��ĵá�\n");
	return 1;
}

int help(object me)
{
	write( @HELP
ָ���ʽ: study|du <��Ʒ����>

���ָ��ʹ����Դ����Ż�������Ʒ��ѧĳЩ����,
��ǰ����: �㲻���Ǹ�����ä����

see also : learn
HELP
	);
	return 1;
}


