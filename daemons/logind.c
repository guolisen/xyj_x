//Cracked by Roath
#include <ansi.h>
#include <command.h>
#include <login.h>
#include <net/daemons.h>
#include <net/macros.h>
#include <mudlib.h>     // for GB_AND_BIG5 define.

inherit F_DBASE;
#define MUDLIST_CMD     "/cmds/usr/mudlist"
// added by xfile@bjxyj for debug.
// 2005-7-30
#define DEBUG 0

#if DEBUG
object xfile = find_player("xfile");
#endif


int wiz_lock_level = WIZ_LOCK_LEVEL;
string *banned_name = ({
	"你","我","他","她","它",
	"毛泽东","江泽民","邓小平","李鹏","朱榕基","胡锦涛","温家宝","周恩来",
	"自己","某人","尸体","我们","你们","他们","大家",
	"他妈的", "去你的", "巫师",
	"他奶奶的","他姥姥的","水老鼠","飞蚂蚁","李靖对你",
	"管理员","系统管理员",
	"圣","坐山雕","Ｘ档案","佩佩","不不","图省事儿","格格巫","西瓜太郎",
	"麦克小狼","小宝","水壶","【"," ",
});
string *legalid;

string *default_name = ({
	"猴子","狐狸", "老鼠",
	"蜻蜓","甲虫","蝴蝶","蝈蝈",
	"螳螂","瓢虫","蝗虫","蟋蟀",
	"牛", "老虎", "兔子",
	"狗","猫咪","羊","猪",
	"骆驼","乌龟","蛇","鱼儿",
	"鹿","马","犀牛"
});
string *default_prefix=({
	"小","大","老","白","黄","黑","花","灰",
	"纸","木头","石头","泥","黄毛","黑角","黑风",
});

int new_start = 0;

void logind_user_log(); // mon 11/5/98
int total_players();
int total_count;
private void encoding(string arg, object ob);
private void if_young(string arg, object ob);
private void get_id(string arg, object ob);
private void confirm_id(string yn, object ob);
object make_body(object ob);
varargs void enter_world(object ob, object user, int silent);
varargs void reconnect(object ob, object user, int silent);
object find_body(string name);
int check_legal_id(string arg, int insaneid);
int check_legal_name(string arg);
string dis_attr(int value);
private void confirm_gift(string yn,object ob,object user);

void create()
{
	seteuid(getuid());
	set("channel_id", "连线精灵");
	set("id", "logind");

	legalid = explode(read_file(BANNED_ID), "\n");
}

// mon 11/7/98
void logind_user_log()
{
	int user=sizeof(users());
	int total;

	remove_call_out("logind_user_log");
	rm("/log/user_count");    log_file("user_count",""+
		((total=total_count)?total:user)+"\n"+
		user+"\n"+
		UPTIME_CMD->report_str()+"\n"+
		"西游记\n");
	call_out("logind_user_log",600);
}

// added by snowcat Mar 11 1998
int total_players()
{
	mapping mud_list;
	mixed *muds;
	string output;
	int loop, size, nb, total=0;

	if( !find_object(DNS_MASTER) )
		return 0;

	mud_list = (mapping)DNS_MASTER->query_muds();
	if(!mud_list)
		return 0;

	muds = keys( mud_list ) - ({ "DEFAULT" });
	for(loop = 0, size = sizeof(muds); loop<size; loop++) {
		if(mud_list[muds[loop]]["MUDLIB"]=="A Journey to the West" 
			&& !undefinedp(mud_list[muds[loop]]["USERS"])) {
				sscanf (mud_list[muds[loop]]["USERS"],"%d",nb);
				total += nb;
		}
	}

	total_count=total;
	return total;
}

void logon(object ob)
{
	//防止恶意reconnet造成系统崩溃 by pkyou
	/*
	object *online_user;
	int logon_cnt;
	int i;

	online_user = filter_array(children(LOGIN_OB), (: interactive :));
	i = sizeof(online_user);
	logon_cnt = 0;
	while (i--) 
	{  if (query_ip_number(online_user[i]) == query_ip_number(ob))
	logon_cnt = logon_cnt + 1 ;
	}

	if (logon_cnt > 15 ) {

	log_file( "login", sprintf("%s:恶意reconnet:%s\n" , ctime(time()) , query_ip_number(ob) ) );
	write(HIW"请你稍候再进入本MUD...... \n");
	destruct(ob);
	return;
	}
	*/
	//防止恶意reconnet造成系统崩溃 by pkyou
#ifdef GB_AND_BIG5
	cat(BANNER);
	write("            西游记欢迎您来访！使用国标码的玩家请键入：gb\n");
	write("           ﹁村癘舧眤ㄓ砐ㄏノき絏產叫龄big5\n\n");
	write("    [If there is no response after ENTER, please try Ctrl-ENTER]\n");
	write("        [提示：如果按ENTER键后系统没有响应，请试 Ctrl-ENTER]\n\n");
	write("         Welcome to Xi You Ji! Select GB or BIG5 (gb/big5):");
	input_to( (: encoding :), ob );
#else
	encoding("gb",ob);
#endif

}

