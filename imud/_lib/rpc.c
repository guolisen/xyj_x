

int _seed = 1;

//设置随机种子
void srand(int seed)
{
	_seed = seed % (RAND_MAX + 1);
}



 