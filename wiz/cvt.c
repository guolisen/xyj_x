
// by firefox 11/21/2009
// ������ת����

void create()
{
	seteuid(getuid());
	set_heart_beat(1);
}


//���������գ����ң�������



#define LIT			"gift/literate"
//����literate������Ǳ��
int set_literate(int lvl)
{
	object who = this_player();

	int literate = who->query_skill("literate", 1);
	int pot = 0;

	if(who->query(LIT)) 
		return notify_fail("���Ѿ������literate�ˡ�\n");

	if(lvl >= literate)
		return notify_fail("���趨�����ڵ͵�literate����\n");

	if(lvl < 20)
		return notify_fail("���趨�ȸ���20��literate����\n");

	for(int i = lvl; i < literate; ++i) {
		int intelligence = who->query("int") + (i - 20) / 10;
		pot += (i + 1) * (i + 1) / intelligence * 2;
	}
	
	who->set(LIT, 1);
	who->add("learned_points", -pot);
	who->set_skill("literate", lvl);

	return notify_ok("��õ���" + pot + "��Ǳ�ܡ�\n");

}

