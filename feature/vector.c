
//������������C++�е�vector

mixed* _vec_elems = ({});


//ȫ��Ԫ��
mixed* elems()
{
	return _vec_elems;
}

//Ԫ������
int size()
{
	return sizeof(_vec_elems);
}

//���Ԫ��
void clear()
{
	_vec_elems = ({});
}

//���Ԫ��
void push_back(mixed elem)
{
	_vec_elems += ({ elem });
}

//��Ӷ��Ԫ��Ԫ��
void push_backs(mixed* arr)
{
	_vec_elems += arr;
}

