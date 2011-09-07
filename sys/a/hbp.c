//Cracked by Roath
// treasure_box.c
// created by xfile@bjxyj 
// 2004-12-20 12:45

#include <ansi.h>

#define MAX_ITEM                10000
#define MAX_ENCUMBRANCE         10000000

inherit ITEM;

void create()
{
        set_name(HIW "�۱���" NOR, ({"jubao pen", "pen"}));
        set_weight(5000000);
        set("long", "һ�����������ľ۱��裬���滹���ҵķ���Щ��Ʒ(list)��\n"
                "���۱�����Ŷ��� : putin ��Ʒ\n"
                "�Ӿ۱�����ȡ���� ��fetch ��Ʒ\n");     
        set("material", "stone" );       
        set("unit","��");
        set("no_get","��������������������˰��쾢ҲûŲ��һ�֡�\n");        
        set_max_encumbrance( MAX_ENCUMBRANCE );
        set_max_items( MAX_ITEM );
        seteuid(geteuid());
        setup();
        
}

// helper function.
// get name filt ansi color character.
varargs string get_name( string str )
{
    string str1, str2;
    
    if ( !str )
                str = query("name");
        
    while( sscanf(str,"%s*sm%s",str1,str2) == 3 )
                str = str1 + str2;
    return str;
}

void init()
{
        // normal player action.
        add_action("do_list","list");
        add_action("fetch_obj","fetch");
        add_action("put_obj","putin");  
        add_action("do_get","get");
        
        // wizard action.
        add_action("do_reset", "reset" );  
        add_action("do_set_name","set_name");
}


// reset the table.
// purpose : clean up the objects. and refresh all flags.
int do_reset()
{
        mapping numbers;
        string *key;
        int *value, i;
        
        object me = this_player();
        object table = this_object();
        
        if (!wizardp( me ) )    
                return 0;
        
        numbers = query_temp("numbers");
    
        if(!numbers) 
                return 0;
        
        key = keys(numbers);
        value = values(numbers);
        i = sizeof(numbers);
    
        while(i--) 
        {
                if( value[i] > 50 )
                        set_temp( "numbers/" + key[i], value[i] - 2 );
        }
        
        return 1;
}

int do_get(string arg)
{
    string str1,str2;
    if (!arg) return 0;
    if( sscanf(arg, "%s from %s", str1,str2) == 2 )
    {
         if (str2=="jubao pen"||str2=="pen")
         {
          write("��������þ��˳��̵�����������ʲôҲû�õ���\n");
          return 1;
         }
    }
    return 0;
}

int do_list()
{ 
        mapping objs;
        string list, *name;
        int i;
        int j = 0;
        string tlist;
        object me = this_player();
        
        if( !mapp(objs = query_temp("objects")) )
                return notify_fail( get_name() + "��Ŀǰ�ǿյģ�ʲô��û�С�\n");
        
        name = keys( objs );
        if( !sizeof(objs) ) 
                return notify_fail( get_name() + "��Ŀǰ�ǿյģ�ʲô��û�С�\n");
        
        list = query("name") + "����������Щ������\n";
        i = sizeof( objs );
        while(i--) 
        {
                if(!objs[name[i]])
                {
                        delete_temp("numbers/"+name[i]);
                        delete_temp("objects/"+name[i]);
                        continue;
                }
                tlist = get_name(name[i]);
                list += sprintf("%3d  %-30s��%s%s\n", ++j, tlist,
                        chinese_number(query_temp("numbers/"+name[i])),
                        objs[name[i]]->query("unit") );
        }
        me->start_more(list);
        
        return 1;
}

