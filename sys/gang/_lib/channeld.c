// cracked by vikee 2/09/2002   vikee@263.net 
// channeld.c 
// modified by tool on 96/10/05 
// modified by mon@xyj on 10/97 to add support for 
//          intermud emote. 
// modified by fengs 
// modified by deep 
// modified by firefox 

#include <ansi.h> 
#include <net/dns.h> 
#include <net/macros.h> 
inherit F_DBASE; 

// mon 6/16/99 
int intermud_open=1; 
void open_intermud(); 
void close_intermud(); 
int query_inter() {return intermud_open;} 

// mon 8/5/99 
int TOTAL=4000; 
mapping msg_buf=([]); 
int check_string(string arg, string who, int emote_mode); 
string query_buffer() {return sprintf("%O\n",msg_buf);} 

// deep 7/23/06 
static string msg_log; 
static int log_from; 
static string wiz_msg_log; 
static int wiz_log_from; 

object* team_listener(object me);
object* bang_listener(object me);
object* org_listener(object me);  
object* area_listener(object me);  

mapping channels = ([ 
  "sys":  (["name"     :"系统",
    "msg_speak": HIG "【%s】%s：%s\n" NOR, 
    "wiz_only": 1 
  ]),
  "zi":  (["name"     :"汉字",
    "msg_speak": WHT "【%s】%s：%s\n" NOR, 
    "wiz_only": 1 
  ]),
  "debug":(["name"     :"代码调试",
    "msg_speak": HIG "【%s】%s：%s\n" NOR, 
    "wiz_only": 1 
  ]), 
  "wiz":  (["name"     :"巫师",
    "msg_speak": HIY "【%s】%s：%s\n" NOR, 
    "msg_emote": HIY "【%s】%s\n" NOR, 
    "wiz_only": 1 
  ]), 
  "gwiz": (["name"     :"网际巫师",
    "msg_speak": HIG "【%s】%s：%s\n" NOR, 
    "msg_emote": HIG "【%s】%s\n" NOR, 
    "wiz_only": 1, 
    "intermud": GWIZ, 
    "channel": "CREATOR", 
    "filter": 1, 
    "intermud_emote": 0 
  ]), 
  "xyj":  (["name"     :"西游记",
    "msg_speak": YEL "【%s】%s：%s\n" NOR, 
    "msg_emote": YEL "【%s】%s\n" NOR, 
    "intermud": GCHANNEL, 
    "channel": "xyj", 
    "filter": (:$1["MUDLIB"]=="A Journey to the West" :) 
  ]), 
  "es":   (["name"     :"潭际闲聊",
    "msg_speak": HIR "【%s】%s：%s\n" NOR, 
    "msg_emote": HIR "【%s】%s\n" NOR, 
    "intermud": GCHANNEL, 
    "channel": "es", 
    "filter": 1 
  ]), 
  //keep the channel name 
  //as "es" to be compatible with other 
  //ES2 type muds. 
  "sldh": (["name"     :"水陆大会",
    "msg_speak": HIC "【%s】%s：%s\n" NOR, 
    "msg_emote": HIC "【%s】%s\n" NOR, 
  ]), 

  "chat": (["name"     :"闲聊",
    "msg_speak": HIC "【%s】%s：%s\n" NOR, 
    "msg_emote": HIC "【%s】%s\n" NOR, 
  ]), 
  "rumor":(["name"     :"谣言",
    "msg_speak": HIM "【%s】%s：%s\n" NOR, 
    "msg_emote": HIM "【%s】%s\n" NOR, 
    "anonymous": "某人" 
  ]), 
  "teamtalk":(["name"     :"队伍",
    "msg_speak": WHT"【%s】%s：%s\n" NOR,
    "msg_emote": WHT"【%s】%s\n" NOR,
    "listeners": (:team_listener:) 
  ]),
  "menpai":(["name"     :"门派", //will be changed
    "msg_speak": HIW"【%s】%s：%s\n" NOR,
    "msg_emote": HIW"【%s】%s\n" NOR,
    "listeners": (:bang_listener:) 
  ]),
  "orgtalk":(["name"     :"组织", //will be changed
    "msg_speak": CYN"【%s】%s：%s\n" NOR,
    "msg_emote": CYN"【%s】%s\n" NOR,
    "listeners": (:org_listener:) 
  ]),
  "westwar": (["name"     :"西游战争",
    "msg_speak": HIB "【%s】%s：%s\n" NOR, 
    "msg_emote": HIB "【%s】%s\n" NOR, 
    "listen_only": 1,
  ]), 
  "areatalk":(["name"     :"区域", //will be changed
    "msg_speak": RED"【%s】%s：%s\n" NOR,
    "msg_emote": RED"【%s】%s\n" NOR,
    "listeners": (:area_listener:) ,
  ]),
  "gt":(["name"     :"帮派", //will be changed
    "msg_speak": HIY"【%s】%s：%s\n" NOR,
    "msg_emote": HIY"【%s】%s\n" NOR,
    "listeners": (:org_listener:) 
  ]),

]); 

