/* 糸通し　を作ってみる */
#include <stdio.h>
#include "main.h"


//==============================
// 共通の定数や変数や関数
// 他の人がつくったもの
//==============================
// 他の先生が作った便利な関数使うときはここに書いておく。
// ここに書いてあるものは実機にすでにあるということにする。
// 実機で動かすときはこの部分はコピペしない。


//==============================
// 定数宣言 LITERAL
//==============================
#define PLAYER_W	8
#define PLAYER_H	12
#define PLAYER_SPEED	0.7
#define ROAD_Y	(V_SIZE-PLAYER_H-3)
#define PLAYER_X_DEF	5
#define PLAYER_Y_DEF	ROAD_Y
// FRUIT
#define FRUITS_MAX	10				// フルーツの最大数
#define FR_STATE_NONE	0		// Fruitがない
#define FR_STATE_GREEN	1		// 青い小さい実
#define FR_STATE_BIG	2		// 青い大きな実
#define FR_STATE_RIPE	3		// 赤い大きな実(完熟)
#define FR_STATE_DROPPING	4	// 落下中

//==============================
// 独自関数のプロトタイプ宣言 PROTOTYPE
//==============================
void game_init(); // ゲームの初期化関数
void game_main(); // ゲームの関数
void plot(int x, int y, int color);
void fillBox(int x1, int y1, int x2, int y2, int color);
void draw_line(int x1, int y1, int x2, int y2, int color);
void draw_back();

void move_harvester();
void draw_harvester();
void draw_basket();

void set_fruit();
void grow_fruits();	// フルーツを成長させる
void drop_fruits();	// フルーツを落とす
void draw_fruits();	// フルーツを描く

//==============================
// 独自のグローバル変数の宣言 VALUE
//==============================
//=== TYPE =====================
typedef struct Pos {
	int x, y;
} Pos;
typedef struct Size {
	int w, h;
} Size;
typedef struct FPos {
	float x, y;
} FPos;
typedef struct LevelConf {
	unsigned char level;	// 現在のレベル
	char fruits_n;	// 現在の果実の最大数
} LevelConf;

// 果実
typedef struct Fruit {
	FPos p;			// 現在の場所
	FPos p_prev; 	// 直前の場所
	float f;		// 現在加えられている力
	unsigned char state;	// 果実、完熟、落下中
	unsigned int state_cnt;
} Fruit;

// 収穫者
typedef struct Harvester {
	FPos p;		// 現在の場所
	FPos p_prev; // 直前の場所
	float f;	// 現在加えられている力
	char isflying;	// 空中なら1
	char turnRight;		// 向き。1なら右、それ以外で左向き
} Harvester;

// カゴ
typedef struct Basket {
	Pos p;
	Size size;
} Basket;

//=== VARIABLES =================
#define LCOUNT_FRUITS_GROW	5
unsigned int lcnt_fruits_grow;
Fruit fruits[FRUITS_MAX];	// フルーツ(時間経過で成長、落下する。収穫者でバウンド)
Harvester hvester;			// 収穫者(プレイヤーが操作する)
LevelConf conf;
Basket basket;


//==============================
// 独自関数 FUNCTION
//==============================

void plot(int x, int y, int color)
{
	if (0 <= x && x < H_SIZE && 0<=y && y < V_SIZE)
	{
		pat[y][x] = color;
	}
}
void draw_line(int x1, int y1, int x2, int y2, int color)
{
	// 参考:http://fussy.web.fc2.com/algo/algo1-1.htm
	int i;
	Pos dist, direc;	// 2点間距離、方向
	int E;

	// 2点間距離
	dist.x = (x2 > x1) ? (x2-x1):(x1-x2);
	dist.y = (y2 > y1) ? (y2-y1):(y1-y2);

	// 2点の方向
	direc.x = (x2 > x1) ? 1 : -1;
	direc.y = (y2 > y1) ? 1 : -1;

	//傾きが1より小さい場合
	if ( dist.x > dist.y )
	{
		E = -dist.x;
		for ( i = 0 ; i <= dist.x ; i++ ) {
			plot( x1, y1, color );
			x1 += direc.x;
			E += 2 * dist.y;
			if ( E >= 0 ) {
				y1 += direc.y;
				E -= 2 * dist.x;
			}
		}
		/* 傾きが1以上の場合 */
	} else {
		E = -dist.y;
		for ( i = 0 ; i <= dist.y ; i++ ) {
			plot( x1, y1, color );
			y1 += direc.y;
			E += 2 * dist.x;
			if ( E >= 0 ) {
				x1 += direc.x;
				E -= 2 * dist.y;
			}
		}
	}
}

void fillBox(int x1, int y1, int x2, int y2, int color)
{
	int i, j;

	//全部はみ出ていれば、なにもしない。
	if (H_SIZE <= x1 || V_SIZE <= y1 || x2 < 0 || y2 < 0) { return; }

	// 横と縦はみ出ていれば、収まるようにサイズ調整
	if (x1 < 0) { x1 = 0; }
	if (y1 < 0) { x1 = 0; }
	if (H_SIZE < x2) { x2 = H_SIZE; }
	if (V_SIZE < y2) { y2 = V_SIZE; }

	for (i=y1; i<y2; i++) {
		for (j=x1; j<x2; j++) {
			pat[i][j] = color;
		}
	}

	return;
}

void move_harvester()
{
	FPos p_tmp;
	p_tmp.x = hvester.p.x;
	p_tmp.y = hvester.p.y;

	if (!R_BTN) {
		hvester.p.x += PLAYER_SPEED;
		hvester.turnRight = 1;
	}
	if (!L_BTN) {
	 	hvester.p.x -= PLAYER_SPEED;
		hvester.turnRight = 0;
	}


	hvester.p_prev.x = p_tmp.x;
	hvester.p_prev.y = p_tmp.y;
}
void draw_harvester()
{
	fillBox(hvester.p.x, hvester.p.y,
			hvester.p.x + PLAYER_W, hvester.p.y + PLAYER_H, 0xa8);
}