int fetch_obj(string arg)
{
        mapping objs;
        int rand_busy_time;
        string type;    
        string arg1, arg2;
        
        string *name;
        string fname;
        object obj_file, ob;
        int value, oldnum, afford, order;
        int i, j;
        object* inv;
        
        object who = this_player();
        object me = this_object();
        
        if ( who->query_temp("no_move") || who->is_busy() )
                return notify_fail("����һ��������û����ɣ������ƶ���\n");
        
        if (!arg )
                return notify_fail("��Ѿ�����������ȥ����ʲô?\n");
        
        
        if( sscanf(arg, "%s from %s", arg1, arg2) == 2 )   
        {
                arg = arg1;
        }
        if( sscanf(arg, "%s %d", fname, order) != 2 )   
        {
                fname = arg;
                order = 1;
        }       
        if( !mapp(objs = query_temp("objects")) )
                return notify_fail( get_name() + "��Ŀǰ�ǿյģ�ʲô��û�С�\n");
        name = keys( objs );
        if(!sizeof( objs )) 
                return notify_fail( get_name() + "��Ŀǰ�ǿյģ�ʲô��û�С�\n");
        
        j = 0;
        i = sizeof(name);
        while(i--)
        {
                if( !objs[name[i]]) continue;
                
                if( member_array(fname, objs[name[i]]->parse_command_id_list()) != -1 ||
                        strsrch(name[i], fname)>=0 )  
                {
                        j++;     
                }
                if( j == order )   
                {
                        obj_file = objs[name[i]];               
                        ob = new( base_name( obj_file ) ); 
                        ob->set_name(obj_file->query("name"),
                                obj_file->parse_command_id_list());
                        
                        rand_busy_time = random( 2 ) + 2 ;
                        
                        who->start_busy(rand_busy_time);
                        
                        message_vision( "$Nʹ���˳��̵�����ȥȡ�۱������" + ob->query("name") + "��\n", who );      
                        
                        // set the value to zero,  so that it can't be sold,
                        // and when the object was dropped, it will destroied itself.   
                        ob->set("value", 0);
                //      ob->set("no_give", "���֮������������ˣ�\n");        
                        ob->set("from_pen", 1);   
                        call_out("get_it", rand_busy_time - 1,  who, ob );              
                        
                        arg = obj_file->query("name")+ "("+obj_file->query("id")+")";
                        oldnum = query_temp("numbers/"+arg);
                        if(oldnum == 1)  
                        {
                                destruct(obj_file);
                                delete_temp("numbers/"+arg);
                                delete_temp("objects/"+arg);
                        }
                        else    
                        {
                                set_temp("numbers/"+arg, oldnum-1); 
                        }
                        
                        return 1;
                } // j == order
        } // while 
        
        write( get_name() + "����û������Ҫ�Ķ�����\n");
        return 1;
}

void get_it( object who, object ob )
{       
        int sen_cost;
        int ret;
        switch( random( 3 ) )
        {
        case 2:
                message_vision( "$N�۵���ͷ�󺹡�\n", who );    
                sen_cost = -10;
                break;
        case 1:
                message_vision( "$N�۵ĺ���䤱�����������ġ�\n", who );        
                sen_cost = -20;
                break;
        case 0:
                message_vision( "$N�۵�����ֱ�������ˡ�\n", who );      
                sen_cost = -30;
                break;  
        }
        
        who->add( "sen", sen_cost );
        
        ret = ob->move( who );
        message_vision( "����л��л�أ�$N�����õ���һ"+ ob->query("unit") + ob->query("name")+"��\n", who);
        
        
        if ( !ret  || random( 100 ) == 1 )
        {
                message_vision( "$Nһ��û����"+ ob->query("name")+"ͻȻ����ָ�们�䲻���ˡ�\n", who);
                destruct( ob );         
        }
        
}

// wizard can set name to this basin.
int do_set_name( string arg )
{
        if ( !wizardp( this_player() ) )
                return 0;
        
        arg = replace_string(arg, "$BLK$", BLK);
        arg = replace_string(arg, "$RED$", RED);
        arg = replace_string(arg, "$GRN$", GRN);
        arg = replace_string(arg, "$YEL$", YEL);
        arg = replace_string(arg, "$BLU$", BLU);
        arg = replace_string(arg, "$MAG$", MAG);
        arg = replace_string(arg, "$CYN$", CYN);
        arg = replace_string(arg, "$WHT$", WHT);
        arg = replace_string(arg, "$HIR$", HIR);
        arg = replace_string(arg, "$HIG$", HIG);
        arg = replace_string(arg, "$HIY$", HIY);
        arg = replace_string(arg, "$HIB$", HIB);
        arg = replace_string(arg, "$HIM$", HIM);
        arg = replace_string(arg, "$HIC$", HIC);
        arg = replace_string(arg, "$HIW$", HIW);
        arg = replace_string(arg, "$NOR$", NOR);
        
        arg += NOR;
        
        set_name( arg, ({"jubao pen", "pen"}) );
        write("�۱��������趨Ϊ��" + arg  + "\n" );
        write( "Ok!\n" );
        return 1;
}