int valid_channel(object me, string verb)
{
    return(!undefinedp(channels[verb]) &&
      (wizardp(me) || !(channels[verb]["wiz_only"]) ));
}

void create() 
{ 
    seteuid(getuid());  // This is required to pass intermud access check. 
    set("channel_id", "频道精灵"); 
} 

// deep 7/23/06 
string log_time() 
{ 
    string msg = ctime(time()); 

    //    msg = msg[4..6] + "/" + msg[8..9] + "/" + 
    //    msg[20..23] + " " + msg[11..18]; 
    msg = msg[11..18]; 
    return msg; 
} 

// deep 7/23/06 
void channel_log(string msg, string verb, object user) 
{ 
    string lfn; 
    mixed lt; 
    int t; 

    if (! mapp(channels[verb]) || ! objectp(user) || ! userp(user)) 
        return; 

    msg=remove_ansi(msg);
    if (channels[verb]["wiz_only"]) 
    { 
        if (! stringp(wiz_msg_log)) wiz_msg_log = ""; 

        t = time();
        if (wizardp(user))
            wiz_msg_log += sprintf(" %s %s\t%s", 
              user->query("id"), log_time(), msg); 
        if (strlen(wiz_msg_log) > 8000 || t - wiz_log_from > 900) 
        { 
            lt = localtime(t); 

            lfn = sprintf("channel/wiz_%02d-%02d-%02d", lt[5], lt[4] + 1, lt[3]); 
            assure_file(LOG_DIR + lfn); 
            log_file(lfn, wiz_msg_log); 
            wiz_msg_log = ""; 
            wiz_log_from = t; 
        } 
    } 
    else 
    { 
        if (! stringp(msg_log)) msg_log = ""; 

        t = time(); 
        msg_log += sprintf("%10s%10s%s", 
          user->query("id"), log_time(), msg); 
        if (strlen(msg_log) > 8000 || t - log_from > 900) 
        { 
            lt = localtime(t); 

            lfn = sprintf("channel/%02d-%02d-%02d", lt[5], lt[4] + 1, lt[3]); 
            assure_file(LOG_DIR + lfn); 
            log_file(lfn, msg_log); 
            msg_log = ""; 
            log_from = t; 
        } 
    } 
} 



