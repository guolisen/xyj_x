// by firefox 11/21/2009

//字符串中搜索字符位置
int ch(string str, int ch)
{
	int i;
	for(i = 0; i < sizeof(str); ++i) {
		if(str[i] == ch) return i;
	}
	return -1;
}

//用一个字符分割字符串，explode的行为居然舍弃第一个空串，与文档不符
string* split(string str, int sep)
{
	string* arr = ({});
	int n;
	while((n = ch(str, sep)) >= 0) {
		arr += ({str[0..n - 1]});
		str = str[n + 1..];
	}
	arr += ({str});
	return arr;
}

//计算散列值
int hash(string str)
{
    int h = 0;
	foreach(int c in str) {    
		h = 31 * h + c;
	}
    return h;
}
