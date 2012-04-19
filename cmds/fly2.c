// firefox 02/21/2010

#include <xyj_x.h>
#include <ansi.h>

#define FLY_FAIL	message_vision(HIY"$N��������һ�����ƺ���������������ز������߾�һ�����Դ�ˤ��������\n"NOR, me)

mapping _maps = ([
	"stone"			: "/d/dntg/hgs/entrance",
	"kaifeng"		: "/d/kaifeng/tieta",
	"moon"			: "/d/moon/ontop2",
	"lingtai"		: "/d/lingtai/gate",
	"putuo"			: "/d/nanhai/gate",
	"changan"		: "/d/city/center",
	"sky"			: "/d/dntg/sky/nantian",
	"wuzhuang"		: "/d/qujing/wuzhuang/gate",
	"meishan"		: "/d/meishan/erlangwai",

	"penglai"		: ({ "/d/penglai/penglai", "eastsea map" }),
	"xueshan"		: ({ "/d/xueshan/binggu", "xueshan map" }),

	"baoxiang"		: ({ "/d/qujing/baoxiang/bei1.c", 4 }),
	"pingding"		: ({ "/d/qujing/pingding/ping1.c", 4 }),
	"yalong"		: ({ "/d/qujing/pingding/yalong1.c", 3 }),
	"wuji"			: "/d/qujing/wuji/square.c",
	"chechi"		: ({ "/d/qujing/chechi/jieshi1.c", 9 }),
	"tongtian"		: ({ "/d/qujing/tongtian/hedong1.c", 6 }),
	"jindou"		: ({ "/d/qujing/jindou/jindou1.c", 4 }),
	"nuerguo"		: ({ "/d/qujing/nuerguo/towna1.c", 3 }),
	"dudi"			: ({ "/d/qujing/dudi/dudi1.c", 4 }),
	"firemount"		: ({ "/d/qujing/firemount/cuiyun1.c", 5 }),
	"huangfeng"		: "/d/qujing/huangfeng/huangfeng.c",
	"huoyun"		: "/d/qujing/kusong/kusongjian.c",
	"jilei"			: ({ "/d/qujing/jilei/jilei1.c", 3 }),
	"jisaiguo"		: ({ "/d/qujing/jisaiguo/east1.c", 4 }),
	"jingjiling"	: "/d/qujing/jingjiling/jingji1.c",
	"xiaoxitian"	: "/d/qujing/xiaoxitian/simen.c",
	"zhuzi"			: ({ "/d/qujing/zhuzi/zhuzi1.c", 5 }),
	"qilin"			: "/d/qujing/qilin/yutai.c",
	"pansi"			: ({ "/d/qujing/pansi/ling1.c", 6 }),
	"biqiu"			: ({ "/d/qujing/biqiu/jie1.c", 9 }),
	"qinghua"		: "/d/qujing/biqiu/zhuang.c",
	"wudidong"		: ({ "/d/qujing/wudidong/firemount-wudidong1.c", 3 }),
	"qinfa"			: ({ "/d/qujing/qinfa/jiedao1.c", 8 }),
	"yinwu"			: "/d/qujing/yinwu/huangye1.c",
	"fengxian"		: ({ "/d/qujing/fengxian/jiedao1.c", 9 }),
	"yuhua"			: ({ "/d/qujing/yuhua/xiaojie1.c", 9 }),
	"baotou"		: ({ "/d/qujing/baotou/shanlu1.c", 9 }),
	"zhujie"		: ({ "/d/qujing/zhujie/shanlu11.c", 8 }),
	"jinping"		: ({ "/d/qujing/jinping/xiaojie1.c", 7 }),
	"qinglong"		: "/d/qujing/qinglong/shanjian.c",
	"tianzhu"		: ({ "/d/qujing/tianzhu/jiedao11.c", 8 }),
	"maoying"		: ({ "/d/qujing/maoying/shanpo1.c", 9 }),
	"lingshan"		: ({ "/d/qujing/lingshan/dalu1.c", 3 }),

	"gaolao"		: "/d/gao/gate",
	"jiangzhou"		: "/d/jz/center",
	"bibotan"		: "/d/qujing/bibotan/gudu",
	"emei"			: "/d/southern/emei/shanlu4",
	"bang"			: (: call_other, GANG, "home" :),
	"gang"			: (: call_other, GANG, "home" :),
]);

int MIN_DX = RANK_D->grade_dx(BLU "�������" NOR);
int MIN_MANA = RANK_D->grade_fali(HIB "���Ƽ���" NOR);

