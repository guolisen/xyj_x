// by firefox 11/21/2009

//���Զ����صĲ�����Ʒ���߿ɺϲ���Ʒ

string query_autoload() 
{
	return this_object()->query_amount() + ""; 
}

void autoload(string param)
{
	int n;
	if( sscanf(param, "%d", n) == 1 && n > 0) this_object()->set_amount(n);
}
