// by firefox 06/21/2010

#include <xyj_x.h>
#include <ansi.h>

/*
	转世投胎

	- 投胎要取消出家/剃度/法名，清空任务列表
*/

#define REI_PROP		XYJ_X"/rei"		//转世属性
#define	MIN_EXP			(3*M)			//投胎exp下限
#define	MIN_MANA		3000			//投胎法力/内力下限，用于限制玩家skill

string* _bak_prop = ({	//需要备份的前生数据
	"mud_age",
	"combat_exp",	"daoxing",	"potential",
});

string* _del_prop = ({	//需要删除的前生数据

	"death",			//死亡损失
	"family",
	"betray",			//判师记录

	"force",	"max_force",	"maximum_force",	"force_factor",
	"mana",		"max_mana",		"maximum_mana",		"mana_factor",

	"bellicosity",
	"learned_points",

	"life",				//寿命&永生
	"rsg_eaten",
	
	"spell_qiankun_on",
});

void create()
{
	seteuid(getuid());
}

//获取转世信息数组
mixed* query(object who)
{
	return DB->query_array(who, REI_PROP);
}

//计算转世的总exp
private int exp_sum(object who)
{
	int sum = 0;
	mapping* arr = query(who);
	foreach(mapping m in arr) {
		sum += m[CEXP] + m[DEXP] + m[PEXP]*4;
	}
	return sum;
}

//转世条件，法力不小于规定值，历次转世的exp均值不小于规定值
int precondition(object who)
{
	int n = sizeof(query(who)) + 1;
	int mana = who->query("max_mana") + who->query("max_force");
	int sum = exp_sum(who);
	sum += total_exp(who) + who->query(PEXP)*4;

	return mana/2 >= MIN_MANA
		&& sum/3/n >= MIN_EXP;
}

//列出转世履历
void list(object who)
{
	mapping* arr = query(who);
	write("转世履历：\n");
	for(int i = 0; i < sizeof(arr); ++i) {
		printf("%2d:   %s\n", i, or2(arr[i]["name"], "人类"));
	}
}

//备份并复位属性
private void reset_prop(object who)
{
	//备份关键属性
	mapping bak = ([]);
	foreach(string prop in _bak_prop) {
		bak[prop] = who->query(prop);
		who->delete(prop);
	}
	bak["family"] = who->query("family/family_name");
	//删除需要归零的属性
	foreach(string prop in _del_prop) {
		who->delete(prop);
	}
	//清空skill
	SKI->clear_all(who);
	//备份种族
	bak["race"] = ([
		"id"	: RACE_D->query(who, "id"),
		"name"	: RACE_D->query(who, "name"),
	]);
	who->add(REI_PROP, ({ bak }) );
}

//飞向地球
void to_earth(object who)
{
	tell_object(who, "你渐渐失去了知觉。\n\n");
	tell_object(who, CYN"不知过去了多少时候...\n\n"NOR);

	who->set_temp("block_msg/all", 1);
	who->move("/obj/empty");

	call_out("go_home", 20, who);
}

//终点站到了
private void go_home(object who)
{
	object_f race;
	reset_prop(who);
	race = RACE_D->set_random(who);
	race->born(who);
}