private void encoding(string arg, object ob)
{
	object *usr;
	int i, ttl_cnt, wiz_cnt, ppl_cnt, login_cnt;
	string ip_name, ip_number;
	int ii;
	mixed info;
	int encode;


	if(!arg || arg=="") {
		write("\nSelect 国标码 GB or き絏 BIG5 (gb/big5):");
		input_to( (: encoding :), ob );
		return;
	} else if(arg[0..0]=="g" || arg[0..0]=="G")
		encode=0;
	else if(arg[0..0]=="b" || arg[0..0]=="B")
		encode=1;
	else {
		write("\nSelect 国标码 GB or き絏 BIG5 (gb/big5):");
		input_to( (: encoding :), ob );
		return;
	}

	ob->set_encoding(encode);

	ip_name = query_ip_name(ob);
	ip_number = query_ip_number(ob);

	if(new_start==0) { //only check for once.
		//           if(!find_object(DNS_MASTER) || !"/adm/daemons/band"->check_ip_(
		//	    DNS_MASTER->get_host_name(mud_nname()))) {
		//	    log_file("no shutdown", "no Shutdown IP "+
		//	      DNS_MASTER->get_host_name(mud_nname()) +
		//	      " " +ctime(time())+"\n");
		//	    shutdown(1);
		//	    return;
		//	   }
		new_start++;
	}
	//by mon 9.22.97 for mirror security check.
	// only IP specified in band.c can run this mud.

	//log all connections.
	log_file( "ALLCONT", sprintf("IP_name--number  %s--%s (%s)\n", ip_name,
		ip_number, ctime(time()) ) );

	// snowcat dec 10 1997
	// try strict ban here...weiqi.

	if ("/adm/daemons/band"->is_strict_banned(query_ip_number(ob)) == 1) {
		write("您的地址在本 MUD 之信誉被人破坏了。\n");
		destruct(ob);
		log_file( "ALLCONT", sprintf("kicked out, strict_banned\n"));
		return;
	}

	// try not accept "name" as IP

	if (!ip_name) {
		destruct(ob);
		log_file( "ALLCONT", sprintf("kicked out, No IP\n"));
		return;
	}

	for(ii=0; ii<sizeof(ip_number); ii++) {
		if( (ip_number[ii] != '.')&&(ip_number[ii]>'9') ){
			destruct(ob);
			log_file( "ALLCONT", sprintf("kicked out, Non_number\n"));
			return;
		}
	}

	write(CLR);
	cat(WELCOME);
	catch(MUDLIST_CMD->main());

	UPTIME_CMD->report();

	// children will show both netdead and interactive users.
	usr = children(USER_OB);
	wiz_cnt = 0;
	ppl_cnt = 0;
	login_cnt = 0;
	for(i=0; i<sizeof(usr); i++) {
		if( !environment(usr[i]) ) login_cnt++;
		else if( (wizardp(usr[i]) && (string)wizhood(usr[i])!="(elder)")&& 
			!usr[i]->query("env/invisibility") ) wiz_cnt++;
		else ppl_cnt++;
	}
	// snowcat Mar 11 1998
	ttl_cnt = total_players();
	if (ttl_cnt == 0)
		printf("目前"); // info not available
	else
		printf("目前共有%d位玩家在线上。本站", ttl_cnt );
	printf("共有%d位巫师、%d位玩家，以及%d位在尝试连线。\n\n",
		wiz_cnt, ppl_cnt, login_cnt );

	// mon 11/7/98
	//check whether user_log still running.
	info = filter_array(call_out_info(), (: $1[1]=="logind_user_log" :));
	if(!sizeof(info)) logind_user_log();


	/* move this check to after user input id.

	// mon 4/19/98
	// reduce number of pending login users.
	#ifdef MAX_USERS
	if(sizeof(usr)>(MAX_USERS+10)) {
	write("对不起，"+MUD_NAME+"的玩家已经太多了，请待会儿再来。\n");
	destruct(ob);
	return;
	}
	#endif

	*/

	if (ob) ob->set_temp("id_count",0);
	//mon 10/15/97 to prevent flooding illegal ID after login.

#ifndef GB_AND_BIG5
	write("[提示：如果按ENTER键后系统没有响应，请试 Ctrl-ENTER]\n\n");
#endif

	//we do not welcome young kid playing mud. weiqi...971220.
	write("鉴于学生的主要任务是学习，本游戏不欢迎中小学生来玩。\n");
	write("您是否是中小学学生或年龄更小？(yes/no)");
	input_to( (: if_young :), ob );
}

