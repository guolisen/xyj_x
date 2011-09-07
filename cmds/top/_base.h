#include <ansi.h>
#include <xyj_x.h>

#define NWIZARD			!wizardp

string* _lines;
mapping _lists;
string _arg;

mixed* _arr = allocate(1000);

int cmp_score(mixed* a, mixed* b)
{
	return b[1] - a[1];
}

//����ǰn��Ԫ��
mixed* sub_arr(mixed* arr, int n)
{
	mixed* ret = allocate(n);
	for(int i = 0; i < n; ++i) {
		ret[i] = _arr[i];
	}
	return ret;
}

//��ȡĳ�����а�
mapping query(string arg, int n)
{
	mapping list = _lists[arg];
	mixed* source = evaluate(list["source"]);
	mixed* sorted = sort_array(source, (: cmp_score :));
	int size = min2(n, sizeof(sorted));
	string* lines = allocate(size);

	for(int i = 0; i < size; ++i) {
		lines[i] = evaluate(list["format"], sorted[i], i);
	}

	return ([ "header" : list["header"], "lines" : lines ]);
}

//��ʽ���񵥵�һ�����
string format(string fmt, mixed* arr, int i)
{
	object who = arr[0];
	string* colors = ({NOR, YEL});
	string family = FAMILY->short(who);
	
	return sprintf(fmt,
		colors[i % 2],
		i + 1,
		family ? family : "����",
		name_id(who),
		arr[1],
		);
}

//�鿴�񵥺���(������)
mapping debug()
{
	return _lists;
}
