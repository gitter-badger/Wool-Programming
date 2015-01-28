/*----------------------*
 *	Robot Programming 3	*
 *						*
 *	Robot Kick			*
 *						*
 *	1426107 �����đ�	*
 *----------------------*/

#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL\glut.h>

static GLint n = 100; //�{�[���̒[�_��
static GLdouble ball_x = 20.0; //�{�[���̏���x���W
static GLdouble ball_y = 50.0; //�{�[���̏���y���W
const GLdouble r = 5.0; //�{�[���̔��a
static GLint line = 3; //�{�[���̃��C����

static GLdouble kickang = -50.0; //���̏����p�x
const GLdouble toe_wigth = 20.0;	//�ܐ�̒���
const GLdouble toe_height = 20.0; //�ܐ�̍���
const GLdouble leg_wigth = 30.0; //�����̒���
const GLdouble leg_len = 50.0; //���̒���
static GLdouble leg_x = -20;	//���̏���x���W
static GLdouble leg_y = 80;	//���̏���y���W
static GLdouble leg_speed=0; //���̑��x
const GLdouble e = 0.6; //�����W��
static GLdouble speed_x = 0; //�{�[����x���W�ɑ΂���X�s�[�h
static GLdouble speed_y = 0; //�{�[����y���W�ɑ΂���X�s�[�h

static GLdouble v = 0;

const GLdouble size = 100.0; //�E�B���h�E�̃T�C�Y
const GLdouble edgesize = 5.0; //�t���[���̃T�C�Y


const GLdouble gravity = 9.8; //�d�͉����x
static GLdouble ang = 0.0; //�{�[���̉�]�p�x
GLdouble edgesize_master; //�t���[���̍��W�֌W

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
		rate = (double)i / n; //�䗦�̎Z�o
		rad = (360 * rate) * (M_PI / 180.0); //�p�x�ɔ䗦�������āA���W�A���ɕϊ�
		x_plot = Radius * cos(rad); //cos�ɂ���ă{�[����x���W�����߂�
		y_plot = Radius * sin(rad); //sin�ɂ���ă{�[����y���W�����߂�
		glVertex2d(x_plot, y_plot); //���߂����W���v���b�g
	}
	glEnd();
}

void display(void) //�t���[���A�{�[���A���̕`��
{
	GLint i; //for���p�ϐ�
	GLdouble rad = M_PI / 180; //���W�A��
	const GLdouble shin = leg_len - toe_height; //���˂̒���
	const GLdouble ankle = leg_wigth - toe_wigth; //����

	leg_point1[0] = toe_wigth*cos(kickang * rad) + shin*sin(kickang*rad) + leg_x;
	leg_point1[1] = toe_wigth*sin(kickang * rad) - shin*cos(kickang * rad) + leg_y;
	leg_point2[0] = toe_wigth*cos(kickang * rad) + leg_len*sin(kickang*rad) + leg_x;
	leg_point2[1] = toe_wigth*sin(kickang * rad) - leg_len*cos(kickang * rad) + leg_y;

	//�F�o�b�t�@�̃N���A
	glClear(GL_COLOR_BUFFER_BIT);

	//�t���[��

	//�t���[���`��̂��߂̍s��X�^�b�N
	glPushMatrix();
	//��
	glColor3d(0.0, 0.0, 0.0);
	//�t���[���̃T�C�Y���E�B���h�E���edgesize��������������
	edgesize_master = size - edgesize;
	//�����Ȃ���
	glBegin(GL_LINE_LOOP);
	//���_���w��
	glVertex2d(-edgesize_master, -edgesize_master);
	glVertex2d(-edgesize_master, edgesize_master);
	glVertex2d(edgesize_master, edgesize_master);
	glVertex2d(edgesize_master, -edgesize_master);
	glEnd();
	//�s��X�^�b�N��߂�
	glPopMatrix();

	//��

	//���`��̂��߂̍s��X�^�b�N
	glPushMatrix();
	//���̏����ʒu
	glTranslated(leg_x, leg_y, 0);
	//���̉�]
	glRotated(kickang, 0.0, 0.0, 1.0);
	//��
	glColor3d(0.0, 0.0, 1.0);
	//�����Ȃ��郂�[�h
	glBegin(GL_LINE_LOOP);
	glVertex2d(0.0, 0.0);
	glVertex2d(0.0, -shin);
	glVertex2d(toe_wigth, -shin);
	glVertex2d(toe_wigth, -shin - toe_height);
	glVertex2d(toe_wigth - leg_wigth, -shin - toe_height);
	glVertex2d(toe_wigth - leg_wigth, -shin - toe_height + leg_len);
	glVertex2d(toe_wigth - leg_wigth + ankle, -shin - toe_height + leg_len);
	//���_�̎w��̏I��
	glEnd();

	//�s��X�^�b�N��߂�
	glPopMatrix();

	//�{�[��

	//�{�[���`��̂��߂̍s��X�^�b�N
	glPushMatrix();
	//�{�[���̉^��
	glTranslated(ball_x, ball_y, 0);
	//�{�[���̉�]
	glRotated(ang, 0.0, 0.0, -1.0);
	//��
	glColor3d(0.0, 1.0, 0.0);
	Circle(r);
	//��
	glColor3d(1.0, 0.0, 0.0);
	//���C��������
	glBegin(GL_LINES);
	for (i = 0; i < 180; i += 180 / line){
		glVertex2d(r*cos(i*rad), r*sin(i*rad));
		glVertex2d(r*cos((i + 180)*rad), r*sin((i + 180)*rad));
	}
	glEnd();
	//�s��X�^�b�N��߂�
	glPopMatrix();

	glutSwapBuffers();
}

