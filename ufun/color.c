// by firefox 11/21/2009

#include <ansi.h>
#include <xyj_x.h>


//»ñÈ¡ÑÕÉ«µÄÖÐÎÄÃû
string ch(string color)
{
	mapping tab = ([
		HIR : "ºì",	HIG : "ÂÌ", HIY : "»Æ", HIB : "À¶", 
		HIM : "·Û", HIC : "Çà", HIW : "°×", 
	]);
	return tab[color];
}

//ÑÕÉ«×Ö·û´®Ìæ»»
string rep(string str)
{
	mapping tab = ([
		"BLK" : BLK, "RED" : RED, "GRN" : GRN, "YEL" : YEL, 
		"BLU" : BLU, "MAG" : MAG, "CYN" : CYN, "WHT" : WHT,
		"HIR" : HIR, "HIG" : HIG, "HIY" : HIY, "HIB" : HIB,
		"HIM" : HIM, "HIC" : HIC, "HIW" : HIW, "NOR" : NOR,
	]);

	foreach(string k, string v in tab) {
		str = replace_string(str, "$" + k + "$", v);
	}
	return str;
}

//ÊÇ·ñÊÇÑÕÉ«
int is_color(string color)
{
	int n = sizeof(color);
	return n > 1 && color[0] == '' && color[n-1] == 'm';
}

//ÓÃÑÕÉ«·Ö¸î×Ö·û´®
string* spilt(string str)
{	
	string* arr1 = STRING->split(str, '');
	string* arr2 = ({});

	if(sizeof(arr1) && sizeof(arr1[0])) arr2 += ({arr1[0]});	
	for(int i = 1; i < sizeof(arr1); ++i) {
		string s = arr1[i];
		int offset = STRING->ch(s, 'm');
		if(offset > 0) {
			string next = s[offset + 1..];
			arr2 += ({ESC + s[0..offset]});
			if(sizeof(next)) arr2 += ({next});
		} else {
			arr2 += ({ESC + s});
		}
	}
	return arr2;
}


int color_test()
{
	string s1, s2;
	if(sscanf("%s m", "444 m") == 1) write("color:" + s1 + "\n");
	else write("no match\n");

	{
		string ss = HIR"abc"HIG"cde"HIB"efg";
		string* arr = spilt(ss);

		foreach(string str in arr) {
			if(is_color(str)) write(ch(str) + "\n");
			else write(str + "\n");
		}
	}
}

