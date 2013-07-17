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
#define ROAD_Y (V_SIZE >> 1)

//==============================
// 独自関数のプロトタイプ宣言 PROTOTYPE
//==============================
void game_init(); // ゲームの初期化関数
void game_main(); // ゲームの関数
void plot(int x, int y, int color);
void fillBox(int x1, int y1, int x2, int y2, int color);
void draw_line(int x1, int y1, int x2, int y2, int color);
void move_jiki();
void draw_jiki();
void draw_back();


//==============================
// 独自のグローバル変数の宣言 VALUE
//==============================
typedef struct Pos {
	int x, y;
} Pos;
typedef struct FPos {
	float x, y;
} FPos;

typedef struct Chara {
	FPos p;		// 現在の場所
	FPos p_prev; // 直前の場所
	float f;	// 現在加えられている力
	char isflying;	// 空中なら1
} Chara;
Chara jiki;


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

// 自機
void move_jiki() 
{
	float y_tmp;
	if (!L_BTN) { jiki.p.x-= 0.7; }
	if (!R_BTN) { jiki.p.x+= 0.7; }
	//if (!D_BTN) { jiki.p.y+= 0.7; }
	if (!U_BTN) {
		if (!jiki.isflying) {
			jiki.f = 7;
			jiki.isflying = 1;
		} else {
			jiki.f = -1;
		}
	}

	if (jiki.isflying) {
		y_tmp = jiki.p.y;
		jiki.p.y -= -(jiki.p.y - jiki.p_prev.y) + jiki.f;
		jiki.p_prev.y = y_tmp;
		if (jiki.p.y == ROAD_Y) {
			jiki.isflying = 0;
		}
	}
}
void draw_jiki()
{
	draw_line(20,20, jiki.p.x, jiki.p.y, 0x00);
	fillBox(jiki.p.x, jiki.p.y, jiki.p.x+1, jiki.p.y+1, 0x30);
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
	jiki.p.x = 10;
	jiki.p.y = ROAD_Y;
	jiki.p_prev.x = jiki.p.x;
	jiki.p_prev.y = jiki.p.y;
}

//==============================
// ゲームのメインの処理の関数 MAIN
// 呼ばれた後、毎回disp_frame()が呼ばれている。
//==============================
void game_main()
{



	// バーが動く

	// 自機をうごかす
	move_jiki();

	// 当たり判定
	
	// 画面クリア
	draw_back();
	// 自機を描く
	draw_jiki();
	//draw_line(5,5, 40,50, 0x00);
	//printf("end main().");
}

