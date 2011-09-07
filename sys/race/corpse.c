
/*
他那脊梁上有一行字，叫做白骨夫人。
行者道：『他是个潜灵作怪的僵尸

潜灵僵尸

白骨精

百变尸魔


 /d/changan/fendui
 /obj/corpse


$n对$N说道：我是新来的，请多关照。请问您死几年了？


出现：地上突然伸出一直手，接着$N挣扎着爬出来。

驯服：$N含糊的说道：主人，我愿为您效劳，不要毁灭我。

int _index = 0;

mixed* _tab = ({
	({ "", "", "白骨洞主", }),
	({ HIW, NOR, "尸变白骨精", }),
});
//改变名字
private void change_name()
{
	string c1 = _tab[_index][0];
	string c2 = _tab[_index][1];
	set_name(c1 + "白晶晶" + c2, ({ "bai jingjing", "bai", "jingjing" }));
}

	if(at_night() && is_full_moon())

void init()
{	
	object me = this_object();
	object who = this_player();
	object weapon = who->query_temp("weapon");

	string time = CHINESE_D->chinese_date(time());
	_index = (NATURE_D->query_current_day_phase() >= 6)	//月圆之夜
		&& (strsrch(time, "二十五日") >= 0);
	change_name();

	if(_index) {
		if(weapon) weapon->unequip();
		message_vision("$N满头白发，眼似红灯，舞动白森森的利爪，扑向$n！\n", me, who);
		me->kill_ob(who);		
	} else {
		if(!weapon) command("wield all");
	}

	::init();

	add_action("do_kiss", "kiss");

}

int do_kiss(string arg)
{
	if(arg) {
		object target = present(arg, environment());
		if(target == this_object()) {
			object who = this_player();
			target->remove_all_killer();
			who->remove_all_killer();
			message_vision("$N慌忙吻住$n，阳气慢慢过给$n，红灯般的眼睛黯淡了下来。\n", who, target);
			who->start_busy(5);
			return 1;
		}
	}
	return 0;
}

*/

