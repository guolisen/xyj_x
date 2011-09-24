// by firefox 04/16/2011
// 牌面记分规则

#include <ansi.h>

static mixed* _flower = ({
	({
		"┌─────┐",
		"│"HIR"%s"NOR"　　　　│",
		"│　　　　　│",
		"│　"HIR"　◆　"NOR"　│",
		"│　"HIR"◆　◆"NOR"　│",
		"│　"HIR"　◆　"NOR"　│",
		"│　　　　　│",
		"│　　　　"HIR"%s"NOR"│",
		"└─────┘",
	}),
	({
		"┌─────┐",
		"│%s　　　　│",
		"│　　　　　│",
		"│　　●　　│",
		"│　●◆●　│",
		"│　　▲　　│",
		"│　　　　　│",
		"│　　　　%s│",
		"└─────┘",
	}),
	({
		"┌─────┐",
		"│"HIR"%s"NOR"　　　　│",
		"│　　　　　│",
		"│　"HIR"　▼　"NOR"　│",
		"│　"HIR"◆●◆"NOR"　│",
		"│　"HIR"　▼　"NOR"　│",
		"│　　　　　│",
		"│　　　　"HIR"%s"NOR"│",
		"└─────┘",
	}),
	({
		"┌─────┐",
		"│%s　　　　│",
		"│　　　　　│",
		"│　　▲　　│",
		"│　◆●◆　│",
		"│　　▲　　│",
		"│　　　　　│",
		"│　　　　%s│",
		"└─────┘",
	}),
	({
		"┌─────┐",
		"│※※※※※│",
		"│※※※※※│",
		"│※※※※※│",
		"│※※※※※│",
		"│※※※※※│",
		"│※※※※※│",
		"│※※※※※│",
		"└─────┘",
	}),
});

//显示一组牌
string draw_cards(int* cards)
{
	string canvas = "";
	string str = "８９⒑ＪＱＫＡ";

	for(int y = 0; y < sizeof(_flower[0]); ++y) {
		foreach(int card in cards) {
			int v = card / 4;
			int f = (card < 0) ? 4 : card % 4;
			canvas += sprintf(_flower[f][y], str[v*2..v*2+1]);
		}
		canvas += "\n";
	}
	return canvas;
}

void test1()
{
	write(draw_cards(({-1, 27, 22, 17, 12})));
	write(draw_cards(({-1, 11, 6, 2, 1})));

}


