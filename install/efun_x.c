// by firefox 11/21/2009

#include <ansi.h>


#define SEC_PER_HB				2		//ÿ��������


/********************************��ѧ����***********************************/

//�ϴ�ֵ
mixed max2(mixed a, mixed b) 
{
	return a >= b ? a : b;
}

//��Сֵ
mixed min2(mixed a, mixed b)
{
	return a <= b ? a : b;
}

//���ֵ
mixed max3(mixed a, mixed b, mixed c)
{
	return max2(max2(a, b), c);
}

//��Сֵ
mixed min3(mixed a, mixed b, mixed c)
{
	return min2(min2(a, b), c);
}

//���a�ǿ���a������b��
mixed or2(mixed a, mixed b)
{
	return a ? a : b;
}

//���a����a������b
mixed and2(mixed a, mixed b)
{
	return !a ? a : b;
}

//�����������ѡ��һ��Ԫ��
mixed random1(mixed* arr)
{
	return arr[random(sizeof(arr))];
}


/********************************�ַ�������***********************************/

//��������ָ���ַ�λ��
int rfind(string str, int ch)
{
	int i;
	for(i = sizeof(str) - 1; i >= 0; --i) {
		if(str[i] == ch) break;
	}
	return i;
}

//ȫ·���е��ļ���
string path_file(string path)
{
	int i = rfind(path, '/');
	return path[i+1..];
}

//ȫ·���е�·����
string path_dir(string path)
{
	int i = rfind(path, '/');
	return path[0..i-1];
}

/********************************������***********************************/

//�������󲢷�����Ŀ�껷����ʧ�������ٶ���
object new_to(string file, object env)
{
	object ob = new(file);

	if(!ob || !env) return 0;
	if(ob->is_character() && env->is_character()) env = environment(env);
	if(env && ob->move(env)) return ob;
	destruct(ob);
	return 0;
}

//�ж�id�Ƿ�Ϊָ������
int id_match_ob(string id, object ob)
{
	object ob1;

	if(!id || !ob) return 0;
	ob1 = present(id, environment(ob));

	return ob == ob1;
}

/********************************��Ϣ����***********************************/

//��ʾ��Ϣ��������1��ĳЩʱ�����ڴ���notify_fail
int notify_ok(string msg)
{
	write(msg);
	return 1;
}

//��wiz�����������
varargs int trace(string msg, object who)
{
	if(!who) who = this_player();
	if(who && wizardp(who)) {
		tell_object(who, HIW"TRACE:"HIY + msg + NOR"\n");
	}
	return 1;
}

//�滻�ַ����еĳ�ν����νϰ����Ϯmessage_vision����emote��ͬ
private string _vision_rep(string msg, object who, int low)
{
	object weapon = who->query_temp("weapon");
	mapping m = ([
		"$R"	: RANK_D->query_respect(who),		//����
		"$U"	: RANK_D->query_rude(who),			//���
		"$S"	: RANK_D->query_self(who),			//ǫ��
		"$A"	: RANK_D->query_self_rude(who),		//��ƣ�Arrogant
		"$W"	: weapon ? weapon->name() : "ȭͷ",	//����
	]);
	foreach(string k, string v in m) {
		if(low) k = lower_case(k);
		if(v) msg = replace_string(msg, k, v);
	}
	return msg;
}

//message_vision��ǿ��
varargs int msvx(string msg, object me, object you, mixed a1, mixed a2, mixed a3, mixed a4)
{
	if(!msg || !me) return 1;
	msg = sprintf(msg, a1, a2, a3, a4);
	if(me) msg = _vision_rep(msg, me, 0);
	if(you) msg = _vision_rep(msg, you, 1);
	message_vision(msg, me, you);
	return 1;
}

/********************************�������ߺ���***********************************/

//���ܿ�ʼ��ȴ�����أ�0-������������ȴ�ڣ���0-�����Ѿ���ȴ����ʼ�����µ���ȴ�ڡ�
int cd_start(object who, string prop, int duration)
{
	string str = "sys_cd/" + prop;
	int t = time();

	if(t < who->query(str)) return 0;
	return who->set(str, t + duration * SEC_PER_HB);
}

//�����Ƿ���ȴ����
int cd_end(object who, string prop)
{
	string str = "sys_cd/" + prop;
	return time() >= who->query(str);
}

//��鼼���Ƿ���ȴ��δ��ȴ�򷵻ش�����Ϣ
varargs int cd_check(object who, string prop, string fail_msg)
{
	if(cd_end(who, prop)) return 1;

	fail_msg = fail_msg ? fail_msg : "������ʱ����ʹ�á�\n";
	tell_object(who, fail_msg);
	return 0;
}

