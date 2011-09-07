

mapping m1 = (["a" : 10, "b" : 2]);
mapping m2 = (["a" : m1, "b" : 2]);

mixed* arr = ({ m2 });

void create()
{
	

	printf("arr: %d\n", arr[0]["a"]["a"]);

	arr -= ({ m2 });
	printf("arr: %d\n", sizeof(arr));
	printf("arr: %d\n", m2["a"]["a"]);
}