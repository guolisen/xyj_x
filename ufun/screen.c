
#include <xyj_x.h>
#include <ansi.h>

#define W					24		//�ַ����
#define H					24		//�ַ��߶�
#define LEN					(W*H/8)	//һ���ַ����ֿ���ռ�õ��ֽ���

#define CW					80
#define CH					32

#define DX					5		//ˮƽƫ��

#define pixel(x, y)			_canvas[(y)*CW + (x)]

mixed* _canvas;
string _line;

//�����ȡ�ַ���
int create()
{
	//seteuid(getuid());
	_canvas = allocate(CW*CH);
	_line = "         1         2         3         4         5         6         7         8\n";
}

private void clear()
{
	for(int i = 0; i < sizeof(_canvas); ++i)
		_canvas[i] = ' ';
}

private void show_canvas()
{
	write(YEL);
	for(int y = 0; y < CH; ++y) {
		for(int x = 0; x < CW; ++x) {
			_line[x] = pixel(x, y);
		}
		write(_line);
	}
	write(NOR);

}

//��ʾһ������
private int draw(string data, int left, int top)
{
	for(int y = 0; y < H; ++y) {
		for(int x = 0; x < W; ++x) {
			int offset = y * W + x;
			if(data[offset / 8] & (1 << offset % 8))
				pixel(left + x, top + y) = 'O';
		}
	}

}

//չʾ�����ַ�
void show(string str)
{
	int N = sizeof(str);
	string data;
		
	int x = DX;
	int y = (CH - H) / 2 - 1;
	int d = (CW - (DX + W/2) * 2)/(N - 1);

	clear();

	for(int i = 0; i < N; ++i) {
		int j = str[i] - 'A';
		data = read_bytes(__DIR__"screen.bin", j * LEN, LEN);
		{
			int dx = (DX)/2 - random(DX);
			int dy = y/2 - random(y);

			draw(data, x + i * d + dx, y + dy);
		}
	}
	if(wizardp(_player)) trace("��Ļ���֣�" + str);

	show_canvas();
}

string random4c()
{
	string str = "1234";
	for(int i = 0; i < sizeof(str); ++i) {
		str[i] = 'A' + random(26);
	}
	show(str);
	return str;
}