private void if_young(string arg, object ob)
{
	int id_count;

	id_count=ob->query_temp("id_count");
	// mon 7/19/97 to prevent flooding by repeating illegal id.
	id_count++;
	ob->set_temp("id_count",id_count);
	if(id_count>3) {
		destruct(ob);
		log_file( "ALLCONT", sprintf("kicked out, illegal ID.\n"));
		return;
	}

	if(arg=="\n" || arg=="") {
		write("您是否是中小学学生或年龄更小？(yes/no)");
		input_to( (: if_young :), ob );
		return;
	}

	if( arg[0..0] == "y" || arg[0..0] == "Y" )
	{
		write("\n好，赶紧去学习才是正道理。\n");
		destruct(ob);
		return;
	}

	if( arg[0..0] != "n" && arg[0..0] != "N" ) {
		write("您是否是中小学学生或年龄更小？(yes/no)");
		input_to( (: if_young :), ob );
		return;
	}

	cat(XYJ_SITES);
	write("\n您的英文名字：（新玩家请键入 new 注册）");
	input_to( (: get_id :), ob);
}

private void get_id(string arg, object ob)
{
	object ppl, *usr = children(USER_OB);
	int id_count;

	//edw 6/2/98
	int NowLogin, MaxLimit, login_site, i;
	string my_ip, new_ip;
	//end edw

	if(!ob) return;

	id_count=ob->query_temp("id_count");
	// mon 7/19/97 to prevent flooding by repeating illegal id.
	id_count++;
	ob->set_temp("id_count",id_count);
	if(id_count>6) {
		destruct(ob);
		log_file( "ALLCONT", sprintf("kicked out, illegal ID.\n"));
		return;
	}

	arg = lower_case(arg);
	if( !check_legal_id(arg, 0)) {
		write("您的英文名字：");
		input_to("get_id", ob);
		return;
	}

	ppl = find_body(arg);

#ifdef MAX_USERS
	if( (string)SECURITY_D->get_status(arg)=="(player)"
		&& sizeof(users()) >= MAX_USERS ) {
			// Only allow reconnect an interactive player when MAX_USERS exceeded.
			// i.e., ppl exist. (has nothing to do with whether it interactive) -- mon 3/15/99
			//if( !ppl || !interactive(ppl) )
			if( !ppl ) {
				write("对不起，"+MUD_NAME+"的玩家已经太多了，请待会儿再来。\n");
				destruct(ob);
				return;
			}
	}
#endif

	if( wiz_level(arg) < wiz_lock_level ) {
		write("对不起，" + MUD_NAME + "目前限制巫师等级 " + WIZ_LOCK_LEVEL
			+ " 以上的人才能连线。\n");
		destruct(ob);
		return;
	}

	//edw@zju.mirror.xyj 6/2/98 (limit multi-login)
	// MAX_LOGIN and LOGIN_SITE should be defined in login.h
#ifdef MAX_LOGIN

	if(!ppl)
	{
		my_ip=query_ip_number(ob);

		MaxLimit="/adm/daemons/band"->allow_multi_login(my_ip);
		if(!MaxLimit) MaxLimit=MAX_LOGIN;
#ifdef LOGIN_SITE
		login_site=LOGIN_SITE;
#else
		login_site=0;
#endif
		if(my_ip && login_site==0) // ignore the last field of the IP
			my_ip=my_ip[0..strsrch(my_ip, ".", -1)];

		NowLogin=0;

		for(i=0;i<sizeof(usr);i++)
		{
			if(ob!=usr[i])
			{
				new_ip=query_ip_number(usr[i]);

				// for net_dead players.
				if(!new_ip && !interactive(usr[i]))
					new_ip=usr[i]->query_temp("netdead_ip");

				if(new_ip && login_site==0)
					new_ip=new_ip[0..strsrch(new_ip, ".", -1)];

				// modified by xfile@bjxyj.
				if(my_ip==new_ip && !usr[i]->query_temp("netdead") )
				{
					NowLogin++;
				}

			}
		}

		if(NowLogin>=MaxLimit)
		{
			write(sprintf("对不起，从你的IP地址不能同时登录%s位人物。\n",
				chinese_number(MaxLimit+1)));
			destruct(ob);
			return;
		}
	}
	else
	{
		// added by xfile@bjxyj 2005.1.24
		// if we found the ppl body in MUD, it means that player reconnect
		// to game, in this case there were 2 situations:
		//
		// 1. reconnect from original IP.
		// 2. reconnect from different IP.
		// At the first situation, it was simple thing, we will let it go.
		// and at the other side, we must detect if the IP has been exceeded.
		// if so, it should be denied.
		my_ip = query_ip_number( ppl );
		new_ip = query_ip_number( ob );

		// reconnect from another site.
		if ( my_ip != new_ip )
		{
			//	MaxLimit="/adm/daemons/band"->allow_multi_login(my_ip);
			//	if(!MaxLimit)
			MaxLimit=MAX_LOGIN;
#ifdef LOGIN_SITE
			login_site=LOGIN_SITE;
#else
			login_site=0;
#endif
			if(my_ip && login_site==0) // ignore the last field of the IP
				my_ip=my_ip[0..strsrch(my_ip, ".", -1)];

			NowLogin=0;

			for(i=0;i<sizeof(usr);i++)
			{
				// xfile@bjxyj 2005-7-30
				// make a filter for system temp user object.
				if ( usr[i]->query("id") == "user object")
					continue;

				if(ob!=usr[i])
				{
					new_ip=query_ip_number(usr[i]);

					// for net_dead players.
					if(!new_ip && !interactive(usr[i]))
					{
						new_ip=usr[i]->query_temp("netdead_ip");
					}

					if(new_ip && login_site==0)
						new_ip=new_ip[0..strsrch(new_ip, ".", -1)];

					if(my_ip==new_ip)
					{
						if ( !my_ip || !new_ip )
							continue;
#if DEBUG
						// added by xfile for debug message.
						// 2005-7-30
						if ( xfile && wizardp(xfile))
						{
							tell_object (xfile, usr[i]->query("id") + my_ip + "\n");
							tell_object (xfile, usr[i]->query("id") + new_ip + "\n");
						}
#endif
						NowLogin++;
					}

				}
			}

			if(NowLogin>=MaxLimit)
			{
				write(sprintf("对不起，从你的IP地址不能同时登录%s位人物。\n",
					chinese_number(MaxLimit+1)));
				destruct(ob);
				return;
			}
		}
	}
#endif

	if( (string)ob->set("id", arg) != arg ) {
		write("Failed setting user name.\n");
		destruct(ob);
		return;
	}

	if( arg=="guest" ) {
		// If guest, let them create the character.
		//		confirm_id("Yes", ob);
		//		return;
	} else if (arg=="new") { // new player login
		write("\n请您给自己取一个英文名字：");
		input_to("get_new_id",ob);
		return;
	} else if( file_size(ob->query_save_file()
		+ __SAVE_EXTENSION__) >= 0 ) {
			if( ob->restore() ) {
				write("请输入相应密码：");
				input_to("get_passwd", 1, ob);
				return;
			}
			write("您的人物储存档出了一些问题，请利用 guest 人物通知巫师处理。\n");
			destruct(ob);
			return;
	}

	write("没有这个玩家．．．\n");
	write("您的英文名字：（新玩家请键入 new 注册）");
	input_to("get_id", ob);
	return;
}

