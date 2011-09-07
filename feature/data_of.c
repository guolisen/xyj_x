
#include <xyj_x.h>

//和dbase冲突

string _data_of_prop;

//设置属性名
void set_data_prop(string prop)
{
	_data_of_prop = prop;
}

//设置属性名
string get_data_prop()
{
	return _data_of_prop;
}

//查询目标的属性数据
varargs mixed data_of(object who, string prop)
{
	string full_prop = _data_of_prop + "/" + prop;
	return prop ? who->query(full_prop) : DB->query_map(who, _data_of_prop);
}

//查询目标的属性数据
varargs mixed temp_data_of(object who, string prop)
{
	string full_prop = _data_of_prop + "/" + prop;
	return prop ? who->query_temp(full_prop) : DB->query_temp_map(who, _data_of_prop);
}

//增加目标的属性数据
void add(object who, string prop, mixed value)
{
	string full_prop = _data_of_prop + "/" + prop;
	who->add(full_prop, value);
}

//增加目标的属性数据
void set_data(object who, mapping data)
{	
	who->set(_data_of_prop, data);
}

//增加目标的临时属性数据
void set_temp_data(object who, mapping data)
{	
	who->set_temp(_data_of_prop, data);
}

