// by firefox 10/01/2010
// 西游杀-战斗进行中

#define BUFF_PROP				"buffs"				//buff属性

/*
mapping buff = ([
	"id"			: //本buff id
	"who"			: //buff的宿主玩家
	"duration"		: //buff持续时间
	"apply"			: //为玩家临时增加的属性
	"state"			: //为玩家临时增加的状态
	"dot"			: //为玩家临时增加的dot
	"msg_dot"		: //dot发作时的信息
	"msg_remove"	: //移除时的信息
]);
*/


//添加一个buff
int buff_add(mapping who, mapping buff)
{	
	string id = buff["id"];
	if(who[BUFF_PROP][id]) return 0;	//buff已经存在
	
	buff["who"] = who;
	who[BUFF_PROP][id] = buff;

	//增加apply
	if(buff["apply"]) 
		foreach(string k, int v in buff["apply"]) {
			who["apply"][k] += v;
		}
	//增加状态
	if(buff["state"])
		foreach(string k, int v in buff["state"]) {
			who["state"][k] = v;
		}
	return 1;
}

//刷新并返回buff的剩余时间
int buff_refresh(mapping buff)
{
	mapping who = buff["who"];
	if(buff["dot"]) {	//持续伤害或治疗效果
		foreach(string k, int v in buff["dot"]) {
			who[k] += v;
		}
		msv1(buff["msg_dot"], who);
	}
	if(buff["on_refresh"]) {
	}
	buff["duration"]--;
	return buff["duration"];
}

//移除一个buff
int buff_remove(mapping buff)
{
	string id = buff["id"];
	mapping who = buff["who"];

	if(buff != who[BUFF_PROP][id]) return 0;
	
	//移除apply
	if(buff["apply"]) 
		foreach(string k, int v in buff["apply"]) {
			who["apply"][k] -= v;
		}
	msv1(buff["msg_remove"], who); 
	who[BUFF_PROP][id] = 0;
}

//刷新某人的全部buff，移除过期buff
void buff_refresh_all(mapping who)
{
	foreach(mapping buff in who[BUFF_PROP]) {
		if(buff_refresh(buff) < 1) buff_remove(buff);
	}
}
