// by firefox 03/27/2010

// 注意，加入一个汉字，一定要用PY检查是否有该汉字的拼音。
// 如果没有，要添加拼音表

#include <xyj_x.h>

string* _colors = ({ "赤", "黄", "青", "金", "雪", "紫", "黑", "白", "银", "火", "灰" });

mapping _components = ([
	"顶"	: ({ "花", }),
	"头"	: ({ "巨", "双", "三", "六", "九", "癞", "秃", "焦", }),
	"脸"	: ({ "巨", "长", "花", }),
	"角"	: ({ "巨", "长", "短", "独", "断", }),
	"额"	: ({ "烂", }),
	"嘴"	: ({ "大", "长", "短", "噘", "歪", }),
	"耳"	: ({ "大", "三", "六", "九", }),
	"鼻"	: ({ "长", "短", "卷", "缺", }),
	"目"	: ({ "多", "巨", "三", "六", "九", "百", "千", "电", }),
	"瞳"	: ({ "碧", "幽", }),
	"眼"	: ({ "碧", "独", "四", "瞎", "盲", "蒙",  "邪", "斜", "对", "黯", "细", }),
	"睛"	: ({ "吊", "黯", }),
	"腮"	: ({ "鼓", }),

	"牙"	: ({ "长", "短", "大", "断", "尖", }),
	"齿"	: ({ "巨", "断", "碎", "利", "剑", "巨", "皓", "钩", "错", }),

	"颈"	: ({ "长", "短", "曲", }),
	"背"	: ({ "铁", "隆", "弓", }),
	"脊"	: ({ "铁", "刺", }),
	"甲"	: ({ "铁", "裂", "残", }),

	"腰"	: ({ "粗", "细", "花", }),
	"腹"	: ({ "花", "鼓", }),

	"臂"	: ({ "长", "短", "八", "断", }),
	"腿"	: ({ "瘸", "长", "短", }),
	"翅"	: ({ "折", "断", }),
	"翼"	: ({ "折", "断", "三", "六", "九", "长", "短", }),
	"鳍"	: ({ "长", "短", "断", }),

	"足"	: ({ "三", "百", "千", }),
	"脚"	: ({ "大", "长", "短", "高", "矮", }),
	"趾"	: ({ "长", "短", "碎", "残", }),
	"爪"	: ({ "利", "铁", "残", "钝", }),
	"蹄"	: ({ "铁", "碎", "尖", "裂", "巨", }),

	"尾"	: ({ "长", "短", "大", "小", "断", "双", "七", "九", "巨", "焦",}),

	"毛"	: ({ "长", "短", "蓬", "脱", "锦", "卷", "曲", "焦", }),
	"鬃"	: ({ "长", "短", "刚", "剑", "软"}),
	"鳞"	: ({ "花", "刺", "亮", }),
	"羽"	: ({ "碧", "翠", "长", "残", "花", }),
	
	"斑"	: ({ "花", "霜", }),
]);

mapping _animal_str = ([
	//兽
	"头额耳鼻目瞳眼睛牙齿颈背脊腰腿脚尾" : ([
		"毛斑爪" : ([
			"狮"	: "猱",
			"虎"	: "老/斑斓/跳山/插翅",
			"豹"	: "山/花/草/金钱",
			"狼"	: "苍/黄鼠",
			"熊"	: "狗",
			"狈"	: "",
			"豺"	: "",
			"獭"	: "",
			"狐"	: "花/双面/玉面",
			"狸"	: "伏/河/海/狐",
			"獾"	: "",
			"猁"	: "猞/狮",
			"貂"	: "紫金/花狐",
			"鼠"	: "金鼻白毛/黄毛貂",
			"罴"	: "",
			"猊"	: "狻",
			"犼"	: "",
			"犴"	: "",
			"猫"	: "山/野",
			"兔"	: "野/玉",
		]),
		"毛斑蹄鬃" : ([
			"驴"	: "野/毛/叫",
			"马"	: "野",
			"猪"	: "豪/野",
		]),
		"毛斑蹄角" : ([
			"牛"	: "野/水/牦",
			"羊"	: "山/野/羚",
			"鹿"	: "野/马/梅花",
			"麂"	: "",
			"獐"	: "香",
			"羚"	: "",
		]),
		"蹄" : ([
			"象"	: "抟", 
		]),
		"蹄角" : ([
			"兕"	: "",
			"犀"	: "望月/兕/牯/斑/胡冒/堕罗/通天花文",
		]),
	]),
	//灵长
	"臂腿尾毛"	: ([
		"脸"	: ([
			"猿"	: "",
			"猴"	: "马/猕/猿/灵明石/赤尻马/通臂猿/六耳猕",
		]),
		"背"	: ([
			"猩猩"	: "银背大",
		]),
	]),
	//鸟
	"头嘴背翅翼尾羽斑" : ([
		"颈顶"	: ([
			"鹤"	: "丹顶",
			"鹭"	: "苍/绿",
		]),
		"趾爪"	: ([
			"鸡"	: "山/野/稚/田",
			"鹏"	: "金翅大",
			"孔雀"	: "",
			"雕"	: "山/花",
			"鹰"	: "苍",
			"雀"	: "云",
			"鸥"	: "贼",
			"鹫"	: "秃",
			"鹊"	: "喜",
		]),
	]),
	//鱼&两栖&爬行
	"头目眼腹" : ([
		"鳞腮鳍脊" : ([
			"鱼"	: "鲇/鲤/墨/鲫/鲈/狗/剑/鳐",
			"鲢"	: "花",
			"鲨"	: "大白",
			"鳠"	: "",
			"鲭"	: "",
			"鲌"	: "",
			"鳇"	: "",
		]),
		"甲背" : ([
			"鼍"	: "",
			"鳖"	: "土",
			"鳌"	: "",
			"龟"	: "铁背/绿毛",
			"蟹"	: "螃/河/海/六螯/九螯/六跪",
		]),
		"足" : ([
			"蟾"	: "",
			"虾"	: "",
		]),
		"齿牙斑"	: ([
			"蟒"	: "",
			"蛇"	: "蟒/水/花/赤练/金环/银环/白花",
		]),
	]),
	//虫
	"头目腹"	: ([
		"翅"	: ([
			"蝗"	: "飞",
			"蚁"	: "飞",
			"蜢"	: "蚱",
			"蜂"	: "密/马/细腰",
			"蚊"	: "花脚",
		]),
		"足" : ([
			"蛛"	: "",
			"蝎"	: "",
			"蜈蚣"	: "",
			"虫"	: "蝗/臭/大青",
		]),
	]),
]);