int main(object me, string arg)
{
	mixed dst;
	string loc;
	int mana_cost = -(100 - me->query_skill("spells")) / 4 - 40;
	object ridee = me->ride();
	string ridemsg = "";

	seteuid(getuid());

	if(!arg)
		return notify_fail("��Ҫ�ɵ�����ȥ��\n");
	if(me->is_fighting())
		return notify_fail("������ս�����ɲ�����\n");
	if(me->is_busy() || me->query_temp("pending/exercising"))
		return notify_fail("����æ���أ�û�������Ƽ���\n");
	if(!wizardp(me) && !environment(me)->query("outdoors") )
		return notify_fail("��Χû��һƬ�ƣ�û�취���Ƽ���\n");
	if(me->is_ghost())
		return notify_fail("���˹��ˣ�����ʵ��ɣ�\n");
	if(me->query_temp("no_move"))
		return notify_fail("�㱻��ס�ˣ�����ɵ�������\n");

	if(RANK_D->grade_dx( RANK_D->describe_dx( me->query("daoxing"))) < MIN_DX ) {
		FLY_FAIL;
		return notify_fail("�����ڻ����������̸���ϣ�����ɵ�������\n");
	}
	if(RANK_D->grade_fali( RANK_D->describe_fali( me->query("max_mana"))) < MIN_MANA ) {
		FLY_FAIL;
		return notify_fail("��������ķ�����Ϊ���������Ƽ���\n");
	}
	if(me->query("mana") < 200) {
		FLY_FAIL;
		return notify_fail("��Ŀǰ����������ӯ��\n");
	}
	if(me->query("sen") * 100 / me->query("max_sen") < 50)
		return notify_fail("������ͷ�Բ�̫���ѣ����ĵ�����ˤ����\n");
	if(me->query("kee") * 100 / me->query("max_kee") < 50)
		return notify_fail("��������������������ƺ��е㲻֧��\n");

	message_vision(HIY"$N��һָ������һ���Ʋʣ��߸����˵�������ȥ��\n"
		+ "�ٴ�һ�����ڣ���֮����ȽȽ�����𡣡���\n\n"NOR, me);

	if(mana_cost > 0) mana_cost = 0;
	me->add("mana", mana_cost);

	dst = _maps[arg];
	if(!dst) {
		write("\n\n���ˣ��㰴����ͷ����������\n");
		write("�ף���������ô����ԭ���ĵط���\n");
		return 1;
	}
	if(stringp(dst)) loc = dst;								//�̶����
	else if(functionp(dst)) loc = evaluate(dst, me);		//�������
	else {		
		loc = dst[0];
		if(intp(dst[1])) {									//������
			loc[strlen(loc) - 3] += random(dst[1]);
		}
	}
	if(ridee) {
		ridemsg = ridee->ridee_msg(1);
		ridee->move(loc);
	} 
	me->move(loc);

	write("\n\n���ˣ��㰴����ͷ����������\n");
	message_vision(HIY"\nֻ������н���һ���Ʋʣ�$N" + ridemsg + "���������˳�����\n" NOR, me);

	return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : fly|fei [Ŀ�ĵ�]

����ĵ��кͷ�����ǿʱ����������Ƽ���

Ŀǰ����Էɵ��ĵط���
changan         ->������                 kaifeng        ->�����
stone           ->����ɽ��ʯ             sky            ->������
moon            ->����ɽ�¹�             penglai        ->�����ɵ�
lingtai         ->��̨����ɽ             putuo          ->�Ϻ�����ɽ
xueshan         ->��ѩɽ������           meishan        ->÷ɽ�཭��
wuzhuang        ->����ɽ��ׯ��

baoxiang        ->�����                 pingding      ->ƽ��ɽ
yalong          ->ѹ��ɽ                 wuji          ->�ڼ���
chechi          ->���ٹ�                 tongtian      ->ͨ���
jindou          ->��ɽ                 nuerguo       ->Ů����
dudi            ->����ɽ                 firemount     ->����ɽ
jilei           ->����ɽ                 jisaiguo      ->������
jingjiling      ->������                 xiaoxitian    ->С����
zhuzi           ->���Ϲ�                 qilin         ->����ɽ
pansi           ->��˿��                 biqiu         ->����� 
qinghua         ->�廪ׯ                 wudidong      ->�޵׶�
qinfa           ->�շ���                 fengxian      ->���ɿ� 
yinwu           ->����ɽ                 yuhua         ->���� 
baotou          ->��ͷɽ                 zhujie        ->���ɽ
jinping         ->��ƽ��                 qinglong      ->����ɽ 
tianzhu         ->���ù�                 maoying       ->ëӱɽ 
lingshan        ->��ɽ                   

gaolao          ->����ׯ                 jiangzhou     ->���ݳ� 
bibotan         ->�̲�̶                 emei          ->��üɽ

bang|gang       ->����פ��

HELP
        );
        return 1;
}

