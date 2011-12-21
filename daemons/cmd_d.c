// cracked by vikee 2/09/2002   vikee@263.net
//
// cmd_d.c
//
// By Annihilator (11/07/94)

mapping search = ([]);

void rehash(string dir)
{
	int i;
	string *cmds;

	if( dir[sizeof(dir)-1]!='/' ) dir += "/";
	cmds = get_dir(dir);
	i = sizeof(cmds);
	while(i--)
		if( !sscanf(cmds[i], "%s.c", cmds[i]) ) {
			if( i==0 ) cmds = cmds[1..sizeof(cmds)];
			else if( i==sizeof(cmds) ) cmds = cmds[0..<2];
			else cmds = cmds[0..i-1] + cmds[i+1..<1];
		}
	if( sizeof(cmds) )
		search[dir] = cmds;
}

string find_command(string verb, string *path)
{
	int i;

	if( !pointerp(path) ) return 0;
	if( !verb) return 0;

	i = sizeof(path);
	while(i--) {
		if( undefinedp(search[path[i]]) ) rehash(path[i]);
		if( undefinedp(search[path[i]]) ) continue;
		if( member_array(verb, search[path[i]])!=-1 )
			return path[i] + verb;
	}
	return 0;
}

mapping _cost = ([]);

void verb_cost(string verb, int cost)
{
	if(!_cost[verb]) _cost[verb] = ({0, 0.1});
	_cost[verb][0]++;
	_cost[verb][1] += to_float(cost);
}

private int cmp_cmds_cost(mixed k1, mixed k2)
{
	reset_eval_cost();
	return _cost[k1][1] >= _cost[k2][1] ? -1 : 1;
}

mapping query_cost()
{
	return _cost;
}

void show_cost()
{
	string* cmds = sort_array(keys(_cost), "cmp_cmds_cost");
		
	//return cmds;
	for(int i = 0; i < 50 && i < sizeof(cmds); ++i) {		
		printf("%2d  %-16s %8d  %8f\n", i, cmds[i], _cost[cmds[i]][0], _cost[cmds[i]][1]);
	}
}

void clear_cost()
{
	_cost = ([]);
}

