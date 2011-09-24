// by firefox 04/16/2011
// FCS牌面记分规则

/*
规则：
    (1)同花顺：拥有五张连续性同花色的顺子。以A为首的同花顺最大。
    (2)铁支：四张相同数字的牌，外加一单张。比数字大小，「A」铁支最大。
    (3)葫芦：由「三条」加一个「对子」所组成的牌，若别家也有此牌型，则比三条数字大小。
    (4)同花：不构成顺子的五张同花色的牌。先比数字最大的单张，如相同再比第二张、依此类推。
    (5)顺子：五张连续数字的牌组。以A为首的顺子最大，如果大家都是顺子，比最大的一张牌，如果大小还一样就比这张牌 
的花色。
    (6)三条：牌型由三张相同的牌组成，以A为首的三条最大。
    (7)二对：牌型中港式五张牌由两组两张同数字的牌所组成。若遇相同则先比这副牌中最大的一对，如又相同再比第二对，
如 果还是一样，再比剩下的单牌的点数，如果再相同，则比大对子中的最大花色。
    (8)对子：牌型由两张相同的牌加上三张单张所组成。如果大家都是对子，比对子的大小，如果对子也一样，则比剩下的三 
张单牌的大小;如果还是相同，则比这个对子中的最大花色。
    (9)散牌：单一型态的五张散牌所组成，不成对(二对)，不成三条，不成顺(同花顺)，不成同花，不成葫芦，不成铁支。 
先比最大一张牌的大小，如果大小一样，比这张牌的花色。

牌表示：
	1.数值v取值[0,27]表示28张牌
	2.v/4表示牌面的值，取值[0,6]
	3.v%4表示牌面化色，取值[0,3]

*/

#define MAX_CARD						5		//最多牌数

#define STRAIGHT_FLUSH					8		//同花顺
#define FOUR_OF_A_KIND					7		//四同
#define FULL_HOUSE						6		//葫芦，满堂彩
#define FLUSH							5		//同花
#define STRAIGHT						4		//顺子
#define THREE_OF_A_KIND					3		//三同
#define TWO_PAIR						2		//双对
#define PAIR							1		//对子
#define SINGLE							0		//单张

static string* _score_name = ({
	"单张", "对子", "双对", "三条", "顺子", "同花", "满堂彩", "铁支", "同花顺"
});


//顺子
int is_straight(int* values)
{
	for(int i = 0; i < MAX_CARD - 1; ++i)
		if(values[i] - values[i + 1] != 1) return 0;
	return 1;
}

//同花
int is_flush(int* cards)
{
	for(int i = 0; i < MAX_CARD - 1; ++i)
		if(cards[i]%4 != cards[i + 1]%4) return 0;
	return 1;
}

//按牌值分组
mapping group_num(int* cards)
{
	mapping m = ([]);
	foreach(int c in cards) {
		m[c/4]++;
	}
	return m;
}

//计算牌分数并通告其特性
int* cards_score(int* cards)
{
	int* sorted = sort_array(cards, -1);
	int* values = allocate(sizeof(cards));	
	mapping group = group_num(cards);						//牌按值分组
	int straight, flush;

	for(int i = 0; i < MAX_CARD; ++i)
		values[i] = sorted[i]/4;

	straight = is_straight(values);
	flush = is_flush(cards);

	if(straight && flush) 
		return ({STRAIGHT_FLUSH, sorted[0]});				//同花顺
	if(sizeof(group) == 2) {
		foreach(int k, int v in group) {
			if(v == 4) return ({FOUR_OF_A_KIND, k});		//铁支，四同
			if(v == 3) return ({FULL_HOUSE, k});			//葫芦，三带二
		}
	}
	if(flush) return ({FLUSH}) + values + ({sorted[0]%4});	//同花
	if(straight) return ({STRAIGHT, sorted[0]});			//顺子

	if(sizeof(group) < 5) {
		int* pair = ({});
		int* single = ({});
		int flower = 0;
		foreach(int k, int v in group) {
			if(v == 3) return ({THREE_OF_A_KIND, k});		//三条		
			if(v == 2) pair += ({k});
			else single += ({k});
		}
		pair = sort_array(pair, -1);
		single = sort_array(single, -1);
		
		foreach(int card in cards) {	//查找大对子的最大花色
			if(card/4 == pair[0] && card%4 > flower) 
				flower = card%4;
		}

		if(sizeof(pair) == 2) 
			return ({TWO_PAIR, pair[0], pair[1], single[0], flower});	//两对
		if(sizeof(pair) == 1) 
			return ({PAIR, pair[0]}) + single + ({flower});				//一对
	}

	return ({SINGLE, sorted[0]});
}

//比较牌分值大小，返回值：正数-s1>s2，0-s1=s2，负数-s1<s2
int cmp_score(int* s1, int* s2)
{
	for(int i = 0; i < sizeof(s1); ++i) {
		int n = s1[i] - s2[i];
		if(n) return n;
	}
	return 0;
}

//字符串转牌
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
