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
#define chat_UP	5			// チャタリング防止用の空回しループ回数
#define PLAYER_W	5
#define PLAYER_H	8
#define PLAYER_SPEED	0.9

#define ROAD_Y	(V_SIZE-PLAYER_H-3)
#define PLAYER_X_DEF	5
#define PLAYER_Y_DEF	ROAD_Y-PLAYER_H
#define HVESTER_COLOR	0x70
#define BASKET_FRAME_COLOR	0x10	// バスケットのフレームの色
#define BASKET_COLOR	0x60	// バスケットのフレームの色
// FRUIT
#define FRUITS_MAX	10				// フルーツの最大数
#define FR_STATE_NONE	0		// Fruitがない
#define FR_STATE_GREEN	1		// 青い小さい実
#define FR_STATE_BIG	2		// 青い大きな実
#define FR_STATE_RIPE	3		// 赤い大きな実(完熟)
#define FR_STATE_DROPPING	4	// 落下中
#define FR_RIPE_R			1		// フルーツの半径
#define FR_RIPE_DIA			2		// フルーツの直径	//Diameter
#define FR_COLOR_RIPE	0x30	// RIPEの色
#define FR_DROPPING_F	0.14	// 落下中のフルーツへかかる力
#define FR_BOUND_F		(-1.3)	// 落下中のフルーツへかかる力

//==============================
// 独自関数のプロトタイプ宣言 PROTOTYPE
//==============================
void game_init(); // ゲームの初期化関数
void game_main(); // ゲームの関数
void plot(int x, int y, int color);
void fillBox(int x1, int y1, int x2, int y2, int color);
void draw_line(int x1, int y1, int x2, int y2, int color);
void draw_back();

void loop_chatter(unsigned char *counter, char *flag);	// counterをデクリメントして0ならflagを0にする

void check_level();
void check_collision_fruits();	// フルーツとの当たり判定

void move_harvester();
void draw_harvester();
void draw_basket();

void move_basket();

void set_fruit(int fruiti);	// 指定の番号にフルーツを作成する
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
	unsigned char level_prev;	// 直前までのレベル(変化を確認するため)
	char fruits_n;	// 現在の果実の最大数
	char fruits_n_prev;	// 直前までのレベル(変化を確認するため)
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
unsigned char cloop_u_btn;	// loop for chatterring
unsigned char cloop_d_btn;
char C_U_BTN;			// チャタリング対策済みボタン変数(credible)
char C_D_BTN;
char C_L_BTN;
char C_R_BTN;
char C_BTN1;
char C_BTN2;
unsigned int score;


//==============================
// 独自関数 FUNCTION
//==============================

