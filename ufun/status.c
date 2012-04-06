

mapping _infos = ([]);

int query(string prop);

void create()
{

	query("str");

}

private int get(string line)
{
	int d = 0;
	sscanf(line, "%*s%d%*s", d);
	return d;
}

int query(string prop)
{
	string str = mud_status(0);
	string* arr = explode(str, "\n");

	_infos["objects"]		= get(arr[1]);
	_infos["mappings"]		= get(arr[4]);
	_infos["nodes"]			= get(arr[5]);
	_infos["interactives"]	= get(arr[6]);
	_infos["strings"]		= get(arr[8]);
	_infos["callout"]		= get(arr[9]);
	
	_infos["mem"]			= memory_info();

	return _infos[prop];
}