/*----------------------------------------------------------------------------------------------------------------------------------------------*
 * Robot Programming Report 3																													*
 * Robot kick																																	*
 *																																				*
 * School ID : 1426107																															*
 *																																				*
 * Name : Syouta Hirama																															*
 *																																				*
 * glPushMatrix()��glPopMatrix()�̊Ԃɕ`�������I�u�W�F�N�g���B																				*
 * ����𕡐���邱�Ƃɂ���đ��̃I�u�W�F�N�g�Ɋ����Ȃ�																						*
 *																																				*
 * glRotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z)																				*
 * �I�u�W�F�N�g����]������																														*
 * angle�Ŋp�x�w��																																*
 * x,y,z�͉�]���鎲���w��																														*
 *																																				*
 * glTranslated (GLdouble x, GLdouble y, GLdouble z)																							*
 * �I�u�W�F�N�g���ړ�������																														*
 * x,y,z�ɂ́A���ꂼ��ړ������������W���w�肷��																								*
 *																																				*
 * glPushMatrix(void)																															*
 * �I�u�W�F�N�g���s��X�^�b�N�ɕۑ�����																											*
 *																																				*
 * glPopMatrix(void)																															*
 * �X�^�b�N�ɕۑ������I�u�W�F�N�g�����o��																										*
 * glPushMatrix()�ƕ��p���邱�Ƃő��̃I�u�W�F�N�g�Ɋ������ɕ`�悷�邱�Ƃ��ł���																*
 *																																				*
 * glColor3d(GLdouble red, GLdouble green, GLdouble blue)																						*
 * �I�u�W�F�N�g�̐F���w�肷��																													*
 * red,green,blue�ɂ�0�`1�̒l���w�肷��																											*
 *----------------------------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------------------------*
 * ���[�h��1�̎��́A�����܂������̂܂ܑO�ɐi��Ń{�[���ɓ���������{�[���������n�߂āA�������̈ʒu�ɖ߂��Ă����܂�								*
 *																																				*
 * ���[�h��2�̎��́A������]���A�{�[���ɓ���������{�[���������o���A���̊p�x��45�x�ɂȂ�܂ŉ�]�������܂�(�~�܂�p�x�͕ύX�\)				*
 *----------------------------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------------------------------*
 * �Փ˔���ɂ���																																*
 *																																				*
 * �Փ˔���͂ܐ悪�~�ɂ��Ă���̂ŁA�ܐ�̉~�̒��S���W���o���A����ƃ{�[���̒��S���W�𗘗p���Č����ɓ��Ă͂߂邱�Ƃłł��܂�				*
 *																																				*
 * (�{�[���̒��S��x���W - �ܐ�̉~�̒��S��x���W)^2 + (�{�[���̒��S��y���W - �ܐ�̉~�̒��S��y���W)^2 <= (�{�[���̔��a + �ܐ�̉~�̔��a)	*
 * ����͐��U�͈̔͂̉~�̏d�Ȃ�̌������g���Ă��܂�																								*
 *----------------------------------------------------------------------------------------------------------------------------------------------*/


#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

static GLfloat ang = 0.0;	//�{�[���̉�]
static GLdouble yoko = -10, tate = 15;	//�{�[���̍��W
static GLdouble leg_yoko = -30, leg_tate = 15+10;	//���̍��W
static GLdouble leg_yoko_init;	//���̏����ʒu
static double n = 100;	//�[�_��
static GLdouble r = 5;	//�{�[���̔��a
static GLdouble kickang=-30.0;	//���̏����p�x
static GLdouble toe_point_x, toe_point_y;	//�ܐ�̉~�̍��W

static int mode = 0;	//���[�h�I��

//�~��`��
void Circle(GLdouble Radius){	//�����ɉ~�̑傫�����w��
	GLdouble x_plot, y_plot;	//�v���b�g���W
	GLdouble rate, rad;	//�䗦�A���W�A��
	int i;	//for�p
	glBegin(GL_POLYGON);	//�|���S�����[�h
	for (i = 0; i < n; i++){
		rate = (double)i / n; //�䗦�̎Z�o
		rad = (360 * rate) * (M_PI / 180.0); //�p�x�ɔ䗦�������āA���W�A���ɕϊ�
		x_plot = Radius * cos(rad); //cos�ɂ���ă{�[����x���W�����߂�
		y_plot = Radius * sin(rad); //sin�ɂ���ă{�[����y���W�����߂�
		glVertex2d(x_plot, y_plot); //���߂����W���v���b�g
	}
	glEnd();
}

void display(void)
{
	const GLdouble rad = M_PI / 180;	//���W�A��

	toe_point_x = 0*cos(kickang*rad) + 15 * sin(kickang*rad) + leg_yoko;	//�ܐ�̉~�̒��S��x���W
	toe_point_y = 0*sin(kickang*rad) - 15 * cos(kickang*rad) + leg_tate;	//�ܐ�̉~�̒��S��y���W

	glClear(GL_COLOR_BUFFER_BIT);	//�F�o�b�t�@���N���A

	glPushMatrix();	//�X�^�b�N�ɕۑ�
	glColor3d(1.0, 1.0, 0.0);	//���F
	glTranslated(yoko, tate, 0);	//�{�[����x���W��ϐ�yoko�̒l�̏ꏊ�ցAy���W��ϐ�tate�̒l�̏ꏊ��
	glRotatef(ang, 0.0, 0.0, -1.0);	//z���ɑ΂��ĉ�]
	Circle(r);	//�{�[���`��
	//�{�[���̐�
	glBegin(GL_LINES);	//�����Ȃ��郂�[�h
	glColor3d(0, 0, 1);	//��
	glVertex2d(-r, 0);	//�{�[���̃��C��
	glVertex2d(r, 0);	//�{�[���̃��C��
	glEnd();	//�w��I��
	glPopMatrix();	//�X�^�b�N������o��

	glPushMatrix();	//�X�^�b�N�ɕۑ�
	glColor3d(1, 0, 0);	//��
	glTranslated(leg_yoko, leg_tate, 0);	//����x���W��ϐ�leg_yoko�̒l�̏ꏊ�ցAy���W��ϐ�leg_tate�̒l�̏ꏊ��
	glRotated(kickang, 0, 0, 1);	//������]������
	glRectd(-7.5, -20, 0, 0);	//�l�p���
	glTranslated(0,-20 + r,0);	//�ܐ�̉~�̈ʒu���w��
	Circle(5);	//�~�̕`��
	glPopMatrix();	//�X�^�b�N������o��

	glutSwapBuffers();	//�o�b�t�@����ւ�
}

