// by firefox 11/21/2009

#include <xyj_x.h>

mapping _e2c = ([

	"mieyao"		: "灭妖",
	"quest"			: "解谜",
	"misc"			: "其他",

	"player"		: "取经人",
	"wizard"		: "神棍",
	
	"gift"			: "天赋",
			
	"str"			: "力量",
	"strength"		: "力量",
	"cor"			: "胆识",
	"courage"		: "胆识",	
	"int"			: "智力",
	"intelligence"	: "智力",	
	"spi"			: "灵性",
	"spirituality"	: "灵性",
	"cps"			: "定力",
	"composure"		: "定力",
	"per"			: "容貌",
	"personality"	: "容貌",
	"con"			: "根骨",
	"constitution"	: "根骨",
	"kar"			: "福缘",
	"karma"			: "福缘",
	
	"bellicosity"	: "杀气",
	
	"skill"			: "技能",
	
	"combat_exp"	: "武学",
	"daoxing"		: "道行",
	"potential"		: "潜能",

	"kee"			: "气血",
	"sen"			: "精神",
	"force"			: "内力",
	"mana"			: "法力",
	"kee"			: "气血",
	"sen"			: "精神",

	"forces"		: "势力",

	"silver"		: "白银",
	"gold"			: "黄金",

	"fairyland"		: "仙界",
	"devildom"		: "魔道",
	 

]);

//英译中
string en_to_ch(string str)
{
	return or2(_e2c[str], to_chinese(str));
}

//中译英
string ch_to_en(string str)
{

}
