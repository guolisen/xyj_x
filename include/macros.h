// by firefox 11/21/2009

//����
#define assert(_exp) if(!(_exp)) error("assert: _exp\n")

//�ضϣ�xֵ�������m1-m2���䣬��ضϵ�m1��m2
#define truncate(x, x1, x2) (min2(max2(x, x1), x2))

//����
#define swap2(a, b) {mixed t = a; a = b; b = t;}

//aռb�İٷֱȣ���ĸΪ��ʱ����0
#define percent(a, b) ((b) ? (a)*100/(b) : 0)

//���̸���ѡ��
#define roulette(m) (MATH->roulette_(m))

//ϴ�ƣ�ʹ�����������
#define shuffle(arr) (MATH->shuffle_arr(arr))

//�������һ��Ԫ��
#define arr_last(arr) (arr[sizeof(arr) - 1])

//�û����ֺ�ID
#define name_id(who) (who->query("name") + "(" + capitalize(who->query("id")) + ")")

//�û����ֺ�ID
#define name_id2(name, id) ((name) + "(" + capitalize(id) + ")")

//�û���ǰʹ�õĵ�һ��ID
#define first_id(who) (who->parse_command_id_list()[0])

//�����û�����ID
#define copy_name_id(src, dst) (dst->set_name(src->name(), src->parse_command_id_list()))

//��ɫ�ʵ�����
#define color_name(name, color) (or2(color, "") + name + (color ? NOR : ""))

//���ֺ�ID����ָ����ֵ
#define name_id_is(who, name_, id_) (who->query("name") == (name_) && who->query("id") == (id_))

//�Ƿ�����λ��ͬһ����
#define same_env(ob1, ob2) (ob1 && ob2 && (environment(ob1) == environment(ob2)))

//�ж��Ƿ���ҹ��
#define at_night() (NATURE_D->query_current_day_phase() / 6)

//�ж��Ƿ���Բ
#define is_full_moon() (strsrch(CHINESE_D->chinese_date(time()), "ʮ����") >= 0);

//�ж��ǲ�������
#define is_weapon(ob) (mapp(ob->query("weapon_prop")))

//�ж��ǲ��ǻ���
#define is_armor(ob) (mapp(ob->query("armor_prop")))

//�ж��ǲ�������
#define is_horse(ob) (mapp(ob->query("ride")))

//�ж�Ŀ���Ƿ��ܶ���
#define cannot_move(who) (who->is_busy() || who->query_temp("no_move") || who->query_temp("pending/exercising") || who->query_temp("pending/meditating"))

//�ж�Ŀ���Ƿ���no_move
#define is_no_move(who) (who->query_temp("no_move"))

//�����ܺ�
#define total_exp(who) (who->query("combat_exp") + who->query("daoxing"))

//��Ч����
#define eff_dx(who) ((who->query("daoxing")*2 + who->query("combat_exp"))/3)

//�ַ���
#define str_split STRING->split

//message_vision��д
#define msv message_vision

//��дtranslator
#define e2c TRANSLATOR->en_to_ch

//��дdelay_destruct��1�������
#define destruct1 UTIL->delay_destruct

//ģ��C++/Java�����Ե�thisָ��
#define _this this_object()

//��ǰ���
#define _player this_player()

//��ǰ������������
#define _env environment(this_object())

//������ļ�id��Ҳ�����ļ���������·��
#define file_id(ob) UTIL->file_leaf(ob)

//�ļ��������ַ���ȫ·�������Ķ���
#define object_f string

//Ĭ��debug wizard
#define D_WIZ find_player("firefox")