void simu(void)
{
	static int ball_start = 0;	//�{�[���̃X�^�[�g�t���O
	static GLdouble v, xv, yv;	//�������x�A���x��x�����A���x��y����
	static GLdouble dt = 0.002, masatu = -0.002;	//���ԊԊu�A���C�W��
	static GLdouble speedrate;	//��]�䗦
	const GLdouble e = 0.6, ensyu = 2 * r*M_PI, rad = M_PI / 180;	//�����W���A�~��
	static GLdouble degree = 0;	//�{�[�����オ��p�x
	static GLdouble leg_speed = 0.05;	//���̑��x

	//���[�h��1�̂Ƃ�
	if (mode == 1){
		//���̍��W�ɖ߂�܂ő��𓮂���
		if (leg_yoko >= leg_yoko_init){
			leg_yoko += leg_speed;
		}
	}
	//���[�h��2�̂Ƃ�
	else{
		//45�x�ɂȂ�܂ŉ�]������
		if (kickang < 45)
			kickang += 0.05;
	}

	//�Փ˔���
	//�ܐ�̉~�̔��a�ƃ{�[���̔��a�Ŕ���
	if (pow(yoko - toe_point_x, 2) + pow(tate - toe_point_y, 2) < pow(5 + r, 2)){
		degree = atan2(fabs(tate - leg_tate), fabs(yoko - leg_yoko)) / M_PI * 180;	//�����������̊p�x���v�Z
		//�˂��悤�ɂ���Ƃ߂荞�ނ̂�
		if (mode == 1){
			leg_yoko = yoko - 10;	//�߂荞�݉���
		}
		v =20;	//���x�ɑ��(�����͓K��)
		xv = v*cos(degree*rad);		//x�����̑��x
		yv = v*sin(degree*rad);	//y�����̑��x
		leg_speed *= -1;	//���̈ړ���������𔽓]

		ball_start = 1;	//�{�[���������n�߂�t���O
	}

	//�{�[���̓���
	if (ball_start){
		speedrate = 360 * dt*xv;	//��]�䗦
		ang += speedrate / ensyu;	//����Ȃ��悤�ɉ�]
		if (ang>360)	//360�x�𒴂�������360�x�����āA�p�x��߂�
			ang -= 360;

		yoko += xv*dt;	//�{�[����x���W
		//�E�̕ǂɂ���������
		if (yoko>50 - r){
			xv *= -e;	//���x�𒵂˕Ԃ�W���������Ĕ��]
			masatu *= -1;	//���C�������]
			yoko = 50 - r;	//�߂荞�݂��Ȃ���
		}
		//���̕ǂɂ���������
		if (yoko<-50 + r){
			xv *= -e;	//���x�𒵂˕Ԃ�W���������Ĕ��]
			masatu *= -1;	//���C�������]
			yoko = -50 + r;	//�߂荞�݂��Ȃ���
		}

		yv = yv - 9.8*dt;	//�{�[����y���x
		tate += yv*dt;	//�{�[����y���W
		//���ɒ�������
		if (tate<-50 + r){
			yv *= -e;	//���x�𒵂˕Ԃ�W���������Ĕ��]
			tate = -50 + r;	//�߂荞�݂��Ȃ���
		}
		//���ɐڐG���Ă��鎞
		if (tate == -50 + r){
			xv += masatu;	//���C
			if (xv>-0.1&&xv<0.1){	//�{�[����~
				xv = 0;
				masatu = 0;
			}
		}
	}

	glutPostRedisplay();	//�ĕ`��
}

//�����֐�
void init(void)
{
	//���[�h�I��
	printf("���[�h��I�����Ă�������\n");
	printf("1�F�˂��悤�ɏR��, 2�F�U��グ�ďR�� >");
	scanf("%d", &mode);	//���[�h��I��������
	glClearColor(0.0, 0.0, 0.0, 0.0);	//��
	glShadeModel(GL_FLAT);
	leg_yoko_init = leg_yoko;	//���̏����ʒu���
	if (mode == 1) kickang = 0;	//�˂��悤�ɏR��Ƃ��͑��͂܂�����
}

//�E�B���h�E�̃T�C�Y���ς�������Ƀ��T�C�Y
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);	//�傫�����߂�
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//�}�E�X
void mouse(int button, int state, int x, int y){
	switch (button) {
		//���N���b�N�F�J�n
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_DOWN)
				glutIdleFunc(simu);
			break;
		//�E�N���b�N�F��~
		case GLUT_RIGHT_BUTTON:
			if (state == GLUT_DOWN)
				glutIdleFunc(NULL);
			break;
		default:
			break;
	}
}

//�L�[�{�[�h
void keyboard(unsigned char key, int x, int y)
{
	if (key == '\x1b') exit(0);	//ESC�ŏI��
	if (key == '\xd') exit(0);	//ENTER�ŏI��
	if (key == 'd') glutIdleFunc(simu);	//d�ŊJ�n
	if (key == 's') glutIdleFunc(NULL);	//s�Œ�~
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(400, 400);	//�E�B���h�E�T�C�Y
	glutInitWindowPosition(100, 100);	//�E�B���h�E�̏ꏊ
	glutCreateWindow("Robokick");	//�E�B���h�E�̃^�C�g��
	init();
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}