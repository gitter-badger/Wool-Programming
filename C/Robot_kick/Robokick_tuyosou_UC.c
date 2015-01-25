/*----------------------------------------------------------------------------------------------------------------------------------------------*
 * Robot Programming Report 3																													*
 * Robot kick																																	*
 *																																				*
 * School ID : 1426107																															*
 *																																				*
 * Name : Syouta Hirama																															*
 *																																				*
 * glPushMatrix()とglPopMatrix()の間に描きたいオブジェクト作る。																				*
 * これを複数作ることによって他のオブジェクトに干渉しない																						*
 *																																				*
 * glRotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z)																				*
 * オブジェクトを回転させる																														*
 * angleで角度指定																																*
 * x,y,zは回転する軸を指定																														*
 *																																				*
 * glTranslated (GLdouble x, GLdouble y, GLdouble z)																							*
 * オブジェクトを移動させる																														*
 * x,y,zには、それぞれ移動させたい座標を指定する																								*
 *																																				*
 * glPushMatrix(void)																															*
 * オブジェクトを行列スタックに保存する																											*
 *																																				*
 * glPopMatrix(void)																															*
 * スタックに保存したオブジェクトを取り出す																										*
 * glPushMatrix()と併用することで他のオブジェクトに干渉せずに描画することができる																*
 *																																				*
 * glColor3d(GLdouble red, GLdouble green, GLdouble blue)																						*
 * オブジェクトの色を指定する																													*
 * red,green,blueには0～1の値を指定する																											*
 *----------------------------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------------------------*
 * モードが1の時は、足がまっすぐのまま前に進んでボールに当たったらボールが動き始めて、足が元の位置に戻っていきます								*
 *																																				*
 * モードが2の時は、足が回転し、ボールに当たったらボールが動き出し、足の角度が45度になるまで回転し続けます(止まる角度は変更可能)				*
 *----------------------------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------------------------*
 * 衝突判定について																																*
 *																																				*
 * 衝突判定はつま先が円にしてあるので、つま先の円の中心座標を出し、それとボールの中心座標を利用して公式に当てはめることでできます				*
 *																																				*
 * (ボールの中心のx座標 - つま先の円の中心のx座標)^2 + (ボールの中心のy座標 - つま先の円の中心のy座標)^2 <= (ボールの半径 + つま先の円の半径)	*
 * これは数Ⅱの範囲の円の重なりの公式を使っています																								*
 *----------------------------------------------------------------------------------------------------------------------------------------------*/


#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

static GLfloat ang = 0.0;	//ボールの回転
static GLdouble yoko = -10, tate = 15;	//ボールの座標
static GLdouble leg_yoko = -30, leg_tate = 15+10;	//足の座標
static GLdouble leg_yoko_init;	//足の初期位置
static double n = 100;	//端点数
static GLdouble r = 5;	//ボールの半径
static GLdouble kickang=-30.0;	//足の初期角度
static GLdouble toe_point_x, toe_point_y;	//つま先の円の座標

static int mode = 0;	//モード選択

//円を描く
void Circle(GLdouble Radius){	//引数に円の大きさを指定
	GLdouble x_plot, y_plot;	//プロット座標
	GLdouble rate, rad;	//比率、ラジアン
	int i;	//for用
	glBegin(GL_POLYGON);	//ポリゴンモード
	for (i = 0; i < n; i++){
		rate = (double)i / n; //比率の算出
		rad = (360 * rate) * (M_PI / 180.0); //角度に比率をかけて、ラジアンに変換
		x_plot = Radius * cos(rad); //cosによってボールのx座標を決める
		y_plot = Radius * sin(rad); //sinによってボールのy座標を決める
		glVertex2d(x_plot, y_plot); //決めた座標をプロット
	}
	glEnd();
}

void display(void)
{
	const GLdouble rad = M_PI / 180;	//ラジアン

	toe_point_x = 0*cos(kickang*rad) + 15 * sin(kickang*rad) + leg_yoko;	//つま先の円の中心のx座標
	toe_point_y = 0*sin(kickang*rad) - 15 * cos(kickang*rad) + leg_tate;	//つま先の円の中心のy座標

	glClear(GL_COLOR_BUFFER_BIT);	//色バッファをクリア

	glPushMatrix();	//スタックに保存
	glColor3d(1.0, 1.0, 0.0);	//黄色
	glTranslated(yoko, tate, 0);	//ボールのx座標を変数yokoの値の場所へ、y座標を変数tateの値の場所へ
	glRotatef(ang, 0.0, 0.0, -1.0);	//z軸に対して回転
	Circle(r);	//ボール描画
	//ボールの線
	glBegin(GL_LINES);	//線をつなげるモード
	glColor3d(0, 0, 1);	//青
	glVertex2d(-r, 0);	//ボールのライン
	glVertex2d(r, 0);	//ボールのライン
	glEnd();	//指定終了
	glPopMatrix();	//スタックから取り出す

	glPushMatrix();	//スタックに保存
	glColor3d(1, 0, 0);	//赤
	glTranslated(leg_yoko, leg_tate, 0);	//足のx座標を変数leg_yokoの値の場所へ、y座標を変数leg_tateの値の場所へ
	glRotated(kickang, 0, 0, 1);	//足を回転させる
	glRectd(-7.5, -20, 0, 0);	//四角作る
	glTranslated(0,-20 + r,0);	//つま先の円の位置を指定
	Circle(5);	//円の描画
	glPopMatrix();	//スタックから取り出す

	glutSwapBuffers();	//バッファ入れ替え
}

