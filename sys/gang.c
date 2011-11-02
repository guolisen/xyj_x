// by firefox 02/21/2010
// ��Ἧ��

#include <xyj_x.h>
#include <ansi.h>

string* _elems = ({
	"ftb", "shenzhou", "taishan", "buduo", "lushan", "szcg", "cangyue",
	"dongxing", "xiaoyao"
});

void create()
{
	seteuid(getuid());
}

/********************************Ŀ������Ϣ��ѯ***********************************/

//��ȡĿ��İ����Ϣ
mapping data(object who)
{
	return who->query(GANG_PROP);
}

//��ȡĿ��İ��ID
string id(object who)
{
	return who->query(GANG_PROP"/id");
}

//���Ұ�����
object find(string gid)
{
	object g;
	if(member_array(gid, _elems) < 0) return 0;
	return load_object(GANG_DIR + gid);
}

//��ȡȫ��������
object* elems()
{
	object* arr = allocate(sizeof(_elems));
	for(int i = 0; i < sizeof(_elems); ++i) {
		arr[i] = find(_elems[i]);
	}
	return arr;
}

//��ȡĿ��İ�����
object of(object who)
{
	return find(id(who));
}

//��ȡĿ��İ������
string name(object who)
{
	return who->query(GANG_PROP"/name");
}

//�ж��Ƿ�ͬһ��ᣬ�ް������һ�����
int same(object ob1, object ob2)
{
	return ob1 && ob2 && id(ob1) == id(ob2);
}

/********************************���ӿ�***********************************/

//�г����а��
int list()
{
	printf(LINE1);
	printf("���              λ��        ����        ��ּ\n");
	printf(LINE1);
	foreach(string g in elems()) {
		printf("%s%-18s%-12s%-12s%-20s\n"NOR,
			g->query("color"),
			name_id(g),
			g->query("location"),
			g->query("from"),
			g->query("slogan"),
		);
	}
	printf(LINE1);
	return 1;
}

//���Դӵ�ǰλ�ý�������
int try_enter(object who, string verb)
{
	foreach(object g in elems()) {
		if(g->enter(who, verb)) return 1;
	}
	return 0;
}

//���ذ���ϳ�
int home(object me)
{
	mapping g = data(me);

	trace(getuid(me));

	if(!g
		|| me->is_fighting()
		|| me->is_busy()
		|| me->query_temp("pending/exercising")
		|| !(wizardp(me) || environment(me)->query("outdoors"))
		|| me->is_ghost()
		|| me->query_temp("no_move")
		|| me->query("daoxing") < 16000
		|| me->query("max_mana") < 360
		|| me->query("mana") < 200)
	{
		return 0;
	} else {
		string yard = GANG_DIR + g["id"] + "/yard";
		string ridemsg = "";
		object ridee = me->ride();

		if (ridee) {
			ridemsg = ridee->query("ride/msg")+"��"+ridee->name();
			ridee->move(yard);
		}
		message_vision(HIY"$N��һָ������һ���Ʋʣ��߸����˵�������ȥ��\n"
			"�ٴ�һ�����ڣ���֮����ȽȽ�����𡣡���\n\n"NOR, me);
		me->add("mana", -20);
		me->move(yard);
		write("\n\n���ˣ��㰴����ͷ����������\n");
		message_vision(HIY"\nֻ������н���һ���Ʋʣ�$N" + ridemsg + "���������˳�����\n"NOR, me);
	}
	return 1;

}
