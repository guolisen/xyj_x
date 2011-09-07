// by firefox 10/01/2010
// ����ɱ-ս��������

#define BUFF_PROP				"buffs"				//buff����

/*
mapping buff = ([
	"id"			: //��buff id
	"who"			: //buff���������
	"duration"		: //buff����ʱ��
	"apply"			: //Ϊ�����ʱ���ӵ�����
	"state"			: //Ϊ�����ʱ���ӵ�״̬
	"dot"			: //Ϊ�����ʱ���ӵ�dot
	"msg_dot"		: //dot����ʱ����Ϣ
	"msg_remove"	: //�Ƴ�ʱ����Ϣ
]);
*/


//���һ��buff
int buff_add(mapping who, mapping buff)
{	
	string id = buff["id"];
	if(who[BUFF_PROP][id]) return 0;	//buff�Ѿ�����
	
	buff["who"] = who;
	who[BUFF_PROP][id] = buff;

	//����apply
	if(buff["apply"]) 
		foreach(string k, int v in buff["apply"]) {
			who["apply"][k] += v;
		}
	//����״̬
	if(buff["state"])
		foreach(string k, int v in buff["state"]) {
			who["state"][k] = v;
		}
	return 1;
}

//ˢ�²�����buff��ʣ��ʱ��
int buff_refresh(mapping buff)
{
	mapping who = buff["who"];
	if(buff["dot"]) {	//�����˺�������Ч��
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

//�Ƴ�һ��buff
int buff_remove(mapping buff)
{
	string id = buff["id"];
	mapping who = buff["who"];

	if(buff != who[BUFF_PROP][id]) return 0;
	
	//�Ƴ�apply
	if(buff["apply"]) 
		foreach(string k, int v in buff["apply"]) {
			who["apply"][k] -= v;
		}
	msv1(buff["msg_remove"], who); 
	who[BUFF_PROP][id] = 0;
}

//ˢ��ĳ�˵�ȫ��buff���Ƴ�����buff
void buff_refresh_all(mapping who)
{
	foreach(mapping buff in who[BUFF_PROP]) {
		if(buff_refresh(buff) < 1) buff_remove(buff);
	}
}
