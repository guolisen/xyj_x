
//文件对象树(fot)，根据约定，按目录结构，将其文件映射成对象树

#include <xyj_x.h>

//对象id
string id()	
{ 
	return file_id(this_object());
}

//获取指定的子节点
object_f child(string id)
{
	string s = base_name(this_object());
	return s + "/" + id;
}

//获取父节点
object_f parent()
{
	return UTIL->file_dir(this_object());
}

//父对象id
string parent_id()
{
	return file_id(load_object(parent()));
}

