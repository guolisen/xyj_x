
#include <ansi.h>
#include <net/dns.h>
#include <net/macros.h>
#include <localtime.h>

inherit F_DBASE;

#include <dirty_words.h>

void channel_log(string msg);

mapping channels = ([
	"sys":	([
		"msg_speak": HIG "【系统】%s：%s\n" NOR,
		"wiz_only": 1 ]),
	"wiz":	([
		"msg_speak": HIY "【巫师】%s：%s\n" NOR,
		"msg_emote": HIY "【巫师】%s\n" NOR,
		"wiz_only": 1 ]),
	"gwiz": ([
		"msg_speak": HIY "【网际巫师】%s：%s\n" NOR,
		"msg_emote": HIY "【网际巫师】%s\n" NOR,
		"wiz_only": 1, "intermud": GWIZ, "channel": "CREATOR",
		"filter": 1,
		"intermud_emote": 1 ]),
	"xyj":	([
		"msg_speak": HIR "【西游记】%s：%s\n" NOR,
		"msg_emote": HIR "【西游记】%s\n" NOR,
		"intermud": GCHANNEL, "channel": "xyj",
		"filter": (:$1["MUDLIB"]=="A Journey to the West" :) ]),
	"es":	([
		"msg_speak": HIR "【潭际闲聊】%s：%s\n" NOR,
		"msg_emote": HIR "【潭际闲聊】%s\n" NOR,
		"intermud": GCHANNEL, "channel": "es",
		"filter": 1 ]), //keep the channel name as "es" to be compatible with other ES2 type muds.
	"sldh": ([
		"msg_speak": HIC "【水陆大会】%s：%s\n" NOR,
		"msg_emote": HIC "【水陆大会】%s\n" NOR, ]),
	"chat":	([
		"msg_speak": HIC "【闲聊】%s：%s\n" NOR,
		"msg_emote": HIC "【闲聊】%s\n" NOR,
		"wiz_spe": 1, ]),
	"rumor":([
		"msg_speak": HIM "【谣言】%s：%s\n" NOR,
		"msg_emote": HIM "【谣言】%s\n" NOR,
		"anonymous": "某人" ]),
]);

void create()
{
	seteuid(getuid());	// This is required to pass intermud access check.
	set("channel_id", "频道精灵");
}

varargs int do_channel(object me, string verb, string arg, int emote, int allow_chat)
{
	object *ob;
	string *tuned_ch, who, arg1, msg;
	int time,count,count1,last_chat,len, chat_age;

	// Check if this is a channel emote.
	if(sizeof(verb)>0)
		if( verb[sizeof(verb)-1] == '*' ) {
			emote = 1;
			verb = verb[0..<2];
		}

		// mon 10/29/98
		// ignore too long messages to reduce flooding.
		if(arg && strlen(arg)>240) return 0;

		if( !mapp(channels) || undefinedp(channels[verb]) )
			return 0;

		if( userp(me) && !allow_chat ) {
			if(channels[verb]["wiz_only"] && !wizardp(me) )
				return 0;

			//temporary block chat flooding.
			time=time();
			chat_age=(int)me->query("mud_age");
			if(chat_age<=36000) return notify_fail("为了防止人为恶意刷屏，连线时间超过十小时才可以使用这个频道。\n");   
			if(me->query("channel/chat_block") && (time-me->query("channel/chat_block")) < 0)
				return notify_fail("你的交谈频道被暂时关闭了。\n");

			count=me->query("channel/chat_count");
			// if the channel arg contains too many lines,
			// then count more than once. -- mon 8/16/98
			count1=sizeof(explode(" "+arg,"\n"))/3+1;
			// if arg too long, also counts more.
			count1+=sizeof(arg)/200;
			count+=count1;
			last_chat=me->query("channel/last_chat");
			if (count>2) {
				count=0;
				me->set("channel/last_chat",time);
				if (time==last_chat || count1>2) {
					me->set("channel/chat_block",time+180);
					return notify_fail("因为一次讲话太多，你的交谈频道被暂时关闭了。\n");
				}
			}
			me->set("channel/chat_count",count);

			if( arg==(string)me->query_temp("last_channel_msg") )
				return notify_fail("用交谈频道说话请不要重复相同的讯息。\n");

			// If we speaks something in this channel, then must tune it in.
			tuned_ch = me->query("channels");
			if( !pointerp(tuned_ch) )
				me->set("channels", ({ verb }) );
			else if( member_array(verb, tuned_ch)==-1 )
				me->set("channels", tuned_ch + ({ verb }) );

			// Support of channel emote
			if( emote && !channels[verb]["intermud_emote"]) {
				string vb, emote_arg;

				if( nullp(arg) ) return 0;
				if( sscanf(arg, "%s %s", vb, emote_arg)!= 2 ) {
					vb = arg;
					emote_arg = "";
				}
				if( channels[verb]["anonymous"] )
					arg = EMOTE_D->do_emote(me, vb, emote_arg, 1, 1);
				else {
					arg = EMOTE_D->do_emote(me, vb, emote_arg, 1, 0,
						!undefinedp(channels[verb]["intermud"]));
					if(!arg) {
						string id, site;
						if(sscanf(emote_arg, "%s@%s", id, site)==2) {
							int age=me->query("mud_age");
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
		if(!emote && wizardp(me) && channels[verb]["wiz_spe"]) {

			if (me->query("color"))
				who = me->query("color") + log_id(me);
			else
				who = log_id(me) + "说道";
			arg = HIY+arg+NOR;
			//                      if(me->query("env/invisibility") > 0)
			//                      do_channel( this_object(), "sys", sprintf(NOR "%s" HIR " 在隐身说话。", me->short(1) ));
		}



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

		ob = filter_array( users(), "filter_listener", this_object(), channels[verb] );
		if( !arg ) arg = "．．．";

		// Added by xfile@bjxyj 2004.11.29.
		// if the emote message contains dirty word, we will write the evidences log
		for ( int i = 0; i < sizeof( dirty_words ); i ++ )
		{		
			// if( member_array( arg, dirty_words ) != -1 )
			if ( strsrch( arg, dirty_words[i] ) >= 0 )
				log_file("channel_log",
				sprintf("%s(%s) said dirty word: %s at 【%s】 channel on %s\n",
				me->name(), me->query("id"), arg, verb, ctime(time()) ) );
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
			&&	base_name(me) != channels[verb]["intermud"] ) {
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
				}
				channels[verb]["intermud"]->send_msg(
					channels[verb]["channel"], me->query("id"), 
					me->name(1), arg, emote, channels[verb]["filter"] );
		}


		msg = emote ? sprintf(channels[verb]["msg_emote"], arg1)
			: sprintf(channels[verb]["msg_speak"], who, arg1);
		message("channel:" + verb, msg, ob);
		
		if(userp(me)) me->set_temp("last_channel_msg", arg);

		if(verb == "chat" || verb == "xyj") channel_log(msg);
		return 1;
}

int filter_listener(object ppl, mapping ch)
{
	// Don't bother those in the login limbo.
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

void channel_log(string msg)
{
	mixed* t = localtime(time());
	string file = sprintf(LOG_DIR"channel/%d/%02d/%02d.log", t[LT_YEAR], t[LT_MON] + 1, t[LT_MDAY]);

	assure_file(file);
	write_file(file, sprintf("%02d:%02d:%02d %s", t[LT_HOUR], t[LT_MIN], t[LT_SEC], msg));
}