private void get_new_id(string arg, object ob)
{
	object ppl, *body;  
	int id_count, i, nb=0;  
	//修改多重登陆

	if(!ob) return;

	id_count=ob->query_temp("id_count");
	// mon 7/19/97 to prevent flooding by repeating illegal id.
	id_count++;
	ob->set_temp("id_count",id_count);
	if(id_count>6) {
		destruct(ob);
		log_file( "ALLCONT", sprintf("kicked out, illegal ID.\n"));
		return;
	}

	if(!arg) {
		write("\n请您给自己取一个英文名字：");
		input_to("get_new_id", ob);
		return;
	}

	arg = lower_case(arg);
	if( !check_legal_id(arg, 1)) {
		write("\n请您给自己取一个英文名字：");
		input_to("get_new_id", ob);
		return;
	}

	if( (string)ob->set("id", arg) != arg ) {
		write("Failed setting user name.\n");
		destruct(ob);
		return;
	}

	ppl = find_body(arg);
	if(ppl || arg=="guest" || arg=="new") {
		write("这个名字已经被别的玩家使用了．．．");
		write("\n请您给自己取一个英文名字：");
		input_to("get_new_id",ob);
		return;
	}

	if( file_size(ob->query_save_file()
		+ __SAVE_EXTENSION__) >= 0 ) {
			write("这个名字已经被别的玩家使用了．．．");
			write("\n请您给自己取一个英文名字：");
			input_to("get_new_id",ob);
			return;
	}
	//修改多重登陆新人 by pkyou
	ob->set("new_player", 1);  
	body = children(LOGIN_OB);  
	i = sizeof(body);  
	while (i--) {   
		if( clonep(body[i]) && body[i]->query("id")==arg  
			&& body[i]->query("new_player")==1 ) nb++;  
		if( nb>1 ) {  
			write("对不起，已经有人在用这个英文名字创造人物了．．．\n");  
			write("\n请您给自己取一个英文名字：");  
			ob->delete("new_player");  
			input_to("get_new_id",ob);  
			return;  
		}  
	}  
	//by pkyou
	confirm_id("Yes", ob);
	return;
}

