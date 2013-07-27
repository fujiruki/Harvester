// NnctPicGameのエミュ
// 2013年6月26日　藤田晴樹
//

#include "emu.h"


int pat[V_SIZE][H_SIZE];			// VRAM
int U_BTN, R_BTN, D_BTN, L_BTN;				// ボタンは1でオフ、0でオン
int BTN1, BTN2;
char EXIT;									// (EXIT!=0) ? exit(0):;
int emu_disp_pat[V_SIZE][H_SIZE];

rectd bdisp = {BDISP_X, BDISP_Y, BDISP_W, BDISP_H};		// box display
rectd bdebug = {BDEBUG_X, BDEBUG_Y, BDEBUG_W, BDEBUG_H};		// box display
rectd bcontrol = {BCONTROL_X, BCONTROL_Y, BCONTROL_W, BCONTROL_H};		// box display

rectd disp_ortho;	//正射影表示する範囲
sized cell_size;	// セルの一辺の長さ
sized cell_box;
double border_w;	// 枠線の太さ
double border_rate=0/100.0;	// セルの隙間の幅=border_rate * cell_size


int wait_ms(long t)
{
	clock_t s_c, e_c;

	s_c = clock();
	while ((e_c=clock())-s_c < CLOCKS_PER_SEC/1000.0*t)
	{
		if (e_c == (clock_t)-1) {
			fprintf(stderr, "clock()が異常な戻り値。");
			return 1;
		}
	}

	return 0;
}


void disp_frame()
{
	int x, y;

	// 表示用の配列へpat[][]の内容を移す
	for (x=0; x<H_SIZE; x++) {
		for (y=0; y<H_SIZE; y++) {
			emu_disp_pat[y][x] = pat[y][x];
		}
	}

	wait_ms(SLEEP_TIME);
}


// pat[][]の要素(ggrrbb**(2))をrgbに分解する。
void pat2rgb(int draw_pat, double *r, double *g, double *b)
{
	int pat_color = draw_pat >> 2;
	
	// r,g,bは[0,3]の整数。これを[0,1]のfloatに治す。
	*b = (pat_color & 3) / 3.0;
	pat_color >>= 2;
	*r = (pat_color & 3) / 3.0;
	pat_color >>= 2;
	*g = (pat_color & 3) / 3.0;

	return;
}


void Emu_draw_rect(double x, double y, double w, double h, double r, double g, double b, char fill)
{
	glColor3d(r, g, b);
	if (fill>0) {
		glBegin(GL_POLYGON);
	} else {
		glBegin(GL_LINE_LOOP);
	}
	glVertex2d(x, y);
	glVertex2d(x+w, y);
	glVertex2d(x+w, y+h);
	glVertex2d(x, y+h);
	glEnd();
}

void emu_disp_cells()
{
	int x, y;
	double r, g, b;
	posd offset;

	offset.x = disp_ortho.x;
	offset.y = disp_ortho.y;
	for (x=0; x<H_SIZE; x++) {
		for (y=0; y<V_SIZE; y++) {
			// pat配列からrgb要素を取り出し、セルにその色を付ける
			pat2rgb(emu_disp_pat[y][x], &r, &g, &b);
			Emu_draw_rect(offset.x + x*cell_box.w +border_w, 
					offset.y + y*cell_box.h +border_w, cell_size.w, cell_size.h, r, g, b, 1);
		}
	}
}

// glut用の描画関数
void display(void)
{
	int x, y;
	double r,g,b;
	glClear(GL_COLOR_BUFFER_BIT);

	//Emu_draw_rect(bdisp.x, bdisp.y, bdisp.w, bdisp.h, 1,0,0,1);
	emu_disp_cells();

	glutSwapBuffers();
}

// 描画するセルや枠線の大きさを計算する。
void set_cell_size()
{
	// 1セルの一辺の長さ
	cell_size.w = disp_ortho.w/( H_SIZE + (H_SIZE+1)*border_rate );
	cell_size.h = disp_ortho.h/( V_SIZE + (V_SIZE+1)*border_rate );
	border_w = border_rate * cell_size.w;
	cell_box.w = border_w + cell_size.w;
	cell_box.h = border_w + cell_size.h;
}
void resize(int w, int h)
{
	//とりあえずウィンドウサイズの変更はないものとする。
	//bdisp.w = w;
	//bdisp.h = h/(double)w * bdisp.w;
	bdisp.w = w;
	bdisp.h = h;
	glViewport(0, 0, bdisp.w, bdisp.h);	// ウィンドウ全体をビューポートにする
	glLoadIdentity();		// 変換行列の初期化
	disp_ortho.w = w/200.0*2;
	disp_ortho.h = h/200.0*2;
	disp_ortho.y = -disp_ortho.h/2.0;
	disp_ortho.x = -disp_ortho.w/2.0;

	set_cell_size();			// セルや枠線の大きさを計算

	glOrtho(disp_ortho.x, disp_ortho.x+disp_ortho.w,
			disp_ortho.y+disp_ortho.h, disp_ortho.y, -1.0, 1.0);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case KEY_ESC: // ESCのASCIIコード
			if (KEY_ESC != 0) {
				EXIT = 0;
			}
			break;
		case KEY_BTN1:	// J:BTN1
			if (BTN1 != 0) {
				BTN1 = 0;
			}
			break;
		case KEY_BTN2:	// K:BTN2
			if (BTN2 != 0) {
				BTN2 = 0;
			}
			break;
		case KEY_U_BTN:
			if (U_BTN != 0) {
				U_BTN = 0;
			}
			break;
		case KEY_D_BTN:
			if (D_BTN != 0) {
				D_BTN = 0;
			}
			break;
		case KEY_L_BTN:
			if (L_BTN != 0) {
				L_BTN = 0;
			}
			break;
		case KEY_R_BTN:
			if (R_BTN != 0) {
				R_BTN = 0;
			}
			break;
		default:
			break;
	}
}
void keyboard_up(unsigned char key, int x, int y)
{
	switch (key)
	{
		case KEY_ESC: // ESCのASCIIコード
			if (KEY_ESC != 1) {
				EXIT = 1;
				exit(0);
			}
		case KEY_BTN1:	// J:BTN1
			if (BTN1 != 1) {
				BTN1 = 1;
			}
			break;
		case KEY_BTN2:	// K:BTN2
			if (BTN2 != 1) {
				BTN2 = 1;
			}
			break;
		case KEY_U_BTN:
			if (U_BTN != 1) {
				U_BTN = 1;
			}
			break;
		case KEY_D_BTN:
			if (D_BTN != 1) {
				D_BTN = 1;
			}
			break;
		case KEY_L_BTN:
			if (L_BTN != 1) {
				L_BTN = 1;
			}
			break;
		case KEY_R_BTN:
			if (R_BTN != 1) {
				R_BTN = 1;
			}
			break;
		default:
			break;
	}
}