varargs int do_channel(object me, string verb, string arg, int emote, 
  int allow_chat) 
{ 
    object *ob; 
    string *tuned_ch, who, arg1, msg; 
    int time,count,count1,last_chat,len; 

    // Check if this is a channel emote. 
    if(sizeof(verb)>0) 
        if( verb[sizeof(verb)-1] == '*' ) { 
            emote = 1; 
            verb = verb[0..<2]; 
        } 

        // mon 10/29/98 
        // ignore too long messages to reduce flooding. 
        //if( arg && userp(me)) arg=replace_string(arg, "*",""); 
    if(arg && strlen(arg)>240) return 0; 

    if( !mapp(channels) || undefinedp(channels[verb]) ) 
        return 0; 

    if( userp(me) && !allow_chat )  
    { 
        if(channels[verb]["wiz_only"] && !wizardp(me) ) 
            return 0; 
        if( emote && undefinedp(channels[verb]["msg_emote"])  )  
        { 
            write("对不起，这个频道不支持 emote 。\n"); 
            return 1; 
        } 
        //temporary block chat flooding. 
        time=time(); 
        if( me->query("channel/chat_block")  
          && (time-me->query("channel/chat_block"))<0 ) 
            return notify_fail("你的交谈频道被暂时关闭了。\n"); 
        /*     还是不要这个判断比较好，一登录不能说话，很郁闷 by fengs 
          if (me->query("mud_age") < 3600) 
              return notify_fail("连线1小时以上才能聊天。\n");*/ 

        count=me->query("channel/chat_count"); 
        // if the channel arg contains too many lines, 
        // then count more than once. -- mon 8/16/98 
        count1=sizeof(explode(" "+arg,"\n"))/3+1; 
        // if arg too long, also counts more. 
        count1+=sizeof(arg)/200; 
        count+=count1; 
        last_chat=me->query("channel/last_chat"); 
        if( count>2 && !wizardp(me) )  
        { 
            count=0; 
            me->set("channel/last_chat",time); 
            if (time==last_chat || count1>2)  
            { 
                me->set("channel/chat_block",time+180); 
                return notify_fail("因为一次讲话太多，你的交谈频道被暂时关闭了。\n"); 
            } 
        } 
        me->set("channel/chat_count",count); 
        /*if( !wizardp(me) && ( !arg || !(string)me->query_temp("last_channel_msg") ) )  
        { 
            if( arg == (string)me->query_temp("last_channel_msg") ) 
          return notify_fail("用交谈频道说话请不要重复相同的讯息。\n"); 
        } 
        else  
        { 
            if ( !wizardp(me) && strsrch(arg,(string)me->query_temp("last_channel_msg"))>=0 ) 
          return notify_fail("用交谈频道说话请不要重复相同的讯息。\n"); 
        }*/ 
        if( arg == (string)me->query_temp("last_channel_msg") ) 
            return notify_fail("用交谈频道说话请不要重复相同的讯息。\n"); 
        // If we speaks something in this channel, then must tune it in. 
        tuned_ch = me->query("channels"); 
        if( !pointerp(tuned_ch) ) 
            me->set("channels", ({ verb }) ); 
        else if( member_array(verb, tuned_ch)==-1 ) 
            me->set("channels", tuned_ch + ({ verb }) ); 

        if(channels[verb]["listen_only"] && !wizardp(me) ) 
        { 
            write("对不起，这个频道不支持发言，你只能打开并收听该通道 。\n"); 
            return 1; 
        } 

        // Support of channel emote 
        if( emote && !channels[verb]["intermud_emote"])  
        { 
            string vb, emote_arg; 

            if( nullp(arg) ) return 0; 
            if( sscanf(arg, "%s %s", vb, emote_arg)!= 2 )  
            { 
                vb = arg; 
                emote_arg = ""; 
            } 
            if( channels[verb]["anonymous"] ) 
                arg = EMOTE_D->do_emote(me, vb, emote_arg, 1, 1); 
            else  
            { 
                arg = EMOTE_D->do_emote(me, vb, emote_arg, 1, 0, 
                  !undefinedp(channels[verb]["intermud"])); 
                if(!arg)  
                { 
                    string id, site; 

                    if(sscanf(emote_arg, "%s@%s", id, site)==2)  
                    { 
                        int age=me->query("mud_age"); 

                        // prevent login  newbie to flood channels. 
                        if(!wizardp(me))  
                        { 
                            if(age<3600) return notify_fail("你现在还不能使用这个频道。\n"); 
                            else if(age<86400)  
                            { 
                                if((int)me->query("sen")<30)  
                                    return notify_fail("你现在精神不足，不能使用这个频道。\n"); 
                                me->add("sen",-5); 
                            } 
                        } 

                        // check whether repeated messages. -- mon 8/5/99 
                        if(!check_string(vb+":"+id+"@"+site, 0, 1))  
                            return 0; 

                        // mon 6/16/99 
                        if(!intermud_open) return 1; 

                        "/adm/daemons/network/services/gemote_q"-> 
                        send_msg(channels[verb]["channel"], me, 
                          vb, id, site, channels[verb]["filter"]); 
                        return 1; 
                    } 
                } 
            } 

            if( !arg ) return 0; 
        } 
    } 

    // Make the identity of speaker. 

    if( channels[verb]["anonymous"] ) { 
        who = channels[verb]["anonymous"]; 
        if (userp(me)) { 
            if((int)me->query("sen")<50) return 
                notify_fail("你已经没有精神散布谣言了。\n"); 
            me->add("sen",-5); 
            do_channel( this_object(), "sys",  
              sprintf("谣言：%s(%s)。", me->name(),me->query("id"))); 
        } 
    } 
    else if( userp(me) || !stringp(who = me->query("channel_id")) ) { 
        who = me->query("name"); 
        if(me->query("id"))  
            who=who+"(" + capitalize(me->query("id")) + ")"; 
    } 

    // Ok, now send the message to those people listening us. 

    if(functionp(channels[verb]["listeners"]))
        ob=evaluate(channels[verb]["listeners"], me);
    else ob = users();
    if(!arrayp(ob)||sizeof(ob)==0) return 0; //Sometimes will get failed
    ob = filter_array( ob, "filter_listener", this_object(), channels[verb] ); 
    if( !arg ) arg = "．．．"; 

    // check whether repeated messages. -- mon 8/5/99 
    if( !undefinedp(channels[verb]["intermud"])) { 
        //          do_channel( this_object(), "sys",  
        //              sprintf("%s:%d", who,emote?1:0)); 
        if(!check_string(arg, who, 0)) return 0; 
        //if(!check_string(arg, who, emote?1:0)) return 0; 
    } 

    len=strlen(arg); 
    while(len>1 && arg[len-1]=='\n') 
        arg=arg[0..((len--)-2)]; 
    //remove excessive return at the end. by mon 9/20/97 

    if(userp(me)) arg1=replace_string(arg, "$N", me->name()); 
    else arg1=arg; 

    if( emote ) { 
        // Support of old behavier of intermud emote. 
        if( channels[verb]["intermud_emote"] ) arg1 = who + " " + arg; 
    } 

    if( arrayp(channels[verb]["extra_listener"]) ) { 
        channels[verb]["extra_listener"] -= ({ 0 }); 
        if( sizeof(channels[verb]["extra_listener"]) ) 
            channels[verb]["extra_listener"]->relay_channel(me, verb, arg); 
    } 

    if( !undefinedp(channels[verb]["intermud"]) 
      &&  base_name(me) != channels[verb]["intermud"] ) { 
        if(userp(me)) { 
            int age=me->query("mud_age"); 

            arg=replace_string(arg, "$N", me->name()+"("+ 
              capitalize(me->query("id"))+"@"+Mud_name()+")",1); 
            arg=replace_string(arg, "$N", me->name()); 

            // prevent login  newbie to flood channels. 
            if(!wizardp(me)) { 
                if(age<3600) return notify_fail( 
                      "你现在还不能使用这个频道。\n"); 
                else if(age<86400) { 
                    if((int)me->query("sen")<30) return  
                        notify_fail 
                        ("你现在精神不足，不能使用这个频道。\n"); 
                    me->add("sen",-5); 
                } 
            } 
            // mon 6/16/99 
            if(!intermud_open) return 1; 
        } 
        channels[verb]["intermud"]->send_msg( 
          channels[verb]["channel"], me->query("id"),  
          me->name(1), arg, emote, channels[verb]["filter"] ); 
    } 

    arg1=replace_string(arg1, "\n", "\n ");
    if( emote ) { 
        arg1 +=NOR + BLK" ."NOR;
        msg = sprintf( channels[verb]["msg_emote"], channels[verb]["name"], arg1 ); 
        message( "channel:" + verb, 
          msg, ob ); 
        channel_log(msg, verb, me); 
    } else 
    { 
        msg = sprintf( channels[verb]["msg_speak"], channels[verb]["name"], who, arg1 ); 
        message( "channel:" + verb, 
          msg, ob ); 
        channel_log(msg, verb, me); 
    } 

    if( userp(me) ) { 
        me->set_temp("last_channel_msg", arg); 
        //log_file("channel",me->query("id")+":"+arg+"\n"); 
    } 
    return 1; 
} 