// put object in basin.
int put_obj( string arg )
{
        string target, item;
        object dest_ob, *inv, me = this_player();
        
        object ob;
        int value, sale;
        string obj_file;
        int i, oldnum, amount;
        string index;
        mixed no_sell;
        int dest;
        int destroy_after_sell;         
        
        if( !arg  )
                return notify_fail( "������" + get_name() + "���ʲô��\nָ���ʽ��putin ��Ʒ��\n");
        
        if ( arg == "all" || arg == "jubao pen" || arg == "pen" )
                return notify_fail("ʲô��\n");                 
        
        if( this_player()->is_busy() || this_player()->query_temp("no_move") )
                return notify_fail("��������æ���ء�\n");
        
        if( !arg || !(ob = present(arg, this_player())) )
                return notify_fail("��Ҫ��ʲô��Ʒ�Ž�ȥ��\n");
                


        // 2004-12-28 14:02 xfile.
        if ( ob->query("no_drop") 
        || ob->is_character()
        || ( ob->query("value") == 0 && ob->query("from_pen") == 0 )
        || ob->query("money_id")|| ob->query("unique") )
                return notify_fail("�㲻�ܽ�" + ob->query("name") + "�ŵ�" + get_name() + "��ȥ��\n");

        // xfile 2004.12.28.
        // if (!ob->query("skill_type") && !ob->query("armor_type") && !wizardp( me ) )
        //      return notify_fail("�۱�����ֻ�ܷű����Ϳ��ס�\n");
        
        value = ob->query("value");
        
        if( (amount = ob->query_amount() ) > 0 )
        {
                if( value > ob->query("base_value") * amount )
                        return notify_fail("��"+ob->query("unit")+
                        ob->name()+"�������㰡���㻹�ǰ���Ŀ�չ���������Űɣ�\n");
        } 
        
        if( get_name(ob->query("name")) == "�쵤ƿ" || get_name(ob->query("name")) == "�̵�ƿ" )
                return notify_fail("�㲻�ܽ�" + ob->query("name") + "�ŵ�" + get_name() +"��ȥ!\n" );

        if( get_name(ob->query("name")) == "�𹿰�" || get_name(ob->query("name")) == "ʯ��" )
                return notify_fail("�㲻�ܽ�" + ob->query("name") + "�ŵ�" + get_name() +"��ȥ!\n" );
                
        if( ob->query("material") == "ice" )
                return notify_fail("���Ķ������·Ž�ȥҲ�û���\n");

        if( ob->query("no_put") )
                return notify_fail("�����������ܷŽ�ȥ��\n");
        
                if( ob->query("only_box") )
                return notify_fail("�����������ܷŽ�ȥ��\n");
        
        index = ob->query("name")+"("+ob->query("id")+")";
        
        destroy_after_sell=ob->query_temp("destroy_after_sell");
        
        //ob->set("no_get","��ֻ����fetch�������ȡ" + get_name() + "��Ķ�����\n");
        if( destroy_after_sell )
        {
                // set no_get flag.         
                ob->move( this_object() );
                dest = 1;
        } 
        else
        {
                if(!query_temp("objects/"+index) )
                {
                        set_temp("objects/"+index, ob);
                        set_temp("numbers/"+index, 1);
                        ob->move(this_object());
                        dest = 0;
                }
                else 
                {
                        oldnum = query_temp("numbers/"+index);
                        if( oldnum >= 100)
                                return notify_fail("�۱�����������������̫���ˡ�\n");
                        set_temp("numbers/"+index, oldnum+1);
                        dest = 1;
                }
        }
        
        message_vision("$N��" + ob->query("name") + "�ŵ�" + get_name() + "�\n",
                this_player());
        
        if( dest )
                destruct( ob );
        
        me->start_busy(1);
        
        return 1;        
        
        
}

// no clean up at this object to prevent items lose.
int clean_up()  
{
        return 0;
}> 