private void get_passwd(string pass, object ob)
{
	string my_pass,id;
	object user;

	write("\n");
	my_pass = ob->query("password");
	if( crypt(pass, my_pass) != my_pass ||
		!SECURITY_D->match_wiz_site(ob, query_ip_number(ob)) ) {
			write("密码错误！");
			write("请重新连线，键入正确的密码或另取一个新的英文名字。\n");
			if((id=ob->query("id")) && member_array(id,
				SECURITY_D->get_wizlist())!=-1)
				log_file("wizlogin",ctime(time())+" "+id+
				" failed login from "+query_ip_number(ob)+"\n");
			else
				log_file("login",ctime(time())+" "+id+
				" failed login from "+query_ip_number(ob)+"\n");
			destruct(ob);
			return;
	}

	// Check if we are already playing.
	user = find_body(ob->query("id"));
	if (user) {

		// netdead is delayed being set
		// after disconnected, so should use interactive.
		// mon 7/5/98
		if( !interactive(user) ) {
			reconnect(ob, user);
			return;
		}
		write("您要将另一个连线中的相同人物赶出去，取而代之吗？(y/n)");
		input_to("confirm_relogin", ob, user);
		return;
	}

	if( objectp(user = make_body(ob)) ) {
		if( user->restore() ) {
			log_file( "USAGE", sprintf("%s(%s) loggined from %s (%s)\n", 
				user->query("name"),
				user->query("id"), query_ip_number(ob), ctime(time()) ) );

			//kickout限制登陆时间 by pkyou
			if(time()-(int)user->query("kickout_time") < 86400) {
				write("你现在已经没有进入西游记的权利，请二十四小时后再连线。\n"NOR);
				destruct(user);
				destruct(ob);
				return;
			}
			/*
			if(time()-(int)user->query("quit_time") < 30) { //by gslxz 2010.5.6
			write("\n你刚退出游戏，为了减轻系统负担请过30秒后再连入，谢谢合作。^0^\n\n");
			destruct(user);
			destruct(ob);
			return;
			}
			*/

			enter_world(ob, user);
			return;
		} else {
			destruct(user);
		}
	}

	if(ob) destruct(ob);
	return;

	//	write("请您重新创造这个人物。\n");
	//	confirm_id("y", ob);
}

private void confirm_relogin(string yn, object ob, object user)
{
	object old_link;

	if( yn=="" ) {
		write("您要将另一个连线中的相同人物赶出去，取而代之吗？(y/n)");
		input_to("confirm_relogin", ob, user);
		return;
	}

	if( (yn[0]!='y' && yn[0]!='Y') || !user ) {
		// user may be destructed during the process.
		// so I put in this check. mon 4/15/98
		write("好吧，欢迎下次再来。\n");
		destruct(ob);
		return;
	} else {
		tell_object(user, "有人从别处( " + query_ip_number(ob)
			+ " )连线取代你所控制的人物。\n");
		log_file( "USAGE", sprintf("%s(%s) replaced by %s (%s)\n",
			user->query("name"), user->query("id"),
			query_ip_number(ob), ctime(time()) ) );
	}

	// Kick out tho old player.
	old_link = user->query_temp("link_ob");

	//	if( old_link ) {
	// mon 7/5/98
	// need to check user is interactive before exec.
	// user may become non-interactive after the input_to.
	if( old_link && interactive(user)) {
		// 5/11/98 mon
		user->set_encoding(ob->query_encoding());

		exec(old_link, user);
	}
	if(old_link)      // mon 9/14/98
		destruct(old_link);

	reconnect(ob, user);
}

