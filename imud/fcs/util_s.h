#ifndef IMUD_UTIL_S_H_INCLUDED
#define IMUD_UTIL_S_H_INCLUDED
// by firefox 04/16/2011
// server util

mapping _g;						//ȫ������


//��ȡ��Ϸ����
mixed g()
{
	return _g;
}

//���������ܲ��ַ�����
varargs int recv_req(string verb, mapping info)
{
	
	mixed* ret = evaluate(verb, info);

	if(mapp(ret)) {

		
	} 
	else if(intp(ret)) {

	}
	
	//������ַ���

	//����������

	//�ַ������пͻ���

	verb = ret["verb"] ? ret["verb"] : (verb + "on_");

	{
		string client = __DIR__"0";
		client->recv_req(verb, ret);		//����
	}

	return 1;
}

///��ͻ��˷���֪ͨ��Ϣ
varargs mapping notify(mapping dst, mixed msg)
{
	mapping m = ([
		"verb"		: "on_notify"
	]);
	
}


#endif

