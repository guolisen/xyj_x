
//�ļ�������(fot)������Լ������Ŀ¼�ṹ�������ļ�ӳ��ɶ�����

#include <xyj_x.h>

//����id
string id()	
{ 
	return file_id(this_object());
}

//��ȡָ�����ӽڵ�
object_f child(string id)
{
	string s = base_name(this_object());
	return s + "/" + id;
}

//��ȡ���ڵ�
object_f parent()
{
	return UTIL->file_dir(this_object());
}

//������id
string parent_id()
{
	return file_id(load_object(parent()));
}