int filter_listener(object ppl, mapping ch) 
{ 
    // Don't bother those in the login limbo. 
    if( !ppl ) return 0;
    if( !environment(ppl) ) return 0; 

    if( ch["wiz_only"] ) return wizardp(ppl); 
    return 1; 
} 

void register_relay_channel(string channel) 
{ 
    object ob; 

    ob = previous_object(); 
    if( undefinedp(channels[channel]) || !ob) return; 
    if( arrayp(channels[channel]["extra_listener"]) ) { 
        if( member_array(ob, channels[channel]["extra_listener"]) >=0 ) return; 
        channels[channel]["extra_listener"] += ({ ob }); 
    } else 
        channels[channel]["extra_listener"] = ({ ob }); 
} 

void open_intermud() 
{ 
    intermud_open=1; 
} 

void close_intermud() 
{ 
    intermud_open=0; 
    remove_call_out("open_intermud"); 
    call_out("open_intermud", 36000); 
} 

// mon 8/5/99 
int check_one_string(string str, string site) 
{ 
    int first, last; 

    if(!msg_buf || !sizeof(msg_buf) || !site) return 1; 
    if(undefinedp(msg_buf[site]) || !sizeof(msg_buf[site])) return 1; 

    first=strsrch(msg_buf[site], str); 
    last=strsrch(msg_buf[site], str, -1); 

    if(first>-1 && last>-1 && first!=last) { 
        // the same sentence at least appeared twice. 
        //        do_channel( this_object(), "sys",  
        //            sprintf("Repeated msg from %s:%s.", site, str)); 
        return 0; 
    } 

    return 1; 
} 

