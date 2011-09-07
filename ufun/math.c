// by firefox 11/21/2009

#include <xyj_x.h>

/*****************************�������*****************************/

///��ȡ������������n���¸���pct%��Χ��
int random_pct(int n, int pct)
{
	int i = n * (100 - pct) +  random(n * pct * 2);
	return i/100;
}

///��С��m�����������ѡn��
mixed* random_int(int m, int n)
{
	int* arr = ({});
	if(n > m) return 0;
	while(sizeof(arr) < n) {
		int i = random(m);
		if(member_array(i, arr) == -1) arr += ({i});
	}
	return arr;
}

///�������������ȡn��Ԫ��
mixed* random_elem(mixed* arr, int n)
{
	mixed* dst = ({});
	if(arrayp(arr)) {
		foreach(int i in random_int(sizeof(arr), n)) {
			dst += ({ arr[i] });
		}
	}
	return dst;
}

///ϴ��С��m������
int* shuffle_int(int m)
{
	int* arr = allocate(m);
	for(int i = 0; i < m; ++i) {
		arr[i] = i;
	}
	for(int i = 0; i < m; ++i) {
		int j = random(m);
		swap2(arr[i], arr[j]);
	}
	return arr;
}

///ϴ������
mixed* shuffle_arr(mixed* arr)
{
	int m = sizeof(arr);
	for(int i = 0; i < m; ++i) {
		int j = random(m);
		swap2(arr[i], arr[j]);
	}
	return arr;
}

///�����̶ķ�ʽ���ѡ��һ��Ŀ�꣬map(Ŀ��,����)
mixed roulette_(mapping map)
{
	int sum = 0;
	int n;
	foreach(int v in values(map)) {
		sum += v;
	}
	n = random(sum);
	foreach(mixed k, int v in map) {
		n -= v;
		if(n < 0) return k;
	}
	return 0;
}

/*****************************ͳ�ƺ���*****************************/

//��ֵ�������ֵ���Ȩƽ��
mixed average(mixed* arr)
{
	int sum = 0;
	if(sizeof(arr)) return 0;

	if(intp(arr[0])) {			//ƽ��
		foreach(int v in arr) {
			sum += v;
		}
		return sum / sizeof(arr);
	}
	else if(arrayp(arr[0])) {	//��Ȩƽ��
		int sum_wei = 0;
		foreach(int* v in arr) {
			sum += v[0] * v[1];
			sum_wei += v[1];
		}
		return sum / sum_wei;
	}
	return 0;
}

/*****************************������*****************************/

mapping _unsort_map;	//����mapҪ������ȫ�ֱ���

private int _sort_map_asce(mixed key1, mixed key2)
{
	return _unsort_map[key1] <= _unsort_map[key2] ? -1 : 1;
}

private int _sort_map_desc(mixed key1, mixed key2)
{
	return _unsort_map[key1] >= _unsort_map[key2] ? -1 : 1;
}

///����map������values���������Ӧ��keys
varargs mixed* sort_map(mapping m, int desc)
{
	string fun = desc ? "_sort_map_desc" : "_sort_map_asce";
	_unsort_map = m;
	return sort_array(keys(m), fun);
}

/*****************************��������*****************************/

//����nλ�������б��е��������䣬�����������
int find_rang(int* rangs, int n)
{
	for(int i = 0; i < sizeof(rangs); ++i) {
		if(n < rangs[i]) return i;
	}
	return sizeof(rangs);
}

//������ֵn���ڵ����䣬�����������Ӧ��ֵ
mixed cvt_rang(mixed* rangs, int n)
{
	for(int i = 0; i < sizeof(rangs); ++i) {
		if(n < rangs[i][0]) return rangs[i][1];
	}
	return 0;
}