string *names4 = ({
		"蝎子",
		"蟾蜍",
		"跳蚤",
		"虱子",
		"狮子",
		"蜘蛛",
		"刺猬",
		"狒狒",
		"白骨",	
});


mixed* _animals = ({});

void create()
{
	foreach(string s1, mapping m1 in _animal_str) {		//s1动物器官1
		foreach(string s2, mapping m2 in m1) {			//s2动物器官2			
			foreach(string s3, string s4 in m2) {		//s3动物名，s4动物修饰语
				//printf("%s %s %s %s\n", s1, s2, s3, s4);
				_animals += ({({s3, explode(s4, "/") + _colors, s1 + s2})});
			}
		}
	}
}

mixed* rnd1()
{    
    mixed* arr = _animals[random(sizeof(_animals))];
	string first = arr[1][random(sizeof(arr[1]))];
    string last = random(2) ? "精" : "怪";
	string name = first + arr[0] + last;
	string py1 = PY->cvt_str(first + arr[0]);
	string py2 = PY->cvt_str(last);
	string *id = ({py1 + " " + py2, py2});
	//printf("%s(%s)\n", name, id[0]);
	return ({ name, id });
}

mixed* rnd2()
{    
    mixed* arr = _animals[random(sizeof(_animals))];
	int n = random(sizeof(arr[2]) / 2);
	string component = arr[2][n*2 .. n*2 + 1];
	string* prefixes = _components[component];

	string* first_list = prefixes ? (prefixes + _colors) : _colors;
	string first = first_list[random(sizeof(first_list))];

	string name = first + component + arr[0];
	string py1 = PY->cvt_str(first + component);
	string py2 = PY->cvt_str(arr[0]);
	string *id = ({py1 + " " + py2, py2});
	//printf("%s(%s)\n", name, id[0]);
	return ({ name, id });
}

mixed* pick(int type)
{
	if(type == 1) return rnd1();
	if(type == 2) return rnd2();
	if(type == 3) return random(15) ? rnd2() : rnd1();
	return 0;
}

//检查拼音
void check_py()
{
	//动物及器官
	foreach(string s1, mapping m1 in _animal_str) {		//s1动物器官1
		PY->cvt_str(s1);
		foreach(string s2, mapping m2 in m1) {			//s2动物器官2
			PY->cvt_str(s2);
			foreach(string s3, string s4 in m2) {		//s3动物名，s4动物修饰语
				PY->cvt_str(s3);
				foreach(string s5 in explode(s4, "/")) {
					PY->cvt_str(s5);
				}
			}
		}
		reset_eval_cost();
	}
	//器官修饰
	foreach(string k, string v in _components) {
		PY->cvt_str(k);
		foreach(string str in v) {
			PY->cvt_str(str);
		}
		reset_eval_cost();
	}
	write("OK.\n");
}

int test1()
{
	int sum = 0;
	printf("\n动物有%d种：\n", sizeof(_animals));
	foreach(mixed* arr in _animals) {
		foreach(string s in arr[1]) {
			printf(s + arr[0] + "\n");
			PY->cvt_str(s + arr[0]);
			sum++;
		}
	}
	printf("共计%d种一类组合。\n", sum);
}

int test2()
{
	int sum = 0;
	printf("\n动物有%d种：\n", sizeof(_animals));
	foreach(mixed* arr in _animals) {
		int n1 = sizeof(arr[2]) / 2;
		for(int i = 0; i < n1; ++i) {
			string component = arr[2][i*2 .. i*2 + 1];
			string* prefixes = _components[component];
			string* first_list = prefixes ? (prefixes + _colors) : _colors;
			sum += sizeof(first_list);	
		}
	}
	printf("共计%d种二类组合。\n", sum);
}

//计算怪重名概率
float p(int n, int m)
{
	float s = 1;
	for(int i = 0; i < m; ++i) {
		s *= n - i;
		s /= n;
	}
	//write(s + "\n");	
	return s;
}

//15000种怪，随机抽400个，无重名的概率低于0.5%，重名无法避免
int test3()
{
	printf("怪名字总数15000,随机出去m个，无重名几率\n");
	for(int i = 100; i < 1000; i += 100)
		printf("%-d\t%f\n", i, p(15000, i));
}