private void confirm_id(string yn, object ob)
{
	/*
	if( yn=="" ) {
	write("使用这个名字将会创造一个新的人物，您确定吗(y/n)？");
	input_to("confirm_id", ob);
	return;
	}

	if( yn[0]!='y' && yn[0]!='Y' ) {
	write("好吧，那么请重新输入您的英文名字：");
	input_to("get_id", ob);
	return;
	}
	*/


	write("

中 文 名 字 注 册 
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
请您给自己想一个符合〖 西游记 〗神话世界的中文名字。不要取一些不
雅或是容易造成他人困扰的名字。这个名字将代表您在这个世界的形象，而
且往后很少能再更改，请务必慎重。( 您的名字如果取的不妥，网络巫师将
有权给予更改，所以郑重建议您取一个比较有个性且比较文明的带有一定浓
郁色彩中文名字 )。如果您不能正确输入中文名字,请按几下回车键(ENTER)
系统将随机给您筛选出一个中文名字。
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
");
	write("您的中文名字：");
	ob->set_temp("get_name",0);
	input_to("get_name", ob);
}

private void get_name(string arg, object ob)
{
	arg = CONVERT_D->input(arg,ob);

	if( !check_legal_name(arg) ) {
		ob->add_temp("get_name",1);
		if(ob->query_temp("get_name")>2) {
			// the user can't input proper chinese name.
			// assign one for him/her.    mon 4/19/98

			arg=default_prefix[random(sizeof(default_prefix))]+
				default_name[random(sizeof(default_name))];

			write("因为你不能输入适当的中文名字，系统指定你的名字为："+
				arg+"\n");
			write("请在进入游戏后请巫师帮助修改。\n");

		} else {
			write("您的中文名字：");
			input_to("get_name", ob);
			return;
		}
	}

	printf("%O\n", ob);
	ob->set("name", arg);
	write("请设定您的密码：");
	input_to("new_password", 1, ob);
}

private void new_password(string pass, object ob)
{
	write("\n");
	if( strlen(pass)<5 ) {
		write("密码至少要由五个字符组成，请重设您的密码：");
		input_to("new_password", 1, ob);
		return;
	}
	ob->set("password", crypt(pass,0) );
	write("请再输入一次您的密码，以确认您没记错：");
	input_to("confirm_password", 1, ob);
}

private void confirm_password(string pass, object ob)
{
	string old_pass;
	write("\n");
	old_pass = ob->query("password");
	if( crypt(pass, old_pass)!=old_pass ) {
		write("您两次输入的密码并不一样，请重新设定一次密码：");
		input_to("new_password", 1, ob);
		return;
	}

	write("
邮 件 地 址 注 册 
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
为了避免您的人物遭人盗用西游记将采用 Email 认证方式保护您的人物
所有权。所以请您输入一个正确的可供网络有效接受认证用的个人电子邮件
地址这个电子邮件地址除了系统巫师以外（玩家个人使用命令有意公开除外）
不会被其他的使用者看到。如果您没有正确输入这个地址,在您的密码或者身
份标识遗失后将不能得到网络巫师的帮助而找回。
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
");
	write("您的电子邮件地址：");
	input_to("get_email",  ob);
}

private void get_email(string email, object ob)
{
	object user;

	ob->set("email", email);

	// If you want do race stuff, ask player to choose one here, then you can
	// set the user's body after the question is answered. The following are
	// options for player's body, so we clone a body here.
	ob->set("body", USER_OB);
	if( !objectp(user = make_body(ob)) ) {
		if(ob) destruct(ob);
		return;
	}

	write("您要扮演男性(m)的角色或女性(f)的角色？");
	input_to("get_gender", ob, user);
}

private void get_gender(string gender, object ob, object user)
{
	if( gender=="" ) {
		write("您要扮演男性(m)的角色或女性(f)的角色？");
		input_to("get_gender", ob, user);
		return;
	}

	if( gender[0]=='m' || gender[0]=='M' )
		user->set("gender", "男性");
	else if( gender[0]=='f' || gender[0]=='F' )
		user->set("gender", "女性" );
	else {
		write("对不起，您只能选择男性(m)或女性(f)的角色：");
		input_to("get_gender", ob, user);
		return;
	}

	confirm_gift("n",ob,user);
}

object make_body(object ob)
{
	string err;
	object user;
	int n;

	if(!ob->query("body")) {
		return 0;
	}
	user = new(ob->query("body"));
	if(!user) {
		write("现在可能有人正在修改玩家物件的程式，无法进行复制。\n");
		write(err+"\n");
		return 0;
	}
	seteuid(ob->query("id"));
	export_uid(user);
	export_uid(ob);
	seteuid(getuid());
	user->set("id", ob->query("id"));
	user->set_name( ob->query("name"), ({ ob->query("id")}) );
	return user;
}

private void confirm_gift(string yn, object ob, object user)
{
	int n, a, b;

	if(!ob || !user) {
		if(user) {
			destruct(user);
			return;
		}
		if(ob) destruct(ob);
		return;
	}

	user->set("kar", 20 );
	user->set("str", 20 );
	user->set("cps", 20 );
	user->set("int", 25 );
	user->set("cor", 20 );
	user->set("con", 20 );
	user->set("spi", 25 );
	user->set("per", 20 );

	// mon 3/21/99 allow players to choose gift after login.
	user->set("no_gift",1);

	CHAR_D->setup_char(user); //setup user weight. mon 11/7/97
	user->set("title", "普通百姓");
	user->set("birthday", time() );
	user->set("potential", 99);
	user->set("food", user->max_food_capacity());
	user->set("water", user->max_water_capacity());
	user->set("channels", ({ "chat","rumor","xyj","sldh" }) );
	user->update_age(); //7/3/99 mon
	log_file( "USAGE", sprintf("%s was created from %s (%s)\n", 
		user->query("id"),
		query_ip_number(ob), ctime(time()) ) );

	ob->set("last_from",query_ip_number(ob));
	ob->set("last_on",time());
	ob->delete("new_player"); //修改多重登陆新人,取消临时参数 by pkyou 

	return enter_world(ob, user);
}

string dis_attr(int value)
{       int gift=20;
if( value > gift ) return sprintf( HIY "%3d" NOR, value );
else if( value < gift ) return sprintf( CYN "%3d" NOR, value );
else return sprintf("%3d", value);
}

varargs void enter_world(object ob, object user, int silent)
{
	object cloth, room, mbx;
	string startroom="";
	int num;

	reset_eval_cost();
	user->set_temp("temp_time",time());
	user->set_temp("link_ob", ob);
	ob->set_temp("body_ob", user);

	// 5/11/98 mon
	user->set_encoding(ob->query_encoding());

	exec(user, ob);

	write("目前权限：" + wizhood(user) + "\n");
	user->setup();

	// In case of new player, we save them here right aftre setup
	// compeleted.
	user->save();
	ob->save();

	if( !silent ) {
		if(file_size(MOTD)>0)
			user->start_more(read_file(MOTD));

		// mon 3/21/99
		// new user login.
		if(user->query("no_gift")) {
			user->move("/d/wiz/init",1);
		} else {
			int approved;

			if( user->is_ghost() )
				startroom = DEATH_ROOM;
			else if( strlen(startroom = user->query("startroom"))<2 )
				startroom = START_ROOM;

			if(!wizardp(user) && startroom[0..2]=="/u/") {
				startroom = START_ROOM;
				user->set("startroom",startroom);
			}
			//added by mon 10/27/97

			// the following 7 lines are aded by snowcat dec 10 1997
			if(startroom=="/d/wiz/punish") {
				user->move(startroom);
			} else if (("/adm/daemons/band"
				->create_char_banned(query_ip_number(user)) == 1 ||
				"/adm/daemons/band"->is_banned(query_ip_number(user))
				== 1 || ((approved=user->query("banned_approved"))!=0
				&& approved!=1)) && !wizardp(user)) {

					// here added by xfile@bjxyj.
					// purpose: when player comes from banned IP address, he will be declined from the
					// XYJ world until wiazrd approve.
					// 2004-12-2 14:15
					if ( BAN_D->is_banned(query_ip_number(user)) == 1
						&& user->query("banned_approved") != 1)
					{
						user->set("banned_approved", -1);
					}

					user->move("/d/wiz/guest");
					log_file( "ALLCONT", sprintf(
						"from banned site or is being banned.\n"));
			} else if( load_object(startroom) )
				user->move(startroom);
			else {
				user->move(START_ROOM);
				startroom = START_ROOM;
				user->set("startroom", START_ROOM);
			}

			if(!environment(user))//修改多物品时突然quit不能进mud Bug by pkyou
			{
				user->move(START_ROOM);
				startroom = START_ROOM;
				user->set("startroom", START_ROOM);
			}

			if(!wizardp(user) || !user->query("env/invisibility"))
				tell_room(startroom, user->query("name") + "连线进入这个世界。\n",
				({user}));
		}
		//added gslxz 2010.3.7 连线提示
		write( NOR+"欢迎你连线进入西游记的神话世界,祝你在此能够玩的愉快！！！ \n\n" + NOR);
		if (!ob->query("count_come")){
			ob->set("count_come",1);}
		write(HIR"→ "+ NOR+"欢迎你第"HIY + chinese_number(ob->query("count_come")) +NOR"次来到西游记！！！\n" + NOR);
		ob->add("count_come",1);
		write(HIR"→ "+NOR+"您上次的退线地址："HIG + ob->query("last_from")+" \n" + NOR);
		write(HIR"→ "+NOR+"您本次的连线地址："HIG +query_ip_name(user)+" \n" + NOR);
		write(HIR"→ "+NOR+"您上次的退线时间：" HIG+ BJTIME_CMD->chinese_time(1, ctime(ob->query("last_on")))+ " \n" + NOR);

		mbx=ob->query_temp("mbox_ob");
		if (!mbx) {
			mbx=new(MAILBOX_OB);
			mbx->set_owner(ob->query("id"));
		}
		num=mbx->query_new_mail();
		if( num>0 ) {
			write( GRN + "\n千里眼告诉你：有您"
				+chinese_number(num)+
				"封信！请到南城客栈来一趟．．．\n\n" + NOR);
		}
		destruct(mbx);
		CHANNEL_D->do_channel( this_object(), "sys",
			sprintf("%s由%s连线进入。", user->name()+"("+capitalize(user->query("id")) + ")", query_ip_name(user)) );
		//增加IP登陆记录功能 2010.3.7
		log_file("cmds/login", sprintf("%s(%s)从(%s)登陆系统. 时间在：(%s)\n",
			user->name(),query_ip_number(user),user->query("id"),ctime(time()) ) );
	}
	//NEWS_D->prompt_user(user);

	UPDATE_D->check_user(user, 0);
	MPTOP_D->check_mp_player(user);
}

varargs void reconnect(object ob, object user, int silent)
{
	object old_link;

	int approved;

	// mon 9/15/98
	old_link=user->query_temp("link_ob");
	if(old_link && old_link!=ob)
		destruct(old_link);

	user->set_temp("link_ob", ob);
	ob->set_temp("body_ob", user);

	// 5/11/98 mon
	user->set_encoding(ob->query_encoding());

	exec(user, ob);

	user->reconnect();
	if( !silent && !user->query("env/invisibility")) {
		tell_room(environment(user), user->query("name") + 
			"重新连线回到这个世界。\n",
			({user}));
		CHANNEL_D->do_channel( this_object(), "sys",
			sprintf("%s由%s重新连线进入。", user->query("name")+"(" + 
			capitalize(user->query("id")) + ")", query_ip_name(user)) );
	}
	UPDATE_D->check_user(user, 1); // this is for reconnect.

	// added by xfile@bjxyj
	// 2005.1.19
	// when the user reconnected from a banned IP sites, we will
	// send him to punish room.

	if ((BAN_D->create_char_banned(query_ip_number(user)) == 1 ||
		BAN_D->is_banned(query_ip_number(user)) == 1 ||
		((approved=user->query("banned_approved"))!=0 && approved!=1)) && 
		!wizardp(user))
	{

		if ( BAN_D->is_banned(query_ip_number(user)) == 1
			&& user->query("banned_approved") != 1)
		{
			user->set("banned_approved", -1);
		}

		user->move("/d/wiz/guest");
		log_file( "ALLCONT", sprintf(
			"reconnected from banned site or is being banned.\n"));
	}



}

int check_legal_id(string id, int insaneid)
{
	int i;

	i = strlen(id);

	if( (strlen(id) < 3) || (strlen(id) > 8 ) ) {
		write("对不起，你的英文名字必须是 3 到 8 个英文字母。\n");
		return 0;
	}
	while(i--)
		if( id[i]<'a' || id[i]>'z' ) {
			write("对不起，你的英文名字只能用英文字母。\n");
			return 0;
		}


		// only check when creating new ids.
		if(insaneid) {
			for(i=0; i<sizeof(legalid); i++)   {
				if(legalid[i][0..0]=="*") { // wildcard match
					if(strsrch(id, legalid[i][1..])!=-1) {
						write("对不起，这种名字会造成其他人的困扰。\n");
						return 0;
					}
				} else {
					if( id == legalid[i] )   { // exact match
						write("对不起，这种名字会造成其他人的困扰。\n");
						return 0;
					}
				}
			}
		}
		return 1;
}

int check_legal_name(string name)
{
	int i;

	i = strlen(name);

	if( (strlen(name) < 2) || (strlen(name) > 12 ) ) {
		write("对不起，你的中文名字必须是一到六个中文字。\n");
		return 0;
	}
	while(i--) {
		if( name[i]<=' ' ) {
			write("对不起，你的中文名字不能用控制字符。\n");
			return 0;
		}
		if( i%2==0 && !is_chinese(name[i..<0]) ) {
			write("对不起，请您用「中文」取名字。\n");
			return 0;
		}
	}
	if( member_array(name, banned_name)!=-1 ) {
		write("对不起，这种名字会造成其他人的困扰。\n");
		return 0;
	}

	return 1;
}

object find_body(string name)
{
	object ob, *body;

	if( objectp(ob = find_player(name)) )
		return ob;
	body = children(USER_OB);
	for(int i=0; i<sizeof(body); i++) {
		ob=body[i];
		if( clonep(ob) && getuid(ob) == name
			&& ob->query("max_gin")>0 ) return ob;
		//check max_gin to avoid damaged user object.
	}
	
	return 0;
}

int set_wizlock(int level)
{
	if( wiz_level(this_player(1)) <= level )
		return 0;
	if( geteuid(previous_object()) != ROOT_UID )
		return 0;
	wiz_lock_level = level;
	return 1;
}