void plot(int x, int y, int color) {
	if (0 <= x && x < H_SIZE && 0<=y && y < V_SIZE)
	{
		pat[y][x] = color;
	}
}
void draw_line(int x1, int y1, int x2, int y2, int color) {
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
void fillBox(int x1, int y1, int x2, int y2, int color) {
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

void check_level() {
	char next_fru_n;
	char i;

	if (conf.level == conf.level_prev) { return; }
	conf.level_prev = conf.level;

	switch (conf.level)
	{
		case 1:
			next_fru_n = 1;
			break;
		case 2:
			next_fru_n = 3;
			break;
		case 3:
			next_fru_n = 4;
			break;
		case 4:
			next_fru_n = 6;
			break;
		case 5:
			next_fru_n = 8;
			break;
		case 6:
			next_fru_n = FRUITS_MAX;
			break;
		case 7:
			break;
		case 8:
			break;
	}

	for (i=conf.fruits_n; i<next_fru_n; i++) {
		// フルーツ数が増えたら増やす
		set_fruit(i);
	}

	conf.fruits_n = next_fru_n;
}

void move_basket() {
	if (hvester.turnRight == 1) {
		basket.p.x = hvester.p.x - basket.size.w - 1;
	} else {
		basket.p.x = hvester.p.x  + PLAYER_W;	//hvester.size.w;
	}
}

void move_harvester() {
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
void draw_harvester() {
	fillBox(hvester.p.x, hvester.p.y,
			hvester.p.x + PLAYER_W, hvester.p.y + PLAYER_H, HVESTER_COLOR);
}


void draw_basket() {
	draw_line(basket.p.x, basket.p.y, basket.p.x, basket.p.y + basket.size.h, BASKET_FRAME_COLOR);
	draw_line(basket.p.x+basket.size.w, basket.p.y, basket.p.x+basket.size.w, basket.p.y + basket.size.h, BASKET_FRAME_COLOR);
	draw_line(basket.p.x, basket.p.y + basket.size.h, basket.p.x+basket.size.w, basket.p.y + basket.size.h, BASKET_FRAME_COLOR);
	fillBox(basket.p.x+1, basket.p.y, basket.p.x+basket.size.w, basket.p.y + basket.size.h, BASKET_COLOR);
}

//fruiti番目のフルーツをセットする
void set_fruit(int fruiti) {
	// fruits
	fruits[fruiti].p.x = rand() & 0x3f;
	fruits[fruiti].p.y = rand() & 0x03;
	fruits[fruiti].state = FR_STATE_NONE;
	fruits[fruiti].state_cnt = rand() & 0x0f +1;
}

void draw_back() {
	int i;
	fillBox(0, 0, H_SIZE, V_SIZE, 0xff);

	// カラースケール
	for (i=0; i<0x3f;i++) {
		if (i < 60) {
			plot(i, 1, i<<2);
			plot(i, 0, (i&1)?0xff:0x00);
			if (i%10==0) {
				plot(i, 0, 0x30);
			}
		} else {
			plot(i-60, 2, i<<2);
		}
	}
}

void grow_fruits() {
	int i;
	for (i=0; i<conf.fruits_n; i++) {
		switch (fruits[i].state) {
			case FR_STATE_NONE:
				if (fruits[i].state_cnt == 0) {
					fruits[i].state++;	// GREENになる
					fruits[i].state_cnt = (rand() & 0x03)+2;
				}
				break;
			case FR_STATE_GREEN:
				if (fruits[i].state_cnt == 0) {
					fruits[i].state++;	// BIGになる
					fruits[i].state_cnt = (rand() & 0x03)+1;
				}
				break;
			case FR_STATE_BIG:
				if (fruits[i].state_cnt == 0) {
					fruits[i].state++;	// RIPEになる
					fruits[i].state_cnt = (rand() & 0x03)+1;
				}
				break;
			case FR_STATE_RIPE:
				if (fruits[i].state_cnt == 0) {
					fruits[i].state++;	// DROPPINGになる
					fruits[i].state_cnt = (rand() & 0x01)+1;
					fruits[i].f = FR_DROPPING_F;
					fruits[i].p_prev.y = fruits[i].p.y;
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
	for (i=0; i<conf.fruits_n; i++) {
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
				fillBox(fruits[i].p.x-FR_RIPE_R, fruits[i].p.y, fruits[i].p.x+FR_RIPE_R, fruits[i].p.y+2, FR_COLOR_RIPE);
				break;
			case FR_STATE_DROPPING:
				fillBox(fruits[i].p.x-1, fruits[i].p.y, fruits[i].p.x+1, fruits[i].p.y+FR_RIPE_DIA, 0x20);
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

		// 画面外に出たら種にもどる
		if (fruits[i].p.y >= V_SIZE) {
			set_fruit(i);
			continue;
		}
	}
	
}
// フルーツとカゴの枠との当たり判定
void check_collision_basket_fruit(Fruit *fr)
{
	char fr_y;
	char x;
	fr_y = (*fr).p.y + FR_RIPE_DIA;

	for (x=(*fr).p.x+FR_RIPE_R-1; x>=(*fr).p.x-1; x--) {
		if (pat[fr_y][x] == BASKET_FRAME_COLOR || pat[fr_y][x] == HVESTER_COLOR) {
			// バウンドさせる
			(*fr).f = FR_BOUND_F;
			(*fr).p_prev.y = (*fr).p.y;
		}
	}
}
void draw_atari()
{
	char i;
	char fr_y;
	Fruit *fr;
	char x;
	for (i=0; i<conf.fruits_n; i++) {
		fr = &(fruits[i]);
		fr_y = (*fr).p.y + FR_RIPE_DIA;
		for (x=(*fr).p.x+FR_RIPE_R-1; x>=(*fr).p.x-1; x--) {
			plot(x, fr_y, 0x00);
		}
	}
}
// フルーツとの当たり判定
void check_collision_fruits() {
	char i;
	char y;
	Fruit *fr;

	for (i=0; i<conf.fruits_n; i++) {
		fr = &(fruits[i]);
		// もしカゴの枠ならバウンド
		if ((*fr).f != FR_DROPPING_F) {
			(*fr).f = FR_DROPPING_F;
		}
		check_collision_basket_fruit(fr);

		// もしカゴの中ならスコアプラス
		if (pat[(int)(*fr).p.y][(int)(*fr).p.x] == BASKET_COLOR) {
			score++;
			set_fruit(i);
		}
		// RIPEの位置なら
		//if (pat[(*fr).p.y][(*fr).p.x] == FR_COLOR_RIPE) 
	}
}
//==============================
// ゲームの初期化関数 INIT
//==============================
void game_init()
{
	int i;

	// チャタリング対策済みボタン変数
	C_U_BTN = 1;
	C_D_BTN = 1;
	C_L_BTN = 1;
	C_R_BTN = 1;
	C_BTN1 = 1;
	C_BTN2 = 1;
	cloop_u_btn = 0;		// チャタリング防止用
	cloop_d_btn = 0;		// チャタリング防止用

	lcnt_fruits_grow = 0;

	hvester.p.x = PLAYER_X_DEF;
	hvester.p.y = PLAYER_Y_DEF;
	hvester.p_prev.x = hvester.p.x;
	hvester.p_prev.y = hvester.p.y;
	hvester.turnRight = 1;
	basket.p.y = hvester.p.y - 2;
	basket.size.w = 6;
	basket.size.h = 8;
	draw_basket();

	for (i=0; i<FRUITS_MAX; i++) {
		fruits[i].state = FR_STATE_NONE;
	}
	set_fruit(0);

	conf.level = 1;
	score = 0;
}

// counterが1以上なら1減らし、
// 0になったらflagを0にする
void loop_chatter(unsigned char *counter, char *flag) {
	if (*counter > 0) {
		(*counter)--;
		if (*counter == 0) {
			// U_BTNが確定した
			*flag  = 0;
		}
	}
}

//==============================
// ゲームのメインの処理の関数 MAIN
// 呼ばれた後、毎回disp_frame()が呼ばれている。
//==============================
unsigned char tmp=5;
char tmpf=1;
void game_main()
{
	unsigned char *counter;
	char *flag;
	if (!BTN1) { set_fruit(0); }
	if (!U_BTN && cloop_u_btn==0) {
		cloop_u_btn = chat_UP;
		printf("set chat_UP\n");
	}
	loop_chatter(&cloop_u_btn, &C_U_BTN);
	loop_chatter(&cloop_d_btn, &C_U_BTN);

	// U_BTNが押されたら(チャタリング対策済み)
	// レベルを上げる
	if (!C_U_BTN) {
		C_U_BTN = 1;
		if (conf.level < 8) {
			conf.level++;
		}
		printf("U_BTN CREDIBLE\n");
	}
	if (!C_D_BTN) {
		C_D_BTN = 1;
		if (conf.level > 1) {
			conf.level--;
		}
		printf("D_BTN CREDIBLE\n");
	}

	check_level();



	// フルーツを成長させる
	if (++lcnt_fruits_grow == LCOUNT_FRUITS_GROW) {
		lcnt_fruits_grow = 0;
		grow_fruits();
	}
	// フルーツを落とす
	drop_fruits();

	// 収穫者をうごかす
	move_harvester();
	move_basket();				// カゴをうごかす

	// 当たり判定
	check_collision_fruits();	// フルーツとの当たり判定
	
	// 画面クリア
	draw_back();
	//draw_atari();
	// フルーツを描く
	draw_fruits();
	draw_basket();
	// 自機を描く
	draw_harvester();
	//draw_line(5,5, 40,50, 0x00);
	//printf("end main().");
}

