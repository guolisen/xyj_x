

inherit NPC;

#include <xyj_x.h>

void create()
{
	object ob;

	set_name("����Ա", ({ "npc", }));

	set("gender", "����" );

	set("long","

�������û����ݵ�NPC��Ҳ������ָ�

    literate �ȼ�                �趨literate���µȼ���ֻ����һ�Σ�
    exchange                     ��80K���һ�Ǳ��25KǱ��

");
	setup();
	
	carry_object("/obj/cloth");

}

void init()
{
	add_action ("do_literate", "literate");
	add_action ("do_exchange", "exchange");
}


int do_literate(string arg)
{
	return __DIR__"cvt"->set_literate(to_int(arg));
}


#define	NORM_RATIO			80

int do_exchange(string arg)
{
	mapping rewards = ([PEXP : 25000]);

	if(total_exp(_player) < 35*K) return notify_fail("�����ѧ����̫�ͣ�\n");

	if(TASK_EXC->do_reward(_player, name(), "�һ�", rewards, NORM_RATIO)) {
		_player->add(PEXP, rewards[PEXP]);
		tell_object(_player, "��һ���Ǳ�ܡ�\n");		
	}
	return 1;
}
