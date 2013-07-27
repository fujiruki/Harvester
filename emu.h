// NnctPicGameのエミュ
// 2013年6月26日　藤田晴樹
//
/* +-------------------------+--------+
 * |+-----------------------+|        |
 * ||                       ||Control |
 * ||      Display          ||        |
 * ||                       ||        |
 * |+-----------------------+|        |
 * |+-----------------------+|        |
 * ||      Debug Console    ||        |
 * |+-----------------------+|        |
 * +-------------------------+--------+
 *
 * エミュレータのための関数はemu_xxx()をつける。
 *
 * disp_frame()はpat[][]をemu_disp_pat[][]に代入する。
 * display() で常にemu_disp_pat[][]やメニューを描画し続ける。
 * disp_frame()が入っているemu_loop()はSLEEP_TIME毎に、
 *       display()は60fpsで別々に呼ばれる。
 */

#ifndef __NNCTPICGAME_EMU_H__
#define __NNCTPICGAME_EMU_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>
#include <pthread.h>

//===========================================
// NnctPicGameと同じ定数の宣言
//===========================================
#define H_SIZE	60	// 横方向のセルの数
#define V_SIZE	60	// 縦方向のセルの数

//===========================================
// NnctPicGameにはない
// 独自の定数の宣言
//===========================================
#define SLEEP_TIME 25					// disp_frame()毎にsleepする時間[ms]。実機に合わせて調整する。
#define REDISPLAY_FRAME 16		// 画面全体の描画間隔。1/60fps=0.0166[s]=17[ms]


#define BDISP_X 0
#define BDISP_Y 0
#define BDISP_W 480
#define BDISP_H 480
#define BDEBUG_X 0
#define BDEBUG_Y (BDISP_H+10)
#define BDEBUG_W BDISP_W
#define BDEBUG_H 200
#define BCONTROL_X (BDISP_X+BDISP_Y+10)
#define BCONTROL_Y 0
#define BCONTROL_W 200
#define BCONTROL_H (BDISP_H+BDEBUG_H+10)
//#define WINDOW_W	(BDISP_W+BCONTROL_W)
//#define WINDOW_H	(BDISP_H+BDEBUG_W)
#define WINDOW_W	BDISP_W
#define WINDOW_H	BDISP_H

//== キーコンフィグ ==
#define KEY_BTN1	'j'
#define KEY_BTN2	'k'
#define KEY_U_BTN	'w'
#define KEY_D_BTN	's'
#define KEY_L_BTN	'a'
#define KEY_R_BTN	'd'
#define KEY_ESC		'\033'			// 終了ボタンはESC(\033)

//===========================================
// エミュ実装のための
// 独自構造体の宣言
//===========================================
typedef struct {
	double x, y;
} posd;
typedef struct {
	double w, h;
} sized;
typedef struct {
	int x, y, w, h;
} recti;
typedef struct {
	double x, y, w, h;	//left, right, top, bottom
} rectd;

//===========================================
// 実機に実装されている
// 変数のextern宣言
//===========================================
extern int pat[V_SIZE][H_SIZE];						// VRAM（この配列に入れた色が描画される。）
extern int U_BTN, R_BTN, D_BTN, L_BTN;				// ボタンは1でオフ、0でオン
extern int BTN1, BTN2;

//===========================================
// 実機に実装されていない独自の
// 変数のextern宣言
//===========================================
extern char EXIT;	// 1ならばエミュを終了
extern rectd bdisp;		// box display
extern rectd bdebug;		// box display
extern rectd bcontrol;		// box display
extern rectd disp_ortho;	//正射影表示する範囲
extern sized cell_size;	// セルの一辺の長さ
extern sized cell_box;

extern int emu_disp_pat[V_SIZE][H_SIZE];	// disp_frame()でこの内容が表示される。
extern double border_w;	// 枠線の太さ
extern double border_rate;	// セルの隙間の幅=border_rate * cell_size


//===========================================
// 実機に実装されている
// 関数のプロトタイプ宣言
//===========================================
void disp_frame();									// pat配列の内容を描画する。

//===========================================
// 実機に実装されていない独自の
// 関数のプロトタイプ宣言
//===========================================
void sleep();
void pat2rgb(int pat, double *r, double *g, double *b);		// pat配列への特殊な色指定を、RGB表現へ変換する。
void Emu_draw_rect(double x, double y, double w, double h, double r, double g, double b, char fill);
int wait_ms(long t);

void print_bit(int n); 


#endif // __NNCTPICGAME_EMU_H__

