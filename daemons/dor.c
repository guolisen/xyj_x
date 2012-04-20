// by firefox 11/21/2009
// ��̬�����滻

#include <xyj_x.h>
#include <ansi.h>

#define TQ			TASK_DIR"quest/npc/"
#define KF			"/d/kaifeng/npc/"

//�滻�����(�¶��󣬷��䣬�϶���)
mapping _replaces = ([

	//��������
	"npc-cien"	: ({ TASK_DIR"forces/cien/npc-cien",	"/d/eastway/ciensi", 0 }),
	
	//��������
	"npc-yuan"	: ({ TASK_DIR"mieyao/npc/npc-yuan", "/d/city/tianjiantai", "/d/city/npc/yuantiangang" }),
	"npc-li"		: ({ TASK_DIR"mieyao/npc/npc-li", "/d/dntg/yunlou/yunloutai", "/d/dntg/yunlou/npc/litianwang" }),	
	
	//��������
	"npc-food"	: ({ TQ"npc-food", "/d/kaifeng/shuaifu", KF"zhubajie" }),
	"npc-cloth"	: ({ TQ"npc-cloth", "/d/kaifeng/xianglan", KF"xianglan" }),
	"npc-armor"	: ({ TQ"npc-armor",	"/d/kaifeng/kuijia", KF"xpo" }),
	"npc-weapon"	: ({ TQ"npc-weapon", "/d/kaifeng/bingqi", KF"xgong" }),	

	"npc-give"	: ({ TQ"npc-give", "/d/kaifeng/pudu", KF"yin" }),
	"npc-ask"	: ({ TQ"npc-ask", "/d/kaifeng/jixian", KF"chen" }),
	"npc-kill"	: ({ TQ"npc-kill", "/d/kaifeng/ee", KF"hu" }),	

	"emperor"	: ({ TQ"emperor", "/d/huanggong/dadian", "/d/huanggong/npc/emperor" }),	
	//���幬
	"sanxin"	: ({ TQ"cancel", "/d/kaifeng/sanxin", 0 }),
	"ningxin"	: ({ TQ"cancel", "/d/kaifeng/ningxin", 0 }),
	"qingxin"	: ({ TQ"cancel", "/d/kaifeng/qingxin", 0 }),
	"jingxin"	: ({ TQ"cancel", "/d/kaifeng/jingxin", 0 }),
]);

void create()
{
	seteuid(getuid());	
}

//ˢ�������
void start___()
{
	trace("dor start", D_WIZ);
	foreach(string k, string* v in _replaces) {		
		string file = v[0];
		string room = v[1];
		string old = v[2];		
		
		mapping m1 = DB->query_map(room, "objects");
		mapping m2 = DB->query_temp_map(room, "objects");

		//�����϶���
		if(old) {
			//trace("old", ff);
			if(m1[old]) {
				map_delete(m1, old);
			}
			if(m2[old]) {
				if(objectp(m2[old])) destruct(m2[old]);
				else if(sizeof(m2[old])) {
					foreach(object ob in m2[old]) {
						destruct(ob);
					}
				}
				map_delete(m2, old);
			}
		}
		//����¶���
		if(!m1[file]) {
			object ob = room->make_inventory(file);
			m1[file] = 1;
			m2[file] = ob;
		}
		reset_eval_cost();
	}
}

