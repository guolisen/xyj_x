
//移动对象到目标里，不受负重等一切限制

int move_to(object ob)
{
	move_object(ob);
	return environment(this_object()) == ob;
}
