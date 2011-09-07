
/*

/d/qujing/pansi/zhuogou	girl7

$N轻轻的


, "name" : 

蜘蛛			结网，被动粘敌人，尤其是攻击者
				$N瞬间织就了一张大网，蹲在网中央，静待别人自投罗网。
				一阵风吹来，蜘蛛网随风飘散了。
*/


string _long = @LONG

一只巨大的蜘蛛，通体黑色。腹部有红色的沙漏状图案。一旦你
得到她的深情拥抱，你的生命将只剩一炷香的时间。

LONG;

mapping _prop = ([
	"黑寡妇"	: ([
		"ids"		: ({"hei guafu", "guafu", "spider"}),
	])
]);



int do_act(object me, object target)
{
	object hook = new(CMD_HOOK);
	hook->set_listener(_this, "perform")
	stone->set("host", me);


	msv("$N瞬间织就了一张大网，蹲在网中央，静待别人自投罗网。", me);

	
}

