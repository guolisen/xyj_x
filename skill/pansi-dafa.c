// by firefox 03/16/2010

#define NAME		"��˿��"

inherit SKILL;

int valid_enable(string usage) { return usage=="spells"; }

int valid_learn(object me)
{
	if(me->query("family/family_name") != "��˿��") 
		return notify_fail(NAME"̫����£�����˿�����޷���⡣\n");
	
	if(me->query_skill("spells", 1) < 10)
		return notify_fail("��ķ�����Ϊ����������޷�ѧϰ"NAME"��\n");
	return 1;
}

string cast_spell_file(string spell)
{
	return CLASS_D("yaomo") + "/pansidong/pansi-dafa/" + spell;
}

string type() { return "magic";}

void random_level_up(object who)
{
	int lvl = who->query_skill("pansi-dafa", 1);
	//����ѧ֮�Ĳ�ר���޷�����������
	if(who->query("betray/count")) return;

	if(!random(lvl * 2)) who->improve_skill("pansi-dafa", 1);
}

