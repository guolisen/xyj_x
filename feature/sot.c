
#include <xyj_x.h>

//静态对象树
//todo:需要重新设计

mixed* _sot_tab = ({});
string _sot_parent;

//获取获取父节点
object_f parent()
{
	return _sot_parent;
}

//设置父节点
object_f set_parent(object_f parent)
{
	_sot_parent = parent;
}

//全部KEY
string* keys()
{
	object_f* arr = allocate(sizeof(_sot_tab));
	for(int i = 0; i < sizeof(arr); ++i) {
		arr[i] = _sot_tab[i][0];
	}
	return arr;
}

//全部成员
object_f* elems()
{
	object_f* arr = allocate(sizeof(_sot_tab));
	for(int i = 0; i < sizeof(arr); ++i) {
		arr[i] = _sot_tab[i][1];
	}
	return arr;
}

//获取成员 - 指定索引
object_f at(int i) 
{
	if(i >= 0 && i < sizeof(_sot_tab)) 
		return _sot_tab[i][1];
	return 0;
}

//获取成员 - 指定ID
object_f find(string id)
{
	foreach(mixed* arr in _sot_tab) {
		if(arr[0] == id) return arr[1];
	}
	return 0;
}

//获取成员 - 指定ID
varargs object_f find2(string id1, string id2)
{
	object_f f = find(id1);
	if(id2) f = f->find(id2);
	return f;
}

//获取的成员 - 指定索引/ID
object_f elem(mixed i)
{
	if(intp(i)) return at(i);
	return find(i);
}

//获取子孙成员
object_f child(string path)
{
	mixed ob = _this;
	foreach(string id in str_split(path, '/')) {
		ob = ob->elem(id);
		if(!ob) break;
	}
	return ob;
}

//从后面追加对象信息
void append(string id, string file)
{
	_sot_tab += ({ ({ id, file }) });
	file->set_parent(__FILE__);
}

/*
void create()
{
	append("id0", "file0");
	append("id1", "file1");
	append("id2", "file2");
}
*/
mixed sot_test()
{
	append("id0", __FILE__);
	append("id2", __FILE__);
	return _sot_tab;

}