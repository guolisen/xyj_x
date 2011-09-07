// by firefox 02/21/2010

#include <weapon.h>
#include <ansi.h>
#include <xyj_x.h>

inherit F_LOADABLE;
inherit DAGGER;

string help_msg = @LONG

һ����¼��¼�����μ��廪վ�ٿ�֪ʶ���鼮�����������������ȡ
���߼�¼�����ĵ���ע��ؼ����б��еĹؼ���Ҫ�ÿո�ָ�����

    wiki key_words         ���ݹؼ����б�����������Ϣ
    faq_add                ����һ��faq
    faq_lower              �г�����faq���༭ר��
    faq_del                ɾ��һ��faq���༭ר��
    faq_certify            ȷ��һ��faq���༭ר��

    doc_update             �����ĵ����ݿ⣬wizר��

LONG;

void create()
{
	set_name(HIG"���ΰٿ�"NOR, ({ "xyj wiki", "wiki" }) );
	set_weight(10);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", help_msg);
		set("weapon_prop/spells", 20);
		set("wield_msg", "$N�ӻ�������һ��$n�������С�\n");
		set("unwield_msg", "$N�����е�$n���뻳�С�\n");
		set("changed", 1);

	}
	init_dagger(1);
	setup();
}

void doc_add_actions();

void init()
{
	doc_add_actions();
}

/*****************************��������*****************************/
#define MAX_ITEM	15

void doc_add_actions()
{
	object who = this_player();

	add_action("faq_add", "faq_add");

	if(who->query("doc_editor")) {
		add_action("faq_del", "faq_del");
		add_action("faq_lower", "faq_lower");
		add_action("faq_certify", "faq_certify");
	}	

	if(wizardp(who)) {
		add_action("doc_update", "doc_update");
	}
}

//����faq
int faq_add(string arg)
{
	if(arg) {
		FAQ_D->add(arg);
		write("OK.\n");
		return 1;
	}
	return notify_fail("ָ���ʽ��faq_add ���� ��\n");
}

//ȷ��faq
int faq_certify(string arg)
{
	if(arg && FAQ_D->certify(arg, 100)) {
		write("OK.\n");
		return 1;
	}

	return notify_fail("ָ���ʽ��faq_add ���� ��\n");
}

//����faq
int faq_del(string arg)
{
	int n = to_int(arg);
	if(n > 0) {
		FAQ_D->delete(n);
		write("OK.\n");
		return 1;
	}
	return notify_fail("ָ���ʽ��faq_del ���\n");
}

//�г���λ��͵�faq
int faq_lower(string arg)
{
	int n = to_int(arg);	
	if(n > 1) {
		mapping rs = FAQ_D->lower(n, MAX_ITEM);
		printf("FAQ Ȩ�ص���%d����Ŀ��\n", n);
		FAQ_D->list(rs);	
	}
	return 1;
}

//�����ĵ����ݿ�
int doc_update()
{
	return DOC_D->update();
}
