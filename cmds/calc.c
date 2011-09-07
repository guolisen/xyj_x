// by firefox 11/21/2009

#include <ansi.h>

int sum(int n)
{
	return n*(n+1)*(2*n+1)/6;
}

int main(object me, string arg)
{
	int from, to;
	if(arg && sscanf(arg, "%d %d", from, to) == 2) {
		int cost = sum(to) - sum(from);
		printf("ĞèÒªÇ±ÄÜ£º%d\n", cost / 20);
		return 1;
	}
	return 0;
}
