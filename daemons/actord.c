// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

/*
	�籾�еĽ�ɫ
*/

mapping _objects = ([]);

//���������
mapping _files = ([
	"xia"		: X_DIR"d/psd/npc/xia",				//��ϼ
	"wukong"	: X_DIR"d/psd/npc/wukong",			//���
	"xiang"		: X_DIR"d/psd/npc/xiang",			//����
	"xt-dog"		: X_DIR"d/psd/npc/xt-dog",			//Х��Ȯ
	"hole"		: X_DIR"d/psd/obj/hole",			//�����¹ⱦ�еĶ�
	//"glass"		: X_DIR"daemons/race/glass",	//Ͷ̥�õĲ�����
]);

void create()
{
	seteuid(getuid());
}

int remove()
{
	foreach(string id, object ob in _objects) {
		if(ob) destruct(ob);
	}
	return 1;
}

//����ָ��id����Ա
object find(string id)
{
	if(!_objects[id]) {
		object ob = new(_files[id]);
		if(ob) {
			_objects[id] = ob;
		}		
	}
	return _objects[id];
}

//ˢ����Ա�Լ�λ��
void start()
{
	trace("actor start", D_WIZ);
	foreach(string id, string file in _files) {
		object ob = find(id);
		if(ob) ob->debut();
	}
}