int check_string(string arg, string who, int emote_mode) 
{ 
    int len, k; 
    string str, site; 

    arg=replace_string(arg,"\n",""); 
    arg=replace_string(arg,"|",""); 

    notify_fail("请不要在潭际频道发送重复信息，谢谢合作。\n"); 

    if(!who || sscanf(who, "%*s@%s)", site)!=2 || !sizeof(site)) { 
        site="local_host"; 
    } else { // for incoming messages, remove one "who" part. 
        arg=replace_string(arg,who,"",1); 
        site=lower_case(site); 
    } 

    len=sizeof(arg); 
    if(len<2) return 0; 

    if(len<5 || emote_mode) { 
        if(!check_one_string(arg, site)) return 0; 
    } else { 
        k=len/2; 
        if(k>20) k=20; 
        else if(k<4) k=4; 

        switch(random(3)) { 
        case 0: 
            str=arg[0..k-1]; // first 1/3 
            if(!check_one_string(str, site)) return 0; 
            break; 
        case 1: 
            str=arg[(len-k+1)/2..(len+k-1)/2]; // middle 1/3 
            if(!check_one_string(str, site)) return 0; 
            break; 
        case 2: 
            str=arg[(len-k)..(len-1)]; // last 1/3 
            if(!check_one_string(str, site)) return 0; 
            break; 
        } 
    } 

    // ok, this is a new message. add to buffer. 
    if(len<=80 || emote_mode) { 
        str=arg; 
    } else { 
        switch (random(3)) { 
        case 0:  
            str=arg[0..79]; break; 
        case 1:  
            str=arg[(len-79)/2..(len+79)/2]; break; 
        case 2: 
            str=arg[(len-80)..(len-1)]; break; 
        } 
    } 

    //    do_channel( this_object(), "sys",  
    //        sprintf("%s:%s", who,str)); 

    if(undefinedp(msg_buf[site])) { 
        msg_buf[site]=str; 
    } else { 
        while(sizeof(msg_buf[site])>TOTAL) { 
            if((k=strsrch(msg_buf[site],"|"))>-1) { 
                msg_buf[site]=msg_buf[site][k+1..]; 
            } else break; 
        } 
        msg_buf[site]+="|"+str; 
    } 

    return 1; 
} 


object* team_listener(object me)
{
    object* obs=me->query_team();
    if(!arrayp(obs)) notify_fail("你现在并没有和别人组成队伍。\n");
    return obs;
} 
object* bang_listener(object me)
{
    object *obs, *target;
    int i;
    string mebang,obbang; 
    mebang = (string)me->query("family/family_name");
    if(!mebang)
    {
        //notify_fail("你不属于任何帮派！\n");
        //return ({});
        channels["menpai"]["name"]="普通百姓";
    } 
    else
        channels["menpai"]["name"]=mebang;

    obs=users();
    i = sizeof(obs);
    while (i--)
    {
        obbang = (string)obs[i]->query("family/family_name");
        if((mebang == obbang || wizardp(obs[i])))
        {
            if (sizeof(target)==0)
                target=({obs[i]});
            else 
                target+=({obs[i]});
        }
    }
    return target;
} 
object* org_listener(object me)
{
    object *obs, *target;
    int i;
    string meorg,oborg; 
    meorg = (string)me->query("organization/org_name");
    if(!meorg)
    {
        notify_fail("你不属于任何组织！\n");
        return ({});
    } 
    channels["orgtalk"]["name"]=meorg;

    obs=users();
    i = sizeof(obs);
    while (i--)
    {
        oborg = (string)obs[i]->query("organization/org_name");
        if((meorg == oborg || wizardp(obs[i])))
        {
            if (sizeof(target)==0)
                target=({obs[i]});
            else 
                target+=({obs[i]});
        }
    }
    return target;
}    


object* area_listener(object me)
{
    object *obs,*target;
    int i;
    string mearea,mepath,obpath;
    if (!environment(me))
    {
        notify_fail("你不在任何区域！\n");
        return ({});
    } 
    if (MISC_D->is_very_special_place(environment(me)))
    {
        notify_fail("你不在任何区域！\n");
        return ({});
    } 
    mearea = MISC_D->find_place2(environment(me));
    mepath = MISC_D->find_place_path(environment(me));
    channels["areatalk"]["name"]=mearea;
    obs=users();
    i = sizeof(obs);
    while (i--)
    {
        if (!environment(obs[i])) continue;
        obpath = MISC_D->find_place_path(environment(obs[i]));
        if((mepath == obpath || wizardp(obs[i])))
        {
            if (sizeof(target)==0)
                target=({obs[i]});
            else 
                target+=({obs[i]});
        }
    }
    return target;
}
