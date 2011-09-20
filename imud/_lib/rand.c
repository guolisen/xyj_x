
/********************************随机函数***********************************/

#define RAND_MAX		30000		//最大随机数(16位以内，避免乘法溢出)
#define swap2(a, b)		{mixed t = a; a = b; b = t;}

int _seed = 1;

//设置随机种子
void srand(int seed)
{
	_seed = seed % (RAND_MAX + 1);
}

//线性同余伪随机数
int rand()
{
	//3000左右的素数：30269 30389 30467 30491 30557 30839 30851 30869
	return _seed = (_seed * 30269 + 12345) % (RAND_MAX + 1);
}

//小于n的随机数
mixed random(int n)
{
	if(n < 1) n = 1;
	return rand() % n;
}

//从数组中随机选择一个元素
mixed random1(mixed* arr)
{
	return arr[random(sizeof(arr))];
}

//洗牌
int* shuffle(int* arr)
{
	int size = sizeof(arr);
	for(int i = 0; i < size; ++i) {
		int j = random(size);
		swap2(arr[i], arr[j]);
	}
	return arr;
}

//1千万次随机试验：分布78-116，还可以
int* test(int n, int times)
{
	int* arr = allocate(n);
	int a = times;
	int b = 0;
	for(int i = 0; i < times; ++i) {
		reset_eval_cost();
		arr[random(n)]++;
	}
	
	for(int i = 0; i < sizeof(arr); ++i) {
		if(arr[i] < a) a = arr[i];
		if(arr[i] > b) b = arr[i];
	}
	printf("%d %d\n", 100 * a * n / times, 100 * b * n / times); 
	return arr;
}



 