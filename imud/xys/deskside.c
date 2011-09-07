// by firefox 11/21/2009
// ����ɱ-��Ϸ����

inherit ROOM;

#include "xys.h"
#include "cmds.c"

void create ()
{
	set("short", "���лþ�");
	set("long", "�����ξ��е�һ�����ⳡ�����·���������·�ϡ�\n");

	set("no_fight", 1);
	set("no_magic", 1);

	seteuid(getuid());

	setup();
}

void init()
{
	add_action("do_ready", ({"ready"}));
	add_action("do_leave", ({"leave"}));

//	add_action("do_kickout", "kickout");		//�߳�ĳ��
	add_action("do_start", "start");			//��Ҿ���������������
	
	add_action("do_top", "top");				//��������
	
	add_action("do_look", "look");				//���״̬
	add_action("do_hp", "hp");					//����״̬
	add_action("do_inventory", "inventory");	//��ʾ����	
	add_action("do_skills", "skills");			//������
	
	add_action("do_equip", "equip");			//װ��һ��װ��
	add_action("do_unequip", "unequip");		//ж��һ��װ��

	add_action("do_use", "use");				//����/ʹ����
	add_action("do_discard", "discard");		//����

	if(wizardp(_player))
		add_action("do_stat", "stat");			//�鿴��ݣ�ս��
}


mixed* _players = ({});

int _round = 0;
int _turn = -1;


//�볡ѡ����������
int do_ready(string arg)
{
	if(_round > 0) return notify_fail("�����Ѿ���ʼ�ˡ�\n");

}

//�볡ѡ���뿪
int do_leave(string arg)
{
	if(_round > 0) return notify_fail("���������У������뿪��\n");

}
