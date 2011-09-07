// by firefox 11/21/2009

//调试
#define assert(_exp) if(!(_exp)) error("assert: _exp\n")

//截断，x值如果超过m1-m2区间，则截断到m1或m2
#define truncate(x, x1, x2) (min2(max2(x, x1), x2))

//交换
#define swap2(a, b) {mixed t = a; a = b; b = t;}

//a占b的百分比，分母为零时返回0
#define percent(a, b) ((b) ? (a)*100/(b) : 0)

//轮盘概率选择
#define roulette(m) (MATH->roulette_(m))

//洗牌，使数组随机乱序
#define shuffle(arr) (MATH->shuffle_arr(arr))

//数组最后一个元素
#define arr_last(arr) (arr[sizeof(arr) - 1])

//用户名字和ID
#define name_id(who) (who->query("name") + "(" + capitalize(who->query("id")) + ")")

//用户名字和ID
#define name_id2(name, id) ((name) + "(" + capitalize(id) + ")")

//用户当前使用的第一个ID
#define first_id(who) (who->parse_command_id_list()[0])

//复制用户名和ID
#define copy_name_id(src, dst) (dst->set_name(src->name(), src->parse_command_id_list()))

//带色彩的名字
#define color_name(name, color) (or2(color, "") + name + (color ? NOR : ""))

//名字和ID等于指定的值
#define name_id_is(who, name_, id_) (who->query("name") == (name_) && who->query("id") == (id_))

//是否两者位于同一房间
#define same_env(ob1, ob2) (ob1 && ob2 && (environment(ob1) == environment(ob2)))

//判断是否在夜间
#define at_night() (NATURE_D->query_current_day_phase() / 6)

//判断是否月圆
#define is_full_moon() (strsrch(CHINESE_D->chinese_date(time()), "十五日") >= 0);

//判断是不是武器
#define is_weapon(ob) (mapp(ob->query("weapon_prop")))

//判断是不是护甲
#define is_armor(ob) (mapp(ob->query("armor_prop")))

//判断是不是坐骑
#define is_horse(ob) (mapp(ob->query("ride")))

//判断目标是否能动作
#define cannot_move(who) (who->is_busy() || who->query_temp("no_move") || who->query_temp("pending/exercising") || who->query_temp("pending/meditating"))

//判断目标是否能no_move
#define is_no_move(who) (who->query_temp("no_move"))

//经验总和
#define total_exp(who) (who->query("combat_exp") + who->query("daoxing"))

//有效道行
#define eff_dx(who) ((who->query("daoxing")*2 + who->query("combat_exp"))/3)

//字符串
#define str_split STRING->split

//message_vision缩写
#define msv message_vision

//缩写translator
#define e2c TRANSLATOR->en_to_ch

//缩写delay_destruct，1秒后销毁
#define destruct1 UTIL->delay_destruct

//模拟C++/Java等语言的this指针
#define _this this_object()

//当前玩家
#define _player this_player()

//当前对象所处环境
#define _env environment(this_object())

//对象的文件id，也就是文件名，不含路径
#define file_id(ob) UTIL->file_leaf(ob)

//文件对象，用字符串全路径描述的对象
#define object_f string

//默认debug wizard
#define D_WIZ find_player("firefox")
