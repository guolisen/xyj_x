// buy.c

inherit F_CLEAN_UP;

//����id�����Ѱ�һ���
object find_vender(object env, string id, string item)
{
	if(id) return present(id, env);
	foreach(object who in all_inventory(env)) {
		if(who->buy_object(0, item) > 0) return who;
	}
	return 0;
}

int main(object me, string arg)
{
	string item, vid;
	int n = 0;
	object vender;
	int price = 0, afford = 0;

	if(me->is_busy()) return notify_fail("��������æ���ء�\n");

	if(arg) {
		if(sscanf(arg, "%s from %s", item, vid) != 2) item = arg;
		if(sscanf(item, "%d %s", n, item) != 2) n = 1;
		vender = find_vender(environment(me), vid, item);
		if(!objectp(vender)) return notify_fail("��Ҫ��˭������\n");		
		price = vender->buy_object(me, item) * n;
	}
	
	if(price < 1) return notify_fail("ָ���ʽ: buy [����] <ĳ��> [from <ĳ��>]\n");

	if(afford = me->can_afford(price)) {
		if(afford == 2) return notify_fail("��û���㹻����Ǯ������Ʊ��û���ҵÿ���\n");

		if(vender->complete_trade(me, item, n)) {
			me->pay_money(price);
			return 1;
		}
	} 
	else return notify_fail("���Ǯ������\n");

	return 0;
}

int help(object me)
{
	write( @HELP
ָ���ʽ: buy [����] <ĳ��> [from <ĳ��>]

��һָ��������Դ�ĳЩ����������Ʒ��������������Ҳ��ʡ�Ի��̡�
HELP
	  );
	return 1;
}
