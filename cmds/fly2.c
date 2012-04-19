// firefox 02/21/2010

#include <xyj_x.h>
#include <ansi.h>

#define FLY_FAIL	message_vision(HIY"$N奋力望上一跳，似乎想飞起来。结果离地不到三尺就一个倒栽葱摔了下来。\n"NOR, me)

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

int MIN_DX = RANK_D->grade_dx(BLU "初领妙道" NOR);
int MIN_MANA = RANK_D->grade_fali(HIB "腾云驾雾" NOR);

int main(object me, string arg)
{
	mixed dst;
	string loc;
	int mana_cost = -(100 - me->query_skill("spells")) / 4 - 40;
	object ridee = me->ride();
	string ridemsg = "";

	seteuid(getuid());

	if(!arg)
		return notify_fail("你要飞到哪里去？\n");
	if(me->is_fighting())
		return notify_fail("你正在战斗，飞不开。\n");
	if(me->is_busy() || me->query_temp("pending/exercising"))
		return notify_fail("你正忙着呢，没工夫腾云驾雾。\n");
	if(!wizardp(me) && !environment(me)->query("outdoors") )
		return notify_fail("周围没有一片云，没办法腾云驾雾。\n");
	if(me->is_ghost())
		return notify_fail("做了鬼了，就老实点吧！\n");
	if(me->query_temp("no_move"))
		return notify_fail("你被定住了，哪里飞得起来！\n");

	if(RANK_D->grade_dx( RANK_D->describe_dx( me->query("daoxing"))) < MIN_DX ) {
		FLY_FAIL;
		return notify_fail("你现在还初领妙道都谈不上，哪里飞得起来。\n");
	}
	if(RANK_D->grade_fali( RANK_D->describe_fali( me->query("max_mana"))) < MIN_MANA ) {
		FLY_FAIL;
		return notify_fail("看来以你的法力修为还不能腾云驾雾。\n");
	}
	if(me->query("mana") < 200) {
		FLY_FAIL;
		return notify_fail("你目前法力不够充盈。\n");
	}
	if(me->query("sen") * 100 / me->query("max_sen") < 50)
		return notify_fail("你现在头脑不太清醒，当心掉下来摔死。\n");
	if(me->query("kee") * 100 / me->query("max_kee") < 50)
		return notify_fail("你想飞起来，可是体力似乎有点不支。\n");

	message_vision(HIY"$N手一指，召来一朵云彩，高高兴兴地坐了上去，\n"
		+ "再吹一声口哨，随之往上冉冉地升起。。。\n\n"NOR, me);

	if(mana_cost > 0) mana_cost = 0;
	me->add("mana", mana_cost);

	dst = _maps[arg];
	if(!dst) {
		write("\n\n到了！你按下云头跳了下来。\n");
		write("咦？．．．怎么还在原来的地方？\n");
		return 1;
	}
	if(stringp(dst)) loc = dst;								//固定落点
	else if(functionp(dst)) loc = evaluate(dst, me);		//个人落点
	else {		
		loc = dst[0];
		if(intp(dst[1])) {									//随机落点
			loc[strlen(loc) - 3] += random(dst[1]);
		}
	}
	if(ridee) {
		ridemsg = ridee->ridee_msg(1);
		ridee->move(loc);
	} 
	me->move(loc);

	write("\n\n到了！你按下云头跳了下来。\n");
	message_vision(HIY"\n只见半空中降下一朵云彩，$N" + ridemsg + "从里面走了出来。\n" NOR, me);

	return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : fly|fei [目的地]

当你的道行和法力高强时，你可以腾云驾雾。

目前你可以飞到的地方：
changan         ->长安城                 kaifeng        ->开封城
stone           ->花果山仙石             sky            ->南天门
moon            ->昆仑山月宫             penglai        ->蓬莱仙岛
lingtai         ->灵台方寸山             putuo          ->南海普陀山
xueshan         ->大雪山寒冰谷           meishan        ->梅山灌江口
wuzhuang        ->万寿山五庄观

baoxiang        ->宝象国                 pingding      ->平顶山
yalong          ->压龙山                 wuji          ->乌鸡国
chechi          ->车迟国                 tongtian      ->通天河
jindou          ->金兜山                 nuerguo       ->女儿国
dudi            ->毒敌山                 firemount     ->火焰山
jilei           ->积雷山                 jisaiguo      ->祭赛国
jingjiling      ->荆棘岭                 xiaoxitian    ->小西天
zhuzi           ->朱紫国                 qilin         ->麒麟山
pansi           ->盘丝岭                 biqiu         ->比丘国 
qinghua         ->清华庄                 wudidong      ->无底洞
qinfa           ->钦法国                 fengxian      ->凤仙郡 
yinwu           ->隐雾山                 yuhua         ->玉华县 
baotou          ->豹头山                 zhujie        ->竹节山
jinping         ->金平府                 qinglong      ->青龙山 
tianzhu         ->天竺国                 maoying       ->毛颖山 
lingshan        ->灵山                   

gaolao          ->高老庄                 jiangzhou     ->江州城 
bibotan         ->碧波潭                 emei          ->峨眉山

bang|gang       ->帮派驻地

HELP
        );
        return 1;
}

