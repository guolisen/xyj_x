#ifndef IMUD_UTIL_S_H_INCLUDED
#define IMUD_UTIL_S_H_INCLUDED
// by firefox 04/16/2011
// server util

mapping _g;						//全局数据


//获取游戏数据
mixed g()
{
	return _g;
}

//服务器接受并分发请求
varargs int recv_req(string verb, mapping info)
{
	
	mixed* ret = evaluate(verb, info);

	if(mapp(ret)) {

		
	} 
	else if(intp(ret)) {

	}
	
	//编码成字符串

	//反馈请求结果

	//分发给所有客户端

	verb = ret["verb"] ? ret["verb"] : (verb + "on_");

	{
		string client = __DIR__"0";
		client->recv_req(verb, ret);		//反馈
	}

	return 1;
}

///向客户端发送通知信息
varargs mapping notify(mapping dst, mixed msg)
{
	mapping m = ([
		"verb"		: "on_notify"
	]);
	
}


#endif

