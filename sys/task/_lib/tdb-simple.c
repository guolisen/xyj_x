// by firefox 04/10/2010
// ���������ݿ�

#include "tdb.h"

mapping _data;						//�������ݿ�
int* _keys;


//���������б��ɱ���д
int tdb_load(string file)
{
	_data = ([]) + file->data();		//����һ������
	_keys = sort_array(keys(_data), 1);
}

//��ȡ�����б�
mapping tdb_data(object who)
{
	return _data;
}

//��ȡ���������б�
int* tdb_keys(object who)
{
	return _keys;
}

