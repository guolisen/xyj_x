
#include <ansi.h>
#include <mudlib.h>

inherit F_CLEAN_UP;

int summary();
int wiz();
int family(string name, object who);

mapping _funs = ([
	0		: (: summary :),
	"-w"	: (: wiz :),
]);

void create()
{ 
	seteuid(getuid()); 
	foreach(string id in FAMILY->ids()) {
		_funs[id] = (: family :);
	}
}

mixed main(object me, string arg)
{
	function fun = _funs(arg);

	if(fun) return evaluate(fun, me);

	if(arg[0] >= 'a' && arg[0] <= 'z') return match_id(me, arg);

	return match_name(me, arg);
}

int list();

void print(object ob);

int summary()
{
	int i = 0;
	mapping families = ([]);
	foreach(object ob in children(USER_OB)) {
		if(!userp(ob) || wizardp(ob) && !ob->query("env/invisibility")) continue;
		families[ob->query("family/family_name")]++;
	}

	foreach(string family in 

}
int wiz();
int family(string name, object who);



	if(opt_banghui)
		ob = filter_array(ob, (: $1->query("banghui") ==      $2->query("banghui") :), me);
	else if (opt_party)
		ob = filter_array(ob, (: $1->query("family/family_name") ==      $2->query("family/family_name") :), me);


		printf("共有"HIG"%s"NOR"玩家连线中，系统负担：%s。\n\n", player_cnt, query_load_average());

	string name, str, *option, bigname;
	object *list, *ob, ob1;
	int i, ppl_cnt,player_cnt;
	int opt_long, opt_wiz, opt_party,opt_male,opt_female,opt_normal,opt_number,opt_pkgroup;
	int opt_dead,opt_banghui;

	if(remote && sizeof(arg)<2) arg="";
	if( arg )
	{
		option = explode(arg, " ");
		i = sizeof(option);
		while( i-- )
			switch(option[i])
		{
			case "-h": return help();
			case "-l": opt_long = 1;break;
			case "-w": opt_wiz = 1;break;
			case "-b": opt_banghui = 1;break;
			case "-k": opt_pkgroup = 1;break;
			case "-p": opt_party = 1;break;
			case "-f": opt_female = 1;break;
			case "-m": opt_male = 1;break;
			case "-n": opt_normal = 1;break;
			case "-a": opt_number = 1;break;
			case "-d": opt_dead = 1;break;
			default:
				if(option[i][0]=='@' )
				{
					RWHO_Q->send_rwho_q(option[i][1..sizeof(option[i])],me, opt_long);
					write("网路讯息已送出，请稍候。\n");
					return 1;
				}
				ob1 = present(option[i], environment(me));
				if (!ob1) ob1 = find_player(option[i]);
				if (!ob1) ob1 = find_living(option[i]);
				if ((!ob1) && (option[i] =="me")) ob1=me;
				if (!ob1) return notify_fail("没有这个玩家或参数错误。\n指令格式 : who [-h] [-l] [-k] [-w] [-b] [-p] [-f] [-m] [-a] [-d][<ID>]\n");
				me = ob1; opt_party = 1;
		}
	}
	if(me) if(objectp(me)) if( !wizardp(me))
	{
		if(time()-me->query_temp("who_time") < 10 ) 
			return notify_fail("系统忙， 请稍候再尝试。\n");
		else if(opt_long && (int)me->query("force") < 5 ) {
			return notify_fail("你的精神太差了，没有办法得知其他玩家的详细资料。\n");
			me->receive_damage("force", 5);}

	}
	if(remote) {
		opt_long=0; // disable -l for remote because too long.
#ifdef INTERMUD_NAME
		str  = "■ " + INTERMUD_NAME + "";
#else
		str = "■ " + MUD_NAME + "";
#endif
	} else {
		str = "■ " + MUD_NAME + "";
	}
	if(opt_banghui)
		if(me->query("banghui"))
			str += me->query("banghui")+"的玩家有：";
		else
			return notify_fail("你目前还没有加入任何帮会。\n");
	if(opt_pkgroup)
		if(me->query_temp("pkgroup/sure"))
			str += "参加PK活动的玩家有：";
		else
			return notify_fail("你目前还没有参加PK活动。\n");
	else if(opt_party)
		if(me->query("family/family_name"))
			str += me->query("family/family_name")+"的玩家有：";
		else str += "普通百姓有：";
	else if(opt_male)
		str += "男性玩家有：";
	else if(opt_female)
		str += "女性玩家有：";
	else if(opt_normal)
		str += "太监有：";
	else if(opt_wiz)
		str += "巫师有：";
	else if(opt_long) str += "玩家有：";

	else str += "总人物有：";

	str += "\n═════════════════════════════════════════════\n";
	ob = filter_array(children(USER_OB),(: userp :));
	if(opt_banghui)
		ob = filter_array(ob, (: $1->query("banghui") ==      $2->query("banghui") :), me);
	else if (opt_party)
		ob = filter_array(ob, (: $1->query("family/family_name") ==      $2->query("family/family_name") :), me);
	list = sort_array(ob,"sort_user");
	ppl_cnt = 0;
	if(opt_long || opt_wiz)
	{
		i = sizeof(list);
		while ( i-- )
		{
			// Skip those users in login limbo.
			if( !environment(list[i])) continue;
			if( !wizardp(me) && !me->visible(list[i]) ) continue;
			if( opt_wiz && !wizardp(list[i]) && wizhood(list[i]) != "(immortal)" ) continue;
			if(list[i]->query("id")=="tianlin") continue;
			if(list[i]->query("id")=="lei") continue;
			if( interactive(list[i]) )
				ppl_cnt++;
			player_cnt++;
			str = sprintf("%s%12s%s%s\n",str,RANK_D->query_rank(list[i]),
				online_flag(list[i]),
				list[i]->short(1));

		}
	}
	else {
		ppl_cnt = 0;
		i = sizeof(list);
		while( i-- ){
			if(!environment(list[i])) continue;
			if(!me && wizardp(list[i]) && list[i]->query("env/invisibility")) continue;
			//                        if(list[i]->query("id")=="tianlin") continue;
			if(!remote && !wizardp(me) && !me->visible(list[i])) continue;
			if(opt_wiz && !wizardp(list[i]) ) continue;
			if(opt_male && list[i]->query("gender")!="男性") continue;
			if(opt_female && list[i]->query("gender")!="女性") continue;
			if(opt_normal && list[i]->query("gender")!="无性") continue;
			if(opt_dead && !list[i]->query_temp("netdead")) continue;
			if(opt_pkgroup && !list[i]->query_temp("pkgroup/sure")) continue;

			name = online_flag(list[i]),

			bigname = list[i]->name(1);
			if(strlen(bigname) > 12) bigname = sprintf("%.12s...",bigname);
			if( wizardp(list[i])){
				name = sprintf( "%s%-15s(%-11s"" ",name,bigname,
					capitalize(list[i]->query("id"))+")");
			}
			else if(list[i]->query("gender") == "女性"){
				//                      name = sprintf( "%s%-15s(%-11s"" " + HIC,name,bigname,
				name = sprintf( "%s%-15s(%-11s",name,bigname,
					capitalize(list[i]->query("id"))+")");
			}
			else {
				name = sprintf( "%s%-15s(%-11s"" ",name,bigname,
					capitalize(list[i]->query("id"))+")");
			}
			str = sprintf("%s%25s%s", str, name,ppl_cnt%3==2?"\n":"");
			ppl_cnt++;
			player_cnt++;
		}
		if ( ppl_cnt%3 ) str += "\n";
	}
	str += "═════════════════════════════════════════════\n";
	if(opt_number)
		str = "目前当前共有 "+(player_cnt)+" 位使用者连线中。\n";
	else if(player_cnt)
		str = sprintf("%s共有 %s 位使用者连线中，系统负担：%s\n ""*"" 表示发呆中，""#"" 表示断线中。\n\n", str,  CHINESE_D->chinese_number(player_cnt),
		query_load_average());
	else
		str = sprintf("目前游戏中并没有符合该条件的玩家。\n");
	if( remote ) return str;
	else
		me->start_more(str);
	me->set_temp("who_time",time());
	return 1;
}
int sort_user(object ob1, object ob2)
{
	string name1, name2;
	if( wiz_level(ob1) != wiz_level(ob2) )
		return wiz_level(ob2) - wiz_level(ob1);
	name1 = ob1->query("family/family_name");
	name2 = ob2->query("family/family_name");
	if (intp(name1)) name1 = "";
	if (intp(name2)) name2 = "";
	if (name1 > name2) return -1;
	if (name1 < name2) return 1;
	//                return (int)ob2->query("family/generation") - (int)ob1->query("family/generation");
	return 1;
}

int help()
{
	write("

指令格式 : who -w | -f | <ID> | <名字> | <门派ID>

这个指令可以列出所有在游戏中的玩家。

-w        列出游戏中的巫师
<ID>      列出ID与之匹配的玩家
<名字>    列出名字与之匹配的玩家
<门派ID>  列出门派与之匹配的玩家

相关指令： finger \n\n");
        return 1;
}



