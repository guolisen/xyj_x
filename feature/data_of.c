
#include <xyj_x.h>

//��dbase��ͻ

string _data_of_prop;

//����������
void set_data_prop(string prop)
{
	_data_of_prop = prop;
}

//����������
string get_data_prop()
{
	return _data_of_prop;
}

//��ѯĿ�����������
varargs mixed data_of(object who, string prop)
{
	string full_prop = _data_of_prop + "/" + prop;
	return prop ? who->query(full_prop) : DB->query_map(who, _data_of_prop);
}

//��ѯĿ�����������
varargs mixed temp_data_of(object who, string prop)
{
	string full_prop = _data_of_prop + "/" + prop;
	return prop ? who->query_temp(full_prop) : DB->query_temp_map(who, _data_of_prop);
}

//����Ŀ�����������
void add(object who, string prop, mixed value)
{
	string full_prop = _data_of_prop + "/" + prop;
	who->add(full_prop, value);
}

//����Ŀ�����������
void set_data(object who, mapping data)
{	
	who->set(_data_of_prop, data);
}

//����Ŀ�����ʱ��������
void set_temp_data(object who, mapping data)
{	
	who->set_temp(_data_of_prop, data);
}

