// by firefox 11/21/2009


object* _elems = ({});


//返回所有元素
object* elems()
{
	return _elems;
}

//加入一个已经存在的对象
object push_elem(object ob)
{
	_elems += ({ ob });
	return ob;
}

//创建一个新对象并加入集合
object new_elem(string file)
{
	object ob = new(file);
	reset_eval_cost();
	return push_elem(ob);
}

//对象析构，销毁所有子对象
int remove()
{
	foreach(object ob in elems()) {
		if(ob) destruct(ob);
	}
	//this_object()->remove();
	return 0;
}
