// by firefox 04/16/2011
// FCS����Ƿֹ���

/*
����
    (1)ͬ��˳��ӵ������������ͬ��ɫ��˳�ӡ���AΪ�׵�ͬ��˳���
    (2)��֧��������ͬ���ֵ��ƣ����һ���š������ִ�С����A����֧���
    (3)��«���ɡ���������һ�������ӡ�����ɵ��ƣ������Ҳ�д����ͣ�����������ִ�С��
    (4)ͬ����������˳�ӵ�����ͬ��ɫ���ơ��ȱ��������ĵ��ţ�����ͬ�ٱȵڶ��š��������ơ�
    (5)˳�ӣ������������ֵ����顣��AΪ�׵�˳����������Ҷ���˳�ӣ�������һ���ƣ������С��һ���ͱ������� 
�Ļ�ɫ��
    (6)������������������ͬ������ɣ���AΪ�׵��������
    (7)���ԣ������и�ʽ����������������ͬ���ֵ�������ɡ�������ͬ���ȱ��⸱��������һ�ԣ�������ͬ�ٱȵڶ��ԣ�
�� ������һ�����ٱ�ʣ�µĵ��Ƶĵ������������ͬ����ȴ�����е����ɫ��
    (8)���ӣ�������������ͬ���Ƽ������ŵ�������ɡ������Ҷ��Ƕ��ӣ��ȶ��ӵĴ�С���������Ҳһ�������ʣ�µ��� 
�ŵ��ƵĴ�С;���������ͬ�������������е����ɫ��
    (9)ɢ�ƣ���һ��̬������ɢ������ɣ����ɶ�(����)����������������˳(ͬ��˳)������ͬ�������ɺ�«��������֧�� 
�ȱ����һ���ƵĴ�С�������Сһ�����������ƵĻ�ɫ��

�Ʊ�ʾ��
	1.��ֵvȡֵ[0,27]��ʾ28����
	2.v/4��ʾ�����ֵ��ȡֵ[0,6]
	3.v%4��ʾ���滯ɫ��ȡֵ[0,3]

*/

#define MAX_CARD						5		//�������

#define STRAIGHT_FLUSH					8		//ͬ��˳
#define FOUR_OF_A_KIND					7		//��ͬ
#define FULL_HOUSE						6		//��«�����ò�
#define FLUSH							5		//ͬ��
#define STRAIGHT						4		//˳��
#define THREE_OF_A_KIND					3		//��ͬ
#define TWO_PAIR						2		//˫��
#define PAIR							1		//����
#define SINGLE							0		//����

static string* _score_name = ({
	"����", "����", "˫��", "����", "˳��", "ͬ��", "���ò�", "��֧", "ͬ��˳"
});


//˳��
int is_straight(int* values)
{
	for(int i = 0; i < MAX_CARD - 1; ++i)
		if(values[i] - values[i + 1] != 1) return 0;
	return 1;
}

//ͬ��
int is_flush(int* cards)
{
	for(int i = 0; i < MAX_CARD - 1; ++i)
		if(cards[i]%4 != cards[i + 1]%4) return 0;
	return 1;
}

//����ֵ����
mapping group_num(int* cards)
{
	mapping m = ([]);
	foreach(int c in cards) {
		m[c/4]++;
	}
	return m;
}

//�����Ʒ�����ͨ��������
int* cards_score(int* cards)
{
	int* sorted = sort_array(cards, -1);
	int* values = allocate(sizeof(cards));	
	mapping group = group_num(cards);						//�ư�ֵ����
	int straight, flush;

	for(int i = 0; i < MAX_CARD; ++i)
		values[i] = sorted[i]/4;

	straight = is_straight(values);
	flush = is_flush(cards);

	if(straight && flush) 
		return ({STRAIGHT_FLUSH, sorted[0]});				//ͬ��˳
	if(sizeof(group) == 2) {
		foreach(int k, int v in group) {
			if(v == 4) return ({FOUR_OF_A_KIND, k});		//��֧����ͬ
			if(v == 3) return ({FULL_HOUSE, k});			//��«��������
		}
	}
	if(flush) return ({FLUSH}) + values + ({sorted[0]%4});	//ͬ��
	if(straight) return ({STRAIGHT, sorted[0]});			//˳��

	if(sizeof(group) < 5) {
		int* pair = ({});
		int* single = ({});
		int flower = 0;
		foreach(int k, int v in group) {
			if(v == 3) return ({THREE_OF_A_KIND, k});		//����		
			if(v == 2) pair += ({k});
			else single += ({k});
		}
		pair = sort_array(pair, -1);
		single = sort_array(single, -1);
		
		foreach(int card in cards) {	//���Ҵ���ӵ����ɫ
			if(card/4 == pair[0] && card%4 > flower) 
				flower = card%4;
		}

		if(sizeof(pair) == 2) 
			return ({TWO_PAIR, pair[0], pair[1], single[0], flower});	//����
		if(sizeof(pair) == 1) 
			return ({PAIR, pair[0]}) + single + ({flower});				//һ��
	}

	return ({SINGLE, sorted[0]});
}

//�Ƚ��Ʒ�ֵ��С������ֵ������-s1>s2��0-s1=s2������-s1<s2
int cmp_score(int* s1, int* s2)
{
	for(int i = 0; i < sizeof(s1); ++i) {
		int n = s1[i] - s2[i];
		if(n) return n;
	}
	return 0;
}

//�ַ���ת��
int* s2c(string str)
{	
	string* arr1 = explode(str, ",");	
	int* arr2 = allocate(sizeof(arr1));
	string tab = "89TJQKA";

	for(int i = 0; i < sizeof(arr1); ++i) {
		arr2[i] = member_array(arr1[i][0], tab) * 4 + (arr1[i][1] - '0');
	}
	return arr2;
}

