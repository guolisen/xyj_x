
#include <ansi.h>

string* _msg = ({
	"����¶������΢Ц��",
	"������һ�������ֻ���Ц��",
	"����¶����թ�����飬������뵽��ʲô�������ˡ�",
	"���ڱ��Ÿ�����ᡣ",
	"���Ŷ���Ц��ǰ����ϡ�",
	"üͷ��������֪����ʲô���¡�",
	"����������������˼״��",
	"ҧ���гݣ�һ���߷߲�ƽ�����ӡ�",
	"һ������ã����֪����Χ������ʲô�¡�",
	"����������ɵ�֡�",
	"��������״��",
	"�������Ʋ��֡�",
	"�����ذ���ͷ��������м�����顣",
	"ʹ����������죬�������ʹ��������",
	"��ǿ�ջ�Ц�������β�ס����İ��ˡ�",
	"����ü��ɫ�衣",
	"һ���������ࡣ",
	"����¶�����õ�Ц�ݡ�",
	"Ц�ñȿ޻��ѿ���",
	"��ǿ���Ų����Լ��޳�����",
	"������˿��",
	"����С������״��",
	"������Ц��¶������Ľ�����",
});

int main(object me, string arg)
{
	object who = arg ? present(arg, environment(me)) : 0;

	if(!who || !living(who) || who == me)
		return notify_fail("����鿴˭��\n");
	else {
		string msg = _msg[random(sizeof(_msg))];
		int spell1 = me->query_skill("spells");
		int spell2 = who->query_skill("spells");	
		string str;

		if(me->is_busy())
			notify_fail("����æ�š�\n");
		if(me->query("mana") < spell1)
			return notify_fail("��ķ������㡣\n");

		me->add("mana", -spell1);
		me->start_busy(2);

		if (random(spell1) > spell2 && who->name() != who->query("name")) 
			str = "ȴ��" + who->query("name");
		else
			str = "ֻ��" + who->name();

		tell_object(who, "��һ̧ͷ������" + me->name() + "����һ��������Ŀ������Ͷ����\n");
		write("��΢һ������" + who->name() + "ϸϸ������ȥ��" + str + msg + "\n\n");
	}
	return 1;
}

int help(object me)
{
      write(@HELP

ָ���ʽ �� observe <����> ��
	    observe <����> [ 2 | 3 | ...] ���ж��ͬ������ʱ��

���ָ���������÷������۲�����������ķ�����ǿ����
����ʶ�Ʊ��˵ı�������

�������ָ� bian
HELP
     );
     return 1;
}