void specialkey(int key, int x, int y)
{
	switch (key) {
	}
}
void specialkey_up(int key, int x, int y)
{
	switch (key) {
	}
}

void mouse(int button, int state, int x, int y)
{
	switch (button) {
		case GLUT_LEFT_BUTTON:
			break;
		case GLUT_MIDDLE_BUTTON:
			break;
		case GLUT_RIGHT_BUTTON:
			break;
		default:
			break;
	}
}

/*
// 実機上でのmain()の中のループの中身。
void *emu_loop(void* arg)
{
	harvester_init();
	while (EXIT == 0) {
		harvester_main();
		disp_frame();
	}
}
*/

// 実機上でのmain()の中のループの中身。
#ifdef __linux__
void *emu_loop(void *arg) {
#else
unsigned __stdcall emu_loop(void *arg) {
#endif

	harvester_init();
	while (EXIT == 0) {
		harvester_main();
		disp_frame();
	}

#ifdef __linux__
	return;
#else
	return 0;
#endif
}



// 画面全体を再描画する処理（REDISPLAY_FRAME間隔で呼び出される）
void display_loop()
{
	glutPostRedisplay();
}
// エミュレータのメニューやセルの描画のループ
void timer_display(int value)
{
	display_loop();
	glutTimerFunc(REDISPLAY_FRAME, timer_display, 0);
}

void init_emu(int *argc, char *argv[])
{
	int i,j;

	U_BTN = 1;
	D_BTN = 1;
	L_BTN = 1;
	R_BTN = 1;
	BTN1 = 1;
	BTN2 = 1;
	EXIT = 0;

	// 乱数の種を初期化して、
	// 本領発揮のために空回し
	srand((unsigned int)time(0));
	rand(); rand(); rand();
	rand(); rand();
	
	// glutの設定
	glutInitWindowSize(WINDOW_W, WINDOW_H);
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);	// RGBでの色指定
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutIgnoreKeyRepeat(GL_TRUE);	// キーの繰り返し入力は無視する
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboard_up);
	glutSpecialFunc(specialkey);		// 特殊キーを押した時
	glutSpecialUpFunc(specialkey_up);	// 特殊キーを離した時
	glutReshapeFunc(resize);
	glutMouseFunc(mouse);
	glutTimerFunc(REDISPLAY_FRAME, timer_display, 0);
	//glutTimerFunc(SLEEP_TIME, timer_prgress, 0);	// value=0(no mean)

	for (i=0; i<H_SIZE; i++) {
		for (j=0; j<V_SIZE; j++) {
			pat[j][i] = 0xff;
		}
	}
}

/*
int main(int argc, char *argv[])
{
	pthread_t game_thread;
	int game_thread_status;

	init_emu(&argc, argv);


	// ゲームループを別スレッドで回す
	game_thread_status = pthread_create(&game_thread, NULL, emu_loop, 0);
	if (game_thread_status!=0) {
		fprintf(stderr, "pthreadでのエラー");
		exit(-1);
	}

	glutMainLoop();
	return 0;
}
*/
int main(int argc, char *argv[])
{
#ifdef __linux__
	pthread_t game_thread;
#else
	int game_thread;
	unsigned dummy;
#endif
	int game_thread_status;

	init_emu(&argc, argv);


	// ゲームループを別スレッドで回す
#ifdef __linux__
	game_thread_status = pthread_create(&game_thread, NULL, emu_loop, 0);
#else // Windowsでマルチスレッド
	game_thread = _beginthreadex(NULL, 0, emu_loop, (void*)0,0, &dummy);
#endif

	// マルチスレッドのエラー処理
#ifdef __linux__
	if (game_thread_status!=0) {
		fprintf(stderr, "pthreadでのエラー");
		exit(-1);
	}
#else
	if (game_thread == 0) {
		fprintf(stderr, "Error: %s", strerror(game_thread));
	}
#endif


	glutMainLoop();
	return 0;
}


// 二進数を表示する
void print_bit(int n)
{
	int i, bit;
	printf("%d : ", n);
	//for (i=32; i>=0; i--) {
	for (i=0; i<=8; i++) {
		printf("%d",(n >> i) % 2);
		//putc(bit+'0');
	}
}
