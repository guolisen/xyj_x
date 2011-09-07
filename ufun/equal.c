
//判断相等

int var_equal(mixed v1, mixed v2);
int map_equal(mixed m1, mixed m2);
int arr_equal(mixed* a1, mixed* a2);

//比较变量是否相等
int var_equal(mixed v1, mixed v2)
{
	string t = typeof(v1);
	if(!v1 && !v2) return 1;
	if(t != typeof(v2)) return 0;
	if(sizeof(v1) != sizeof(v2)) return 0;
	if(t == "mapping") return map_equal(v1, v2);
	if(t == "array") return arr_equal(v1, v2);
	return v1 == v2;
}

//比较mapping相等
int map_equal(mapping m1, mapping m2)
{
	foreach(mixed k, mixed v in m1) {
		if(!var_equal(v, m2[k])) return 0;
	}
	return 1;
}

//比较mapping相等
int arr_equal(mixed* a1, mixed* a2)
{
	for(int i = 0; i < sizeof(a1); ++i) {
		if(!var_equal(a1[i], a2[i])) return 0;
	}
	return 1;
}

//判断是否相等
int assert_equal(mixed a, mixed b) 
{
	if(!var_equal(a, b)) write("assert fail.\n");
}


int equal_test1()
{
	assert_equal(1, 1);
	assert_equal(0, 0);
	assert_equal(({0, 1, 2, 3}), ({0, 1, 2, 3}));
	assert_equal((["a" : 0, "b" : 1, "c" : 2]), (["a" : 0, "b" : 1, "c" : 2]));
//	assert_equal((["a" : 0, "b" : 1, "c" : 2]), (["a" : 0, "b" : 1,]));

}
