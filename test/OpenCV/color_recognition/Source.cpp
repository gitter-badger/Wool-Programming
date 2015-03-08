#include <opencv2/opencv.hpp>
#include <opencv_lib.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int click_x = 100;
int click_y = 200;
int box_x = 0, box_y = 0;
int rectsize = 2;
int low_hue = 255, high_hue = 0, low_saturation = 255, high_saturation = 0, low_value = 255, high_value = 0;
Mat low_h, high_h, low_s, high_s, low_v, high_v, h, s, v, hue_saturation, image, hoge, img;
Mat hsv;
bool mouseclick = false;
int height = 480;
int width = 640;

void onMouse(int event, int x, int y, int flags, void* param){
	Mat* img = static_cast<Mat*>(param);

	switch (event){
		case EVENT_MOUSEMOVE:
			box_x = x;
			box_y = y;
			if (mouseclick){
				click_x = x;
				click_y = y;
			}
			break;
		case EVENT_LBUTTONDOWN:
			mouseclick = true;
			break;
		case EVENT_LBUTTONUP:
			mouseclick = false;
			break;
	}
}

int main(){

	namedWindow("Input");
	setMouseCallback("Input", onMouse);
	VideoCapture cap(0);
		cap.set(CV_CAP_PROP_FRAME_WIDTH, width);
		cap.set(CV_CAP_PROP_FRAME_HEIGHT, height);
	while (1){
		cap >> img;

		hoge = 0;

		cvtColor(img, hsv, CV_BGR2HSV);

		rectangle(img, Point(box_x - rectsize, box_y - rectsize), Point(box_x + rectsize, box_y + rectsize), Scalar(200, 0, 0));

		printf("%d, %d, %d, %d, %d, %d\n", low_hue, high_hue, low_saturation, high_saturation, low_value, high_value);
		vector<Mat> splitimage;

		split(hsv, splitimage);

		if (mouseclick){
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

		threshold(splitimage[0], low_h, low_hue, 255, THRESH_BINARY);
		threshold(splitimage[0], high_h, high_hue, 255, THRESH_BINARY_INV);
		threshold(splitimage[1], low_s, low_saturation, 255, THRESH_BINARY);
		threshold(splitimage[1], high_s, high_saturation, 255, THRESH_BINARY_INV);
		threshold(splitimage[2], low_v, low_value, 255, THRESH_BINARY);
		threshold(splitimage[2], high_v, high_value, 255, THRESH_BINARY_INV);

		bitwise_and(low_h, high_h, h);
		bitwise_and(low_s, high_s, s);
		bitwise_and(low_v, high_v, v);
		bitwise_and(h, s, hue_saturation);
		bitwise_and(hue_saturation, v, image);

		img.copyTo(hoge, image);

		imshow("Input", img);/*
		imshow("Output", hsv);
		imshow("Threshold", image);*/
		imshow("hoge", hoge);

		int c = waitKey(33);
		if (c == 13)
			break;
		if (c == 'c'){
			low_hue = 255;
			high_hue = 0;
			low_saturation = 255;
			high_saturation = 0;
			low_value = 255;
			high_value = 0;
			click_x = 0;
			click_y = 0;
			hoge = 0;
		}
	}

	return 0;
}