// by firefox 11/21/2009

//从dbase中获取一个array，如果array不存在，则建立array
mixed* query_array(object who, string prop)
{
	mixed* ret = who->query(prop);
	if(!arrayp(ret)) {
		ret = ({});
		who->set(prop, ret);
	}
	return ret;
}

//从temp dbase中获取一个array，如果array不存在，则建立array
mixed* query_temp_array(object who, string prop)
{
	mixed* ret = who->query_temp(prop);
	if(!arrayp(ret)) {
		ret = ({});
		who->set_temp(prop, ret);
	}
	return ret;
}


//从dbase中获取一个map，如果map不存在，则建立map
mapping query_map(object who, string prop)
{
	mapping ret = who->query(prop);
	if(!mapp(ret)) {
		ret = ([]);
		who->set(prop, ret);
	}
	return ret;
}

//从dbase中获取一个map，如果map不存在，则建立map
mapping query_temp_map(object who, string prop)
{
	mapping ret = who->query_temp(prop);
	if(!mapp(ret)) {
		ret = ([]);
		who->set_temp(prop, ret);
	}
	return ret;
}

//为对象设置一组属性
void set_map(object who, mapping props)
{
	foreach(mixed k, mixed v in props) {
		who->set(k, v);
	}
}

//为对象设置一组临时属性
void set_temp_map(object who, mapping props)
{
	foreach(mixed k, mixed v in props) {
		who->set_temp(k, v);
	}
}
