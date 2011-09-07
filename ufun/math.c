// by firefox 11/21/2009

#include <xyj_x.h>

/*****************************随机函数*****************************/

///获取随机数，结果在n上下浮动pct%范围内
int random_pct(int n, int pct)
{
	int i = n * (100 - pct) +  random(n * pct * 2);
	return i/100;
}

///从小于m的整数中随机选n个
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

///从数组中随机抽取n个元素
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

///洗牌小于m的整数
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

///洗牌数组
mixed* shuffle_arr(mixed* arr)
{
	int m = sizeof(arr);
	for(int i = 0; i < m; ++i) {
		int j = random(m);
		swap2(arr[i], arr[j]);
	}
	return arr;
}

///按轮盘赌方式随机选择一个目标，map(目标,概率)
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

/*****************************统计函数*****************************/

//均值，数组均值或加权平均
mixed average(mixed* arr)
{
	int sum = 0;
	if(sizeof(arr)) return 0;

	if(intp(arr[0])) {			//平均
		foreach(int v in arr) {
			sum += v;
		}
		return sum / sizeof(arr);
	}
	else if(arrayp(arr[0])) {	//加权平均
		int sum_wei = 0;
		foreach(int* v in arr) {
			sum += v[0] * v[1];
			sum_wei += v[1];
		}
		return sum / sum_wei;
	}
	return 0;
}

/*****************************排序函数*****************************/

mapping _unsort_map;	//排序map要借助的全局变量

private int _sort_map_asce(mixed key1, mixed key2)
{
	return _unsort_map[key1] <= _unsort_map[key2] ? -1 : 1;
}

private int _sort_map_desc(mixed key1, mixed key2)
{
	return _unsort_map[key1] >= _unsort_map[key2] ? -1 : 1;
}

///排序map，根据values排序，输出对应的keys
varargs mixed* sort_map(mapping m, int desc)
{
	string fun = desc ? "_sort_map_desc" : "_sort_map_asce";
	_unsort_map = m;
	return sort_array(keys(m), fun);
}

/*****************************其他函数*****************************/

//搜索n位于区间列表中的所属区间，返回区间序号
int find_rang(int* rangs, int n)
{
	for(int i = 0; i < sizeof(rangs); ++i) {
		if(n < rangs[i]) return i;
	}
	return sizeof(rangs);
}

//搜索数值n所在的区间，并返回区间对应的值
mixed cvt_rang(mixed* rangs, int n)
{
	for(int i = 0; i < sizeof(rangs); ++i) {
		if(n < rangs[i][0]) return rangs[i][1];
	}
	return 0;
}