//�Փ˔���
int Collision_Detection(GLdouble point1[],GLdouble point2[]){

	//�ܐ�̏�Fp, �ܐ�̉��Fq, �{�[���̒��S�Fm

	static GLdouble pm[2], pq[2], qm[2];	//�x�N�g��
	static GLdouble d, pqxpm, pmpq, qmpq;	//�ܐ�ƃ{�[���̋����A�x�N�g��pm�ƃx�N�g��pq�̊O�ρA�x�N�g��pm�ƃx�N�g��pq�̓��ρA�x�N�g��qm�ƃx�N�g��pq�̓���
	static GLdouble norm_pm, norm_qm;	//�x�N�g��pm�̑傫��, �x�N�g��pq�̑傫��

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
	static GLdouble dt = 0.002; //���ԊԊu
	static GLdouble speed_rate; //�{�[���̉�]�Ԋu�֌W
	GLdouble Circumference = 2 * r * M_PI; //�{�[���̉~��
	const GLdouble rad = M_PI / 180;

	//���̐U��؂�
	if (kickang < 45){
		kickang += 0.05;
		leg_speed += kickang*dt;
	}

	if (Collision_Detection(leg_point1,leg_point2)){
		ballstart = 1;
	}

	//�{�[���ɓ���������
	if (ballstart){
		ball_x += speed_x*dt; //���ړ�
		speed_rate = 360.0 * dt*speed_x;
		ang += speed_rate / Circumference; //�{�[���̉�]

		//�{�[����360�x��]������
		if (ang > 360)
			ang -= 360;

		//�E�̃t���[���ɓ���������
		if (ball_x > edgesize_master - r){
			speed_x *= -e;
			ball_x = edgesize_master - r;
		}
		//���̃t���[���ɓ���������
		else if (ball_x < -edgesize_master + r){
			speed_x *= -e;
			ball_x = -edgesize_master + r;
		}

		speed_y = speed_y - 9.8*dt; //�X�s�[�h
		ball_y += speed_y*dt; //�c�ړ�

		//���̃t���[���ɓ���������
		if (ball_y < -edgesize_master + r){
			speed_y *= -e;
			ball_y = -edgesize_master + r;
		}
		//�n�ʂɒ����Ă���
		if (ball_y == -edgesize_master + r){
			if (speed_x > 0)
				speed_x -= 0.002; //���C
			else if (speed_x < 0)
				speed_x += 0, 002; //���C
		}
	}
	else{
		v = abs(leg_speed); //���̊p�x�ɂ���ă{�[����x���W�̑��x�ɑ����Ă�
		speed_x = v*cos(kickang*rad);
		speed_y = v*sin(kickang*rad);
	}

	glutPostRedisplay(); //�ĕ`��

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
	//��
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
	glOrtho(-size, size, -size, size, -1.0, 1.0); //�ˉe�ϊ�
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mouse(int button, int state, int x, int y){
	switch (button) {
		case GLUT_LEFT_BUTTON: //���N���b�N
			if (state == GLUT_DOWN) //�N���b�N������
				glutIdleFunc(simu); //simu�֐��Ăяo��
			break;
		case GLUT_MIDDLE_BUTTON: //�z�C�[���N���b�N
			if (state == GLUT_DOWN){ //�N���b�N������
				ball_x = ball_x_init;
				ball_y = ball_y_init;
				speed_x = speed_x_init;
				speed_y = speed_y_init;
				kickang = kickang_init;
				leg_speed = 0;
				v = 0;
				ballstart = 0;

				glutPostRedisplay();
				glutIdleFunc(NULL); //�`��~�߂�
			}
			break;
		default:
			break;
	}
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == '\x1b') exit(0); //ESC��������I��
	if (key == '\xd') exit(0); //ENTER��������I��
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