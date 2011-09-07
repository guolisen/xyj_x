
#include <ansi.h>
#include <net/dns.h>
#include <mudlib.h>
inherit F_CLEAN_UP;

int sort_user(object,object);
int help();

//����Ƿ�����
string online_flag(object who)
{
	if(interactive(who)) {
		if(query_idle(who)>120) return "*";
	} else {
		if(!who->query_temp("scheme")) return "#";
	}
	return " ";	
}

private void create() { seteuid(getuid()); }
string *exclude = ({"tianlin","lei"});

mixed main(object me, string arg, int remote)
{
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
					write("��·ѶϢ���ͳ������Ժ�\n");
					return 1;
				}
				ob1 = present(option[i], environment(me));
				if (!ob1) ob1 = find_player(option[i]);
				if (!ob1) ob1 = find_living(option[i]);
				if ((!ob1) && (option[i] =="me")) ob1=me;
				if (!ob1) return notify_fail("û�������һ��������\nָ���ʽ : who [-h] [-l] [-k] [-w] [-b] [-p] [-f] [-m] [-a] [-d][<ID>]\n");
				me = ob1; opt_party = 1;
		}
	}
	if(me) if(objectp(me)) if( !wizardp(me))
	{
		if(time()-me->query_temp("who_time") < 10 ) 
			return notify_fail("ϵͳæ�� ���Ժ��ٳ��ԡ�\n");
		else if(opt_long && (int)me->query("force") < 5 ) {
			return notify_fail("��ľ���̫���ˣ�û�а취��֪������ҵ���ϸ���ϡ�\n");
			me->receive_damage("force", 5);}

	}
	if(remote) {
		opt_long=0; // disable -l for remote because too long.
#ifdef INTERMUD_NAME
		str  = "�� " + INTERMUD_NAME + "";
#else
		str = "�� " + MUD_NAME + "";
#endif
	} else {
		str = "�� " + MUD_NAME + "";
	}
	if(opt_banghui)
		if(me->query("banghui"))
			str += me->query("banghui")+"������У�";
		else
			return notify_fail("��Ŀǰ��û�м����κΰ�ᡣ\n");
	if(opt_pkgroup)
		if(me->query_temp("pkgroup/sure"))
			str += "�μ�PK�������У�";
		else
			return notify_fail("��Ŀǰ��û�вμ�PK���\n");
	else if(opt_party)
		if(me->query("family/family_name"))
			str += me->query("family/family_name")+"������У�";
		else str += "��ͨ�����У�";
	else if(opt_male)
		str += "��������У�";
	else if(opt_female)
		str += "Ů������У�";
	else if(opt_normal)
		str += "̫���У�";
	else if(opt_wiz)
		str += "��ʦ�У�";
	else if(opt_long) str += "����У�";

	else str += "�������У�";

	str += "\n�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n";
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
			if(opt_male && list[i]->query("gender")!="����") continue;
			if(opt_female && list[i]->query("gender")!="Ů��") continue;
			if(opt_normal && list[i]->query("gender")!="����") continue;
			if(opt_dead && !list[i]->query_temp("netdead")) continue;
			if(opt_pkgroup && !list[i]->query_temp("pkgroup/sure")) continue;

			name = online_flag(list[i]),

			bigname = list[i]->name(1);
			if(strlen(bigname) > 12) bigname = sprintf("%.12s...",bigname);
			if( wizardp(list[i])){
				name = sprintf( "%s%-15s(%-11s"" ",name,bigname,
					capitalize(list[i]->query("id"))+")");
			}
			else if(list[i]->query("gender") == "Ů��"){
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
	str += "�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n";
	if(opt_number)
		str = "Ŀǰ��ǰ���� "+(player_cnt)+" λʹ���������С�\n";
	else if(player_cnt)
		str = sprintf("%s���� %s λʹ���������У�ϵͳ������%s\n ""*"" ��ʾ�����У�""#"" ��ʾ�����С�\n\n", str,  CHINESE_D->chinese_number(player_cnt),
		query_load_average());
	else
		str = sprintf("Ŀǰ��Ϸ�в�û�з��ϸ���������ҡ�\n");
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

ָ���ʽ : who [-h] [-l] [-w] [-p] [-f] [-m] [-a] [-d] [<ID>]

���ָ������г���������Ϸ�е���Ҽ���ȼ���

-h �г�������Ļ��
-l ѡ���г��ϳ���ѶϢ��
-b ֻ�г�ͬ������ҡ�
-p ֻ�г�ͬ���ɵ���ҡ�
-w ֻ�г���Ϸ�е���ʦ��
-f ֻ�г���Ϸ�е�Ů��ҡ�
-m ֻ�г���Ϸ�е�����ҡ�
-k ֻ�г��μ�PK�����ҡ�
-n ֻ�г���Ϸ�е�������ҡ�
-a ֻ�г���ǰ��Ϸ����ҵ���������
-d ֻ�г���ǰ��Ϸ�д��ڶ���״̬�е���ҡ�

<ID> �г�<ID>��������������ɵ���ҡ�

* ��ʾ�����У�# ��ʾ�����С�

���ָ� finger \n\n");
        return 1;
}



