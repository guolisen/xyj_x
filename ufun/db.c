// by firefox 11/21/2009

//��dbase�л�ȡһ��array�����array�����ڣ�����array
mixed* query_array(object who, string prop)
{
	mixed* ret = who->query(prop);
	if(!arrayp(ret)) {
		ret = ({});
		who->set(prop, ret);
	}
	return ret;
}

//��temp dbase�л�ȡһ��array�����array�����ڣ�����array
mixed* query_temp_array(object who, string prop)
{
	mixed* ret = who->query_temp(prop);
	if(!arrayp(ret)) {
		ret = ({});
		who->set_temp(prop, ret);
	}
	return ret;
}


//��dbase�л�ȡһ��map�����map�����ڣ�����map
mapping query_map(object who, string prop)
{
	mapping ret = who->query(prop);
	if(!mapp(ret)) {
		ret = ([]);
		who->set(prop, ret);
	}
	return ret;
}

//��dbase�л�ȡһ��map�����map�����ڣ�����map
mapping query_temp_map(object who, string prop)
{
	mapping ret = who->query_temp(prop);
	if(!mapp(ret)) {
		ret = ([]);
		who->set_temp(prop, ret);
	}
	return ret;
}

//Ϊ��������һ������
void set_map(object who, mapping props)
{
	foreach(mixed k, mixed v in props) {
		who->set(k, v);
	}
}

//Ϊ��������һ����ʱ����
void set_temp_map(object who, mapping props)
{
	foreach(mixed k, mixed v in props) {
		who->set_temp(k, v);
	}
}