void simu(void)
{
	static int ball_start = 0;	//ボールのスタートフラグ
	static GLdouble v, xv, yv;	//初期速度、速度のx成分、速度のy成分
	static GLdouble dt = 0.002, masatu = -0.002;	//時間間隔、摩擦係数
	static GLdouble speedrate;	//回転比率
	const GLdouble e = 0.6, ensyu = 2 * r*M_PI, rad = M_PI / 180;	//反発係数、円周
	static GLdouble degree = 0;	//ボールが上がる角度
	static GLdouble leg_speed = 0.05;	//足の速度

	//モードが1のとき
	if (mode == 1){
		//元の座標に戻るまで足を動かす
		if (leg_yoko >= leg_yoko_init){
			leg_yoko += leg_speed;
		}
	}
	//モードが2のとき
	else{
		//45度になるまで回転させる
		if (kickang < 45)
			kickang += 0.05;
	}

	//衝突判定
	//つま先の円の半径とボールの半径で判定
	if (pow(yoko - toe_point_x, 2) + pow(tate - toe_point_y, 2) < pow(5 + r, 2)){
		degree = atan2(fabs(tate - leg_tate), fabs(yoko - leg_yoko)) / M_PI * 180;	//当たった時の角度を計算
		//突くようにけるとめり込むので
		if (mode == 1){
			leg_yoko = yoko - 10;	//めり込み解除
		}
		v =20;	//速度に代入(ここは適当)
		xv = v*cos(degree*rad);		//x成分の速度
		yv = v*sin(degree*rad);	//y成分の速度
		leg_speed *= -1;	//足の移動する方向を反転

		ball_start = 1;	//ボールが動き始めるフラグ
	}

	//ボールの動き
	if (ball_start){
		speedrate = 360 * dt*xv;	//回転比率
		ang += speedrate / ensyu;	//滑らないように回転
		if (ang>360)	//360度を超えた時に360度引いて、角度を戻す
			ang -= 360;

		yoko += xv*dt;	//ボールのx座標
		//右の壁にあたったら
		if (yoko>50 - r){
			xv *= -e;	//速度を跳ね返り係数をかけて反転
			masatu *= -1;	//摩擦方向反転
			yoko = 50 - r;	//めり込みをなくす
		}
		//左の壁にあたったら
		if (yoko<-50 + r){
			xv *= -e;	//速度を跳ね返り係数をかけて反転
			masatu *= -1;	//摩擦方向反転
			yoko = -50 + r;	//めり込みをなくす
		}

		yv = yv - 9.8*dt;	//ボールのy速度
		tate += yv*dt;	//ボールのy座標
		//下に着いたら
		if (tate<-50 + r){
			yv *= -e;	//速度を跳ね返り係数をかけて反転
			tate = -50 + r;	//めり込みをなくす
		}
		//下に接触している時
		if (tate == -50 + r){
			xv += masatu;	//摩擦
			if (xv>-0.1&&xv<0.1){	//ボール停止
				xv = 0;
				masatu = 0;
			}
		}
	}

	glutPostRedisplay();	//再描画
}

//初期関数
void init(void)
{
	//モード選択
	printf("モードを選択してください\n");
	printf("1：突くように蹴る, 2：振り上げて蹴る >");
	scanf("%d", &mode);	//モードを選択させる
	glClearColor(0.0, 0.0, 0.0, 0.0);	//黒
	glShadeModel(GL_FLAT);
	leg_yoko_init = leg_yoko;	//足の初期位置代入
	if (mode == 1) kickang = 0;	//突くように蹴るときは足はまっすぐ
}

//ウィンドウのサイズが変わった時にリサイズ
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);	//大きさ決める
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//マウス
void mouse(int button, int state, int x, int y){
	switch (button) {
		//左クリック：開始
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_DOWN)
				glutIdleFunc(simu);
			break;
		//右クリック：停止
		case GLUT_RIGHT_BUTTON:
			if (state == GLUT_DOWN)
				glutIdleFunc(NULL);
			break;
		default:
			break;
	}
}

//キーボード
void keyboard(unsigned char key, int x, int y)
{
	if (key == '\x1b') exit(0);	//ESCで終了
	if (key == '\xd') exit(0);	//ENTERで終了
	if (key == 'd') glutIdleFunc(simu);	//dで開始
	if (key == 's') glutIdleFunc(NULL);	//sで停止
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(400, 400);	//ウィンドウサイズ
	glutInitWindowPosition(100, 100);	//ウィンドウの場所
	glutCreateWindow("Robokick");	//ウィンドウのタイトル
	init();
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}