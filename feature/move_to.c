
//�ƶ�����Ŀ������ܸ��ص�һ������

int move_to(object ob)
{
	move_object(ob);
	return environment(this_object()) == ob;
}