mixed* test()
{
	int* sf_a3 = cards_score(s2c("K3,A3,Q3,J3,T3"));
	int* sf_a0 = cards_score(s2c("A0,Q0,K0,J0,T0"));
	int* sf_q2 = cards_score(s2c("Q2,J2,T2,92,82"));

	int* k4_a = cards_score(s2c("A3,A2,A1,A0,80"));
	int* k4_8 = cards_score(s2c("83,82,81,80,A3"));

	int* fh_a = cards_score(s2c("A3,A2,81,A1,80"));
	int* fh_q = cards_score(s2c("Q3,Q2,Q1,A1,A0"));

	int* f_a3  = cards_score(s2c("A3,K3,Q3,J3,83"));
	int* f_a2  = cards_score(s2c("A2,K2,Q2,J2,82"));
	int* f_q3  = cards_score(s2c("K3,J3,T3,93,83"));

	int* s_a3 = cards_score(s2c("A3,K0,Q3,J3,T3"));
	int* s_a0 = cards_score(s2c("A0,K3,Q0,J0,T0"));
	int* s_q2 = cards_score(s2c("Q2,J1,T2,92,82"));

	int* k3_a = cards_score(s2c("A3,A2,A1,K0,80"));
	int* k3_8 = cards_score(s2c("83,82,81,90,A3"));

	int* p2_a3 = cards_score(s2c("A3,A2,K1,K0,Q0"));
	int* p2_a1 = cards_score(s2c("A1,A0,K2,K3,Q2"));
	int* p2_a1_s = cards_score(s2c("A1,A0,K2,K3,J3"));
	int* p2_a1_p2 = cards_score(s2c("A1,A0,Q2,Q3,J3"));
	int* p2_k1 = cards_score(s2c("K1,K0,Q2,Q3,J3"));
	
	int* p1_a3 = cards_score(s2c("A3,A2,K1,Q0,T0"));
	int* p1_a1 = cards_score(s2c("A1,A0,K2,Q3,T2"));
	int* p1_a1_s = cards_score(s2c("A1,A0,K2,J3,T2"));
	int* p1_k1 = cards_score(s2c("K1,K0,Q2,J3,T3"));

	int* a3 = cards_score(s2c("A3,82,K1,Q0,T0"));
	int* a2 = cards_score(s2c("A2,82,K1,Q0,T0"));

	assert(sf_a3[0] == STRAIGHT_FLUSH);
	assert(sf_a0[0] == STRAIGHT_FLUSH);
	assert(sf_q2[0] == STRAIGHT_FLUSH);
	assert(cmp_score(sf_a3, sf_a0) > 0);
	assert(cmp_score(sf_a3, sf_q2) > 0);
	assert(cmp_score(sf_a0, sf_q2) > 0);

	assert(k4_a[0] == FOUR_OF_A_KIND);
	assert(k4_8[0] == FOUR_OF_A_KIND);
	assert(cmp_score(sf_q2, k4_a) > 0);
	assert(cmp_score(k4_a, k4_8) > 0);

	assert(fh_a[0] == FULL_HOUSE);
	assert(fh_q[0] == FULL_HOUSE);
	assert(cmp_score(k4_8, fh_a) > 0);
	assert(cmp_score(fh_a, fh_q) > 0);
	
	assert(f_a3[0] == FLUSH);
	assert(f_a2[0] == FLUSH);
	assert(f_q3[0] == FLUSH);
	assert(cmp_score(fh_q, f_a3) > 0);
	assert(cmp_score(f_a3, f_a2) > 0);
	assert(cmp_score(f_a2, f_q3) > 0);

	assert(s_a3[0] == STRAIGHT);
	assert(s_a0[0] == STRAIGHT);
	assert(s_q2[0] == STRAIGHT);
	assert(cmp_score(f_q3, s_a3) > 0);
	assert(cmp_score(s_a3, s_a0) > 0);
	assert(cmp_score(s_a0, s_q2) > 0);

	assert(k3_a[0] == THREE_OF_A_KIND);
	assert(k3_8[0] == THREE_OF_A_KIND);
	assert(cmp_score(s_q2, k3_a) > 0);
	assert(cmp_score(k3_a, k3_8) > 0);

	assert(p2_a3[0] == TWO_PAIR);
	assert(p2_a1[0] == TWO_PAIR);
	assert(p2_a1_s[0] == TWO_PAIR);
	assert(p2_a1_p2[0] == TWO_PAIR);
	assert(p2_k1[0] == TWO_PAIR);
	assert(cmp_score(k3_8, p2_a3) > 0);
	assert(cmp_score(p2_a3, p2_a1) > 0);
	assert(cmp_score(p2_a1, p2_a1_s) > 0);
	assert(cmp_score(p2_a1_s, p2_a1_p2) > 0);
	assert(cmp_score(p2_a1_p2, p2_k1) > 0);

	assert(p1_a3[0] == PAIR);
	assert(p1_a1[0] == PAIR);
	assert(p1_a1_s[0] == PAIR);
	assert(p1_k1[0] == PAIR);
	assert(cmp_score(p2_k1, p1_a3) > 0);
	assert(cmp_score(p1_a3, p1_a1) > 0);
	assert(cmp_score(p1_a1, p1_a1_s) > 0);
	assert(cmp_score(p1_a1_s, p1_k1) > 0);
		
	assert(a3[0] == SINGLE);
	assert(a2[0] == SINGLE);
	assert(cmp_score(p1_k1, a3) > 0);
	assert(cmp_score(a3, a2) > 0);

	write("Test cards_score OK.\n");
	return 0;
}