void draw_basket()
{
	if (hvester.turnRight == 1) {
		basket.p.x = hvester.p.x - basket.size.w - 1;
	} else {
		basket.p.x = hvester.p.x  + PLAYER_W;	//hvester.size.w;
	}

	draw_line(basket.p.x, basket.p.y, basket.p.x, basket.p.y + basket.size.h, 0x50);
	draw_line(basket.p.x+basket.size.w, basket.p.y, basket.p.x+basket.size.w, basket.p.y + basket.size.h, 0x50);
	draw_line(basket.p.x, basket.p.y + basket.size.h, basket.p.x+basket.size.w, basket.p.y + basket.size.h, 0x50);
}

//fruiti番目のフルーツをセットする
void set_fruit(int fruiti)
{
	// fruits
	fruits[fruiti].p.x = rand() & 0x3f;
	fruits[fruiti].p.y = rand() & 0x03;
	fruits[fruiti].state = FR_STATE_NONE+1;
	fruits[fruiti].state_cnt = rand() & 0x0f +1;
}


void draw_back()
{
	fillBox(0, 0, H_SIZE, V_SIZE, 0xff);
}

//==============================
// ゲームの初期化関数 INIT
//==============================
void game_init()
{
	int i;

	lcnt_fruits_grow = 0;

	hvester.p.x = PLAYER_X_DEF;
	hvester.p.y = PLAYER_Y_DEF;
	hvester.p_prev.x = hvester.p.x;
	hvester.p_prev.y = hvester.p.y;
	hvester.turnRight = 1;
	basket.p.y = hvester.p.y + 1;
	basket.size.w = 4;
	basket.size.h = 8;
	draw_basket();

	for (i=0; i<FRUITS_MAX; i++) {
		fruits[i].state = FR_STATE_NONE;
	}
	set_fruit(0);

	conf.level = 1;
	conf.fruits_n = 1;
}

void grow_fruits()
{
	int i;
	for (i=0; i<FRUITS_MAX; i++) {
		switch (fruits[i].state) {
			case FR_STATE_NONE:
				break;
			case FR_STATE_GREEN:
				if (fruits[i].state_cnt == 0) {
					fruits[i].state++;	// BIGになる
					fruits[i].state_cnt = (rand() & 0x03)+1;
					printf("SET GREEN: %d\n", fruits[i].state_cnt);
				}
				break;
			case FR_STATE_BIG:
				if (fruits[i].state_cnt == 0) {
					fruits[i].state++;	// RIPEになる
					fruits[i].state_cnt = (rand() & 0x03)+1;
					printf("SET BIG: %d\n", fruits[i].state_cnt);
				}
				break;
			case FR_STATE_RIPE:
				if (fruits[i].state_cnt == 0) {
					fruits[i].state++;	// DROPPINGになる
					fruits[i].state_cnt = (rand() & 0x01)+1;
					fruits[i].f = 0.14;
					fruits[i].p_prev.y = fruits[i].p.y;
					printf("START DROP: %d\n", fruits[i].state_cnt);
				}
				break;
			//case FR_STATE_DROPPING:	別の関数で。
				//break;
			default:	// どれでもなくなったとき
				break;
		}
		fruits[i].state_cnt--;
	}
}
// フルーツを描く
void draw_fruits() {
	int i;
	for (i=0; i<FRUITS_MAX; i++) {
		switch (fruits[i].state) {
			case FR_STATE_NONE:
				break;
			case FR_STATE_GREEN:
				plot(fruits[i].p.x, fruits[i].p.y, 0x94);
				break;
			case FR_STATE_BIG:
				fillBox(fruits[i].p.x-1, fruits[i].p.y, fruits[i].p.x+1, fruits[i].p.y+2, 0x74);
				break;
			case FR_STATE_RIPE:
				fillBox(fruits[i].p.x-1, fruits[i].p.y, fruits[i].p.x+1, fruits[i].p.y+2, 0x30);
				break;
			case FR_STATE_DROPPING:
				fillBox(fruits[i].p.x-1, fruits[i].p.y, fruits[i].p.x+1, fruits[i].p.y+2, 0x20);
				break;
			default:	// どれでもなくなったとき
				break;
		}
	}
}

// フルーツを落とす
void drop_fruits() {
	int i;
	float y_tmp, vy;
	for (i=0; i<FRUITS_MAX; i++) {
		if (fruits[i].state != FR_STATE_DROPPING) {
			continue;
		}

		y_tmp = fruits[i].p.y;
		vy = (fruits[i].p.y - fruits[i].p_prev.y) + fruits[i].f;
		if (vy > 2.5) { vy = 2.5; }
		fruits[i].p.y += vy;
		fruits[i].p_prev.y = y_tmp;
	}
}
//==============================
// ゲームのメインの処理の関数 MAIN
// 呼ばれた後、毎回disp_frame()が呼ばれている。
//==============================
void game_main()
{
	if (!BTN1) { set_fruit(0); }
	// フルーツを成長させる
	if (++lcnt_fruits_grow == LCOUNT_FRUITS_GROW) {
		lcnt_fruits_grow = 0;
		grow_fruits();
	}
	// フルーツを落とす
	drop_fruits();

	// 自機をうごかす
	move_harvester();

	// 当たり判定
	
	// 画面クリア
	draw_back();
	// フルーツを描く
	draw_fruits();
	draw_basket();
	// 自機を描く
	draw_harvester();
	//draw_line(5,5, 40,50, 0x00);
	//printf("end main().");
}

