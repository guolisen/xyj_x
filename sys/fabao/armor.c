// by firefox 11/21/2009
// ������������

#include <armor.h>
#include <ansi.h>
inherit ARMOR;

//���ף���ף�ħ�ף�ƫ��ħ��

/*

������
ͷ�ϴ�һ��ˮĥ����������
���Ϲ�һ���޴�����ƽ��
����̤һ˫���۵���Ƥѥ
������һ����˿����ʨ����

���㾫

ͷ��������һԣ�	�λԽ��
������׳����ޡ�	���޽��
��Χ��������䣬	�����
��̤�̻�ѥ���档	�̻�ѥ


����

���ۻƽ�ϸ��
������
��Ƥѥ


�������ɣ�

ͷ���ǹڷɲ��ޣ������Ʒ��º졣
������Ь�ѽ��壬���䱦�������硣
һ˫�ɽ��貨�࣬��¶ȹ�[�����ޡ�
����������ӣ�����˳���������
*/

void create()
{
	set_name(HIY"���ۻƽ�ϸ��"NOR, ({ "dragon armor", "armor"}));
	set_weight(1);

	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "һ����ӲӵĿ��ף�\n");

		set("material", "iron");
		set("armor_prop/armor", 1);
		set("armor_prop/dodge", 1);

		//set("no_get", 1);
	}
	setup();
}

