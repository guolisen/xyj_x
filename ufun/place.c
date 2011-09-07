// by firefox 03/27/2010

#include <xyj_x.h>

#define MAX_TIMES			30	//寻找房间最大重试次数

mixed* _dirs = ({
	({
		"/d/city",
		//"/d/jjf",
		"/d/westway",
		"/d/kaifeng",
		"/d/lingtai",
		"/d/moon",
		"/d/gao",
		//"/d/dntg/hgs", 
		"/d/sea", 
		"/d/nanhai", 
		"/d/eastway",
		"/d/ourhome/honglou", 
	}),
	({
		"/d/xueshan",
		"/d/qujing/wuzhuang", 
		"/d/qujing/baotou", 
		"/d/qujing/baoxiang", 
		"/d/qujing/bibotan",
		"/d/qujing/biqiu",
		"/d/qujing/chechi",
		"/d/qujing/dudi",
		"/d/qujing/fengxian",
		"/d/qujing/firemount",
		"/d/qujing/jilei",
		"/d/qujing/jindou",
		//"/d/qujing/jingjiling",
		"/d/qujing/jinping",
		"/d/qujing/jisaiguo",
		"/d/qujing/maoying",
		"/d/qujing/nuerguo",
		"/d/qujing/pingding",
		"/d/qujing/pansi",
		"/d/qujing/tongtian",
		"/d/qujing/qilin",
		"/d/qujing/qinfa",
		"/d/qujing/qinglong",
		"/d/qujing/tianzhu",
		//"/d/qujing/wudidong",
		"/d/qujing/wuji",
		"/d/qujing/xiaoxitian",
		"/d/qujing/yinwu",
		"/d/qujing/yuhua",
		"/d/qujing/zhujie",
		"/d/qujing/zhuzi",
		"/d/penglai",
		// "/d/pantao",
	}),
	({
		"/d/death",  
		"/d/meishan",
		"/d/qujing/lingshan",
	}),
});


//随机选择房间，在一张地图上，忽略安全区/密室
object random_room1(string dir)
{
	mixed* files = get_dir(dir + "/*.c", -1);
	for(int i = 0; i < MAX_TIMES; i++) {
		int j = random(sizeof(files));
		if( files[j][1] > 0 ) {
			object room = load_object(dir + "/" + files[j][0]);
			mixed exits;
			if (!room
				|| room->query("no_fight")
				|| room->query("no_magic")
				|| room->query("no_mieyao")
				|| !(exits = room->query("exits"))
				|| sizeof(exits) < 1)
				continue;
			return room;
		}
	}
	return 0;
}

//随机选择房间，在一组地图上
object random_room2(string* dirs)
{
	if(sizeof(dirs)) {
		string dir = dirs[random(sizeof(dirs))];
		return random_room1(dir);
	}
	return 0;
}

//随机选择房间，在预定义的一组地图上
object random_room3(int map_index)
{
	string* dir = ({});
	for(int i = 0; i <= map_index; ++i)
		dir += _dirs[i];
	return random_room2(dir);
}

//把目标随机仍到预定义的一组地图上
object random_drop(object me, int map_index)
{
	object room = random_room3(map_index);
	if(room && me->move(room)) {
		message_vision("$N走了过来。\n", me);
		return room;
	}
	return 0;
}

void test()
{
	random_drop(this_player(), 2);
}

