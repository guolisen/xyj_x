// by firefox 11/21/2009

#include <xyj_x.h>

mapping _e2c = ([

	"mieyao"		: "����",
	"quest"			: "����",
	"misc"			: "����",

	"player"		: "ȡ����",
	"wizard"		: "���",
	
	"gift"			: "�츳",
			
	"str"			: "����",
	"strength"		: "����",
	"cor"			: "��ʶ",
	"courage"		: "��ʶ",	
	"int"			: "����",
	"intelligence"	: "����",	
	"spi"			: "����",
	"spirituality"	: "����",
	"cps"			: "����",
	"composure"		: "����",
	"per"			: "��ò",
	"personality"	: "��ò",
	"con"			: "����",
	"constitution"	: "����",
	"kar"			: "��Ե",
	"karma"			: "��Ե",
	
	"bellicosity"	: "ɱ��",
	
	"skill"			: "����",
	
	"combat_exp"	: "��ѧ",
	"daoxing"		: "����",
	"potential"		: "Ǳ��",

	"kee"			: "��Ѫ",
	"sen"			: "����",
	"force"			: "����",
	"mana"			: "����",
	"kee"			: "��Ѫ",
	"sen"			: "����",

	"forces"		: "����",

	"silver"		: "����",
	"gold"			: "�ƽ�",

	"fairyland"		: "�ɽ�",
	"devildom"		: "ħ��",
	 

]);

//Ӣ����
string en_to_ch(string str)
{
	return or2(_e2c[str], to_chinese(str));
}

//����Ӣ
string ch_to_en(string str)
{

}
