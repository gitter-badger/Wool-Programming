//�C���N���[�h
#include <opencv2\opencv.hpp>
#include <opencv_lib.hpp>	//lib�t�@�C�������J�[�p
#include <iostream>
#include <cmath>

//���O��Ԃ��g�p
using namespace std;
using namespace cv;

//�N���b�N�������W
int click_x = 100;
int click_y = 200;

//�I�����W�̎l�p�`�\���p
int box_x = 0, box_y = 0;

//�N���b�N����Ă����Ԃ��ǂ����̔��f
bool mouseclick = false;

//�}�E�X�C�x���g�p�֐�
void onMouse(int event, int x, int y, int flags, void* param){
	Mat* img = static_cast<Mat*>(param);

	switch (event){
		//�}�E�X�𓮂����Ă��鎞
		case EVENT_MOUSEMOVE:
			box_x = x;
			box_y = y;
			//�h���b�O���Ă���Ƃ�
			if (mouseclick){
				click_x = x;
				click_y = y;
			}
			break;

			//���N���b�N���ꂽ�Ƃ�
		case EVENT_LBUTTONDOWN:
			mouseclick = true;
			break;

			//�w�����ꂽ��
		case EVENT_LBUTTONUP:
			mouseclick = false;
			break;
	}
}

int main(){

	int rectsize = 2;	//�I�����W�̎l�p�`�̑傫��

	int low_hue = 255, high_hue = 0, low_saturation = 255, high_saturation = 0, low_value = 255, high_value = 0;	//���ꂼ��̏���E�����l

	Mat img;	//�J��������擾�����摜

	Mat low_h, high_h, low_s, high_s, low_v, high_v, hue, saturation, value, hue_saturation, mask_image, output_image;	//�}�X�N�p�̉摜�p�A���ʕ\���p

	Mat hsv;	//HSV��Ԃɕϊ��p

	//�J��������擾����f���̑傫��
	int width = 640;
	int height = 480;

	//�E�B���h�E���쐬
	namedWindow("Input");

	//�}�E�X�C�x���g���Ăяo��
	setMouseCallback("Input", onMouse);

	//�f�����擾����f�o�C�X��I��
	VideoCapture cap(0);

	//�J�����f���̑傫����ݒ�
	cap.set(CV_CAP_PROP_FRAME_WIDTH, width);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, height);

	//HSV��Ԃ����ꂼ��̗v�f�ɕ����邽��
	vector<Mat> splitimage;

	while (1){
		//�J�����f�����擾
		cap >> img;

		//���ʕ\���摜��������
		output_image = 0;

		//HSV��Ԃɕϊ�
		cvtColor(img, hsv, CV_BGR2HSV);

		//�}�E�X�̂�����W�Ɏl�p�`�����
		rectangle(img, Point(box_x - rectsize, box_y - rectsize), Point(box_x + rectsize, box_y + rectsize), Scalar(200, 0, 0));

		//�f�o�b�O�p�ɂ��ꂼ��̒l���R���\�[���ɏo��
		printf("%d, %d, %d, %d, %d, %d\n", low_hue, high_hue, low_saturation, high_saturation, low_value, high_value);

		//���ꂼ��̗v�f�ɕ�����
		split(hsv, splitimage);

		if (mouseclick){
			//�N���b�N���ꂽ���W���G���[�łȂ��ꍇ
			if (click_x > 0 && click_y > 0 && click_x < width && click_y < height){
				if ((int)hsv.at<Vec3b>(click_y, click_x)[0] < low_hue)
					low_hue = (int)hsv.at<Vec3b>(click_y, click_x)[0];
				if ((int)hsv.at<Vec3b>(click_y, click_x)[0] > high_hue)
					high_hue = (int)hsv.at<Vec3b>(click_y, click_x)[0];
				if ((int)hsv.at<Vec3b>(click_y, click_x)[1] < low_saturation)
					low_saturation = (int)hsv.at<Vec3b>(click_y, click_x)[1];
				if ((int)hsv.at<Vec3b>(click_y, click_x)[1] > high_saturation)
					high_saturation = (int)hsv.at<Vec3b>(click_y, click_x)[1];
				if ((int)hsv.at<Vec3b>(click_y, click_x)[2] < low_value)
					low_value = (int)hsv.at<Vec3b>(click_y, click_x)[2];
				if ((int)hsv.at<Vec3b>(click_y, click_x)[2] > high_value)
					high_value = (int)hsv.at<Vec3b>(click_y, click_x)[2];
			}
		}

		//���ꂼ��̏���E�����l�ɂ����2�l��
		threshold(splitimage[0], low_h, low_hue, 255, THRESH_BINARY);
		threshold(splitimage[0], high_h, high_hue, 255, THRESH_BINARY_INV);
		threshold(splitimage[1], low_s, low_saturation, 255, THRESH_BINARY);
		threshold(splitimage[1], high_s, high_saturation, 255, THRESH_BINARY_INV);
		threshold(splitimage[2], low_v, low_value, 255, THRESH_BINARY);
		threshold(splitimage[2], high_v, high_value, 255, THRESH_BINARY_INV);

		//�A���h���Z
		bitwise_and(low_h, high_h, hue);
		bitwise_and(low_s, high_s, saturation);
		bitwise_and(low_v, high_v, value);
		bitwise_and(hue, saturation, hue_saturation);
		bitwise_and(hue_saturation, value, mask_image);

		/*dilate(mask_image, mask_image, Mat());

		erode(mask_image, mask_image, Mat());*/

		//morphologyEx(mask_image, mask_image, MORPH_OPEN, Mat());

		//�}�X�N���g�p���ăR�s�[
		img.copyTo(output_image, mask_image);

		/*dilate(output_image, output_image, Mat());

		erode(output_image, output_image, Mat());*/

		//int count=countNonZero(mask_image);

		//cout << count << endl;

		/*double L1 = 50;
		double S = sqrt(53700) / sqrt(count);

		double L2 = L1*S;

		cout << L2 << endl;*/

		//���͉摜�̕\��
		imshow("Input", img);

		//���ʕ\��
		imshow("Output", output_image);

		imshow("Mask", mask_image);

		splitimage.clear();

		int c = waitKey(33);
		//ENTER�L�[�������ꂽ��
		if (c == 13)
			break;
		//�l������������
		if (c == 'c'){
			low_hue = 255;
			high_hue = 0;
			low_saturation = 255;
			high_saturation = 0;
			low_value = 255;
			high_value = 0;
			click_x = 0;
			click_y = 0;
			output_image = 0;
		}
	}

	return 0;
}