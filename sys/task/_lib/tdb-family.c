// by firefox 04/10/2010
// �����������ݿ�

#include "tdb.h"

mapping _data = ([]);						//�������ݿ�


//���������б�
int tdb_load(string file)
{
	mapping m = file->data();
	
	foreach(string k, mapping v in m) {
		if(k != "common") {
			_data[k] = ({0, m["common"] + m[k]});
			_data[k][0] = sort_array(keys(_data[k][1]), 1);
		}
	}
}

//��ȡ�����б�
mapping tdb_data(object who)
{
	string family = who->query("family/family_name");
	return _data[family][1];
}

//��ȡ���������б�
int* tdb_keys(object who)
{
	string family = who->query("family/family_name");
	return _data[family][0];
}

mapping tdb_family_test()
{
	tdb_load("/d/xyj_x/data/task/forces/_family");
	return _data;
}
