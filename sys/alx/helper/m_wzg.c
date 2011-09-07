// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"m_base";

string* _poem = ({

"
    二八佳人体似酥，腰间仗剑斩凡夫。
    虽然不见人头落，暗里教君骨髓枯。
",
"
    踏歌，踏歌，蓝采和！
    世界转几何？
    红颜三春树，流年一掷梭。
    古人混混去不返，今人纷纷来更多。
    朝骑鸾凤到碧落，暮见桑田生白波。
    长景明晖在空际，金银宫阙高嵯峨。
",
"
    举世都为名利醉，伊予道向道中醒。
    他时定是飞升去，冲破秋空一点春。
",
"
    麻姑笑我恋尘嚣，一隔仙凡道路遥。
    飞去沧州弄明月，倒骑黄鹤听吹箫。 
",

});

mapping* _npc = ({
	([
		"name"		: "吕洞宾",
		"ids"		: ({"lu dongbin", "lu", "dongbin"}),
		"cloth"		: "/d/obj/cloth/xianpao",
		"weapon"	: "/d/obj/weapon/sword/changjian",

		"prop"		: ([
			"title"		: "纯阳子",
			"gender"	: "男性",
			"age"		: 35,
			"per"		: 30,
			"long"		: "吕洞宾大概是镇元门下最出名的弟子了，文采风流，色胆包天。\n",
		]),
	]),
	([
		"name"		: "蓝采和",
		"ids"		: ({"lan caihe", "lan", "caihe"}),
		"cloth"		: "/d/obj/cloth/linen",
		"weapon"	: "/d/obj/weapon/blade/yanblade",

		"prop"		: ([
			"gender"	: "男性",
			"age"		: 18,
			"per"		: 20,
			"long"		: "一位面腆和善的少年。\n",
		]),
	]),
	([	
		"name"		: "韩湘子",
		"ids"		: ({"han xiangzi", "han", "xiangzi"}),
		"cloth"		: "/d/obj/cloth/choupao",
		"weapon"	: "/d/obj/weapon/sword/zijinxiao",

		"prop"		: ([
			"gender"	: "男性",
			"age"		: 22,
			"per"		: 30,
			"long"		: "好一位俊雅潇洒的相公。韩湘子本是名门之后，却不喜念书入仕。\n被其族中长者以轻狂不学斥出家门。\n",
		]),
	]),
	([
		"name"		: "何仙姑",
		"ids"		: ({"he xiangu", "he", "xiangu"}),
		"cloth"		: "/d/obj/cloth/skirt",
		"weapon"	: "/d/obj/weapon/sword/heye",

		"prop"		: ([
			"gender"	: "女性",
			"age"		: 25,
			"per"		: 20,
			"long"		: "何仙姑深得镇元大仙喜爱，各位同门大多跟她交好。\n何仙姑原名何秀姑，父亲是开豆腐坊的，她投入五庄观前是当地有名的“豆腐西施”。\n",
		]),
	]),
});


void create()
{
	int i = random(sizeof(_npc));
	mapping m = _npc[i];

	set_name(m["name"], m["ids"]);
	foreach(string k, mixed v in m["prop"]) {
		_this->set(k, v);
	}
	

	create_family("五庄观", 3, "弟子");

	SKI->set_list2(_this, FAMILY->skills_of("五庄观"), 1);

	set_events(
		([
			"born"		: "\n天空中传来一个声音：\n"HIC + _poem[i] + NOR"\n$N驾着一朵祥云缓缓落下。",
			"leave"		: CYN"$N说道：观中有事，恕不奉陪。说罢驾云而去。",

			"cmds"		: ({ "cast zhenhuo", "cast zhenhuo", "cast qimen" }),
		])
	);

	setup();

	carry_object(m["cloth"])->wear();
	carry_object(m["weapon"])->wield();

}




/*
张果老

修成金骨炼归真，
洞锁遗踪不计春。
野草漫随青岭秀，
闲花长对白云新。
风摇翠蓧敲寒玉，
水激丹砂走素鳞。
自是神仙多变异，
肯教踪迹掩红尘。


钟离权

坐卧常携酒一壶，
不教双眼识皇都。
乾坤许大无名姓，
疏散人中一丈夫。

*/