/*----------------------*
 *	Robot Programming 3	*
 *						*
 *	Robot Kick			*
 *						*
 *	1426107 平間翔大	*
 *----------------------*/

#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL\glut.h>

static GLint n = 100; //ボールの端点数
static GLdouble ball_x = 20.0; //ボールの初期x座標
static GLdouble ball_y = 50.0; //ボールの初期y座標
const GLdouble r = 5.0; //ボールの半径
static GLint line = 3; //ボールのライン数

static GLdouble kickang = -50.0; //足の初期角度
const GLdouble toe_wigth = 20.0;	//つま先の長さ
const GLdouble toe_height = 20.0; //つま先の高さ
const GLdouble leg_wigth = 30.0; //足裏の長さ
const GLdouble leg_len = 50.0; //足の長さ
static GLdouble leg_x = -20;	//足の初期x座標
static GLdouble leg_y = 80;	//足の初期y座標
static GLdouble leg_speed=0; //足の速度
const GLdouble e = 0.6; //反発係数
static GLdouble speed_x = 0; //ボールのx座標に対するスピード
static GLdouble speed_y = 0; //ボールのy座標に対するスピード

static GLdouble v = 0;

const GLdouble size = 100.0; //ウィンドウのサイズ
const GLdouble edgesize = 5.0; //フレームのサイズ


const GLdouble gravity = 9.8; //重力加速度
static GLdouble ang = 0.0; //ボールの回転角度
GLdouble edgesize_master; //フレームの座標関係

GLdouble kickang_init;
GLdouble ball_x_init;
GLdouble ball_y_init;
GLdouble speed_x_init;
GLdouble speed_y_init;
static GLdouble leg_point1[2];
static GLdouble leg_point2[2];

static int ballstart = 0;

void mouse(int, int, int, int);

void Circle(GLdouble Radius){
	GLdouble x_plot, y_plot;
	GLdouble rate, rad;
	int i;
	glBegin(GL_POLYGON);
	for (i = 0; i < n; i++){
		rate = (double)i / n; //比率の算出
		rad = (360 * rate) * (M_PI / 180.0); //角度に比率をかけて、ラジアンに変換
		x_plot = Radius * cos(rad); //cosによってボールのx座標を決める
		y_plot = Radius * sin(rad); //sinによってボールのy座標を決める
		glVertex2d(x_plot, y_plot); //決めた座標をプロット
	}
	glEnd();
}

void display(void) //フレーム、ボール、足の描画
{
	GLint i; //for文用変数
	GLdouble rad = M_PI / 180; //ラジアン
	const GLdouble shin = leg_len - toe_height; //すねの長さ
	const GLdouble ankle = leg_wigth - toe_wigth; //足首

	leg_point1[0] = toe_wigth*cos(kickang * rad) + shin*sin(kickang*rad) + leg_x;
	leg_point1[1] = toe_wigth*sin(kickang * rad) - shin*cos(kickang * rad) + leg_y;
	leg_point2[0] = toe_wigth*cos(kickang * rad) + leg_len*sin(kickang*rad) + leg_x;
	leg_point2[1] = toe_wigth*sin(kickang * rad) - leg_len*cos(kickang * rad) + leg_y;

	//色バッファのクリア
	glClear(GL_COLOR_BUFFER_BIT);

	//フレーム

	//フレーム描画のための行列スタック
	glPushMatrix();
	//黒
	glColor3d(0.0, 0.0, 0.0);
	//フレームのサイズをウィンドウよりedgesizeだけ小さくする
	edgesize_master = size - edgesize;
	//線をつなげる
	glBegin(GL_LINE_LOOP);
	//頂点を指定
	glVertex2d(-edgesize_master, -edgesize_master);
	glVertex2d(-edgesize_master, edgesize_master);
	glVertex2d(edgesize_master, edgesize_master);
	glVertex2d(edgesize_master, -edgesize_master);
	glEnd();
	//行列スタックを戻す
	glPopMatrix();

	//足

	//足描画のための行列スタック
	glPushMatrix();
	//足の初期位置
	glTranslated(leg_x, leg_y, 0);
	//足の回転
	glRotated(kickang, 0.0, 0.0, 1.0);
	//青
	glColor3d(0.0, 0.0, 1.0);
	//線をつなげるモード
	glBegin(GL_LINE_LOOP);
	glVertex2d(0.0, 0.0);
	glVertex2d(0.0, -shin);
	glVertex2d(toe_wigth, -shin);
	glVertex2d(toe_wigth, -shin - toe_height);
	glVertex2d(toe_wigth - leg_wigth, -shin - toe_height);
	glVertex2d(toe_wigth - leg_wigth, -shin - toe_height + leg_len);
	glVertex2d(toe_wigth - leg_wigth + ankle, -shin - toe_height + leg_len);
	//頂点の指定の終了
	glEnd();

	//行列スタックを戻す
	glPopMatrix();

	//ボール

	//ボール描画のための行列スタック
	glPushMatrix();
	//ボールの運動
	glTranslated(ball_x, ball_y, 0);
	//ボールの回転
	glRotated(ang, 0.0, 0.0, -1.0);
	//緑
	glColor3d(0.0, 1.0, 0.0);
	Circle(r);
	//赤
	glColor3d(1.0, 0.0, 0.0);
	//ラインを入れる
	glBegin(GL_LINES);
	for (i = 0; i < 180; i += 180 / line){
		glVertex2d(r*cos(i*rad), r*sin(i*rad));
		glVertex2d(r*cos((i + 180)*rad), r*sin((i + 180)*rad));
	}
	glEnd();
	//行列スタックを戻す
	glPopMatrix();

	glutSwapBuffers();
}

