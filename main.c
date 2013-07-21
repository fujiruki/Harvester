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

//==============================
// 独自関数のプロトタイプ宣言 PROTOTYPE
//==============================
void game_init(); // ゲームの初期化関数
void game_main(); // ゲームの関数
void plot(int x, int y, int color);
void fillBox(int x1, int y1, int x2, int y2, int color);
void draw_line(int x1, int y1, int x2, int y2, int color);
void move_harvester();
void draw_harvester();
void draw_back();
void move_harvester();


//==============================
// 独自のグローバル変数の宣言 VALUE
//==============================
typedef struct Pos {
	int x, y;
} Pos;
typedef struct Size {
	int w, h;
} Size;
typedef struct FPos {
	float x, y;
} FPos;

// 果実
typedef struct Fruit {
	FPos p;		// 現在の場所
	FPos p_prev; // 直前の場所
	float f;	// 現在加えられている力
	char isflying;	// 空中なら1
	Pos basket;
	Pos basket_size;	// 
} Fruit;

// 収穫者
typedef struct Harvester {
	FPos p;		// 現在の場所
	FPos p_prev; // 直前の場所
	float f;	// 現在加えられている力
	char isflying;	// 空中なら1
	Pos basket;
	Pos basket_size;	// 
} Harvester;
Harvester hvester;	// 収穫者(プレイヤーが操作する)


//==============================
// 独自関数 FUNCTION
//==============================
void draw_harvester()
{
	fillBox(hvester.p.x, hvester.p.y,
			hvester.p.x + PLAYER_W, hvester.p.y + PLAYER_H, 0xa8);
}

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

	if (!R_BTN) { hvester.p.x += PLAYER_SPEED; }
	if (!L_BTN) { hvester.p.x -= PLAYER_SPEED; }


	hvester.p_prev.x = p_tmp.x;
	hvester.p_prev.y = p_tmp.y;
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
	hvester.p.x = PLAYER_X_DEF;
	hvester.p.y = PLAYER_Y_DEF;
	hvester.p_prev.x = hvester.p.x;
	hvester.p_prev.y = hvester.p.y;
}

//==============================
// ゲームのメインの処理の関数 MAIN
// 呼ばれた後、毎回disp_frame()が呼ばれている。
//==============================
void game_main()
{

	// 



	// 自機をうごかす
	move_harvester();

	// 当たり判定
	
	// 画面クリア
	draw_back();
	// 自機を描く
	draw_harvester();
	//draw_line(5,5, 40,50, 0x00);
	//printf("end main().");
}

