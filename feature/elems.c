// by firefox 11/21/2009


object* _elems = ({});


//��������Ԫ��
object* elems()
{
	return _elems;
}

//����һ���Ѿ����ڵĶ���
object push_elem(object ob)
{
	_elems += ({ ob });
	return ob;
}

//����һ���¶��󲢼��뼯��
object new_elem(string file)
{
	object ob = new(file);
	reset_eval_cost();
	return push_elem(ob);
}

//�������������������Ӷ���
int remove()
{
	foreach(object ob in elems()) {
		if(ob) destruct(ob);
	}
	//this_object()->remove();
	return 0;
}
