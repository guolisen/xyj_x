
//向量，类似于C++中的vector

mixed* _vec_elems = ({});


//全部元素
mixed* elems()
{
	return _vec_elems;
}

//元素数量
int size()
{
	return sizeof(_vec_elems);
}

//清空元素
void clear()
{
	_vec_elems = ({});
}

//添加元素
void push_back(mixed elem)
{
	_vec_elems += ({ elem });
}

//添加多个元素元素
void push_backs(mixed* arr)
{
	_vec_elems += arr;
}

