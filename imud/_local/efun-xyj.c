// by firefox 04/16/2011
// iMUD local simul_efun

#include <imud-efun.h>

//Ãû³ÆID±íÊ¾
string name_id(mapping who)
{
	if(who[PMUD]) return sprintf("%s(%s@%s)", who[PNAME], capitalize(who[PID]), who[PMUD]);
	return sprintf("%s(%s)", who[PNAME], capitalize(who[PID]));
}

