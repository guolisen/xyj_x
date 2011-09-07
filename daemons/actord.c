// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

/*
	剧本中的角色
*/

mapping _objects = ([]);

//出场对象表
mapping _files = ([
	"xia"		: X_DIR"d/psd/npc/xia",				//紫霞
	"wukong"	: X_DIR"d/psd/npc/wukong",			//悟空
	"xiang"		: X_DIR"d/psd/npc/xiang",			//香香
	"xt-dog"		: X_DIR"d/psd/npc/xt-dog",			//啸天犬
	"hole"		: X_DIR"d/psd/obj/hole",			//埋有月光宝盒的洞
	//"glass"		: X_DIR"daemons/race/glass",	//投胎用的玻璃杯
]);

void create()
{
	seteuid(getuid());
}

int remove()
{
	foreach(string id, object ob in _objects) {
		if(ob) destruct(ob);
	}
	return 1;
}

//查找指定id的演员
object find(string id)
{
	if(!_objects[id]) {
		object ob = new(_files[id]);
		if(ob) {
			_objects[id] = ob;
		}		
	}
	return _objects[id];
}

//刷新演员以及位置
void start()
{
	trace("actor start", D_WIZ);
	foreach(string id, string file in _files) {
		object ob = find(id);
		if(ob) ob->debut();
	}
}
