// by firefox 11/21/2009

//�ַ����������ַ�λ��
int ch(string str, int ch)
{
	int i;
	for(i = 0; i < sizeof(str); ++i) {
		if(str[i] == ch) return i;
	}
	return -1;
}

//��һ���ַ��ָ��ַ�����explode����Ϊ��Ȼ������һ���մ������ĵ�����
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

//����ɢ��ֵ
int hash(string str)
{
    int h = 0;
	foreach(int c in str) {    
		h = 31 * h + c;
	}
    return h;
}