//衝突判定
int Collision_Detection(GLdouble point1[],GLdouble point2[]){

	//つま先の上：p, つま先の下：q, ボールの中心：m

	static GLdouble pm[2], pq[2], qm[2];	//ベクトル
	static GLdouble d, pqxpm, pmpq, qmpq;	//つま先とボールの距離、ベクトルpmとベクトルpqの外積、ベクトルpmとベクトルpqの内積、ベクトルqmとベクトルpqの内積
	static GLdouble norm_pm, norm_qm;	//ベクトルpmの大きさ, ベクトルpqの大きさ

	pm[0] = ball_x - point1[0];
	pm[1] = ball_y - point1[1];

	pq[0] = point2[0] - point1[0];
	pq[1] = point2[1] - point1[1];

	qm[0] = ball_x - point2[0];
	qm[1] = ball_y - point2[1];

	pqxpm = pq[0] * pm[1] - pq[1] * pm[0];

	norm_pm = hypot(pm[0], pm[1]);
	norm_pm = hypot(qm[0], qm[1]);

	d = fabs(pqxpm / sqrt(pow(pq[0], 2) + pow(pq[1], 2)));

	pmpq = pm[0] * pq[0] + pm[1] * pq[1];
	qmpq = qm[0] * pq[0] + qm[1] * pq[1];

	return ((d <= r) && (((pmpq * qmpq) < 0) || (norm_pm < r) || (norm_qm < r))) ? 1 : 0;

}



void simu(void)
{
	static GLdouble dt = 0.002; //時間間隔
	static GLdouble speed_rate; //ボールの回転間隔関係
	GLdouble Circumference = 2 * r * M_PI; //ボールの円周
	const GLdouble rad = M_PI / 180;

	//足の振り切り
	if (kickang < 45){
		kickang += 0.05;
		leg_speed += kickang*dt;
	}

	if (Collision_Detection(leg_point1,leg_point2)){
		ballstart = 1;
	}

	//ボールに当たったら
	if (ballstart){
		ball_x += speed_x*dt; //横移動
		speed_rate = 360.0 * dt*speed_x;
		ang += speed_rate / Circumference; //ボールの回転

		//ボールが360度回転した時
		if (ang > 360)
			ang -= 360;

		//右のフレームに当たったら
		if (ball_x > edgesize_master - r){
			speed_x *= -e;
			ball_x = edgesize_master - r;
		}
		//左のフレームに当たったら
		else if (ball_x < -edgesize_master + r){
			speed_x *= -e;
			ball_x = -edgesize_master + r;
		}

		speed_y = speed_y - 9.8*dt; //スピード
		ball_y += speed_y*dt; //縦移動

		//下のフレームに当たったら
		if (ball_y < -edgesize_master + r){
			speed_y *= -e;
			ball_y = -edgesize_master + r;
		}
		//地面に着いてたら
		if (ball_y == -edgesize_master + r){
			if (speed_x > 0)
				speed_x -= 0.002; //摩擦
			else if (speed_x < 0)
				speed_x += 0, 002; //摩擦
		}
	}
	else{
		v = abs(leg_speed); //足の角度によってボールのx座標の速度に足してく
		speed_x = v*cos(kickang*rad);
		speed_y = v*sin(kickang*rad);
	}

	glutPostRedisplay(); //再描画

}

void menu(int value){
	switch (value){
		case 0:
			exit(0);
			break;
		case 1:
			glutIdleFunc(simu);
			break;
		case 2:
			glutIdleFunc(NULL);
			break;
		case 3:
			mouse(GLUT_MIDDLE_BUTTON, GLUT_DOWN, 0, 0);
			break;
		default:
			break;
	}
}

void menucreate(){
	glutCreateMenu(menu);
	glutAddMenuEntry("start", 1);
	glutAddMenuEntry("stop", 2);
	glutAddMenuEntry("reset", 3);
	glutAddMenuEntry("exit", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void init(void)
{
	//白
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glShadeModel(GL_FLAT);
	kickang_init = kickang;
	ball_x_init = ball_x;
	ball_y_init = ball_y;
	speed_x_init = speed_x;
	speed_y_init = speed_y;
	leg_speed = 0;
	ballstart = 0;
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-size, size, -size, size, -1.0, 1.0); //射影変換
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mouse(int button, int state, int x, int y){
	switch (button) {
		case GLUT_LEFT_BUTTON: //左クリック
			if (state == GLUT_DOWN) //クリックしたら
				glutIdleFunc(simu); //simu関数呼び出し
			break;
		case GLUT_MIDDLE_BUTTON: //ホイールクリック
			if (state == GLUT_DOWN){ //クリックしたら
				ball_x = ball_x_init;
				ball_y = ball_y_init;
				speed_x = speed_x_init;
				speed_y = speed_y_init;
				kickang = kickang_init;
				leg_speed = 0;
				v = 0;
				ballstart = 0;

				glutPostRedisplay();
				glutIdleFunc(NULL); //描画止める
			}
			break;
		default:
			break;
	}
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == '\x1b') exit(0); //ESC押したら終了
	if (key == '\xd') exit(0); //ENTER押したら終了
	if (key == 's') glutIdleFunc(simu);
	if (key == 'd') glutIdleFunc(NULL);
	if (key == 'r') mouse(GLUT_MIDDLE_BUTTON, GLUT_DOWN, 0, 0);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutDisplayFunc(display);
	menucreate();
	glutMainLoop();
	return 0;
}