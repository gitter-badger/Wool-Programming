#include <opencv2\opencv.hpp>
#include <opencv_lib.hpp>
#include <string>
#include <vector>
#include <iostream>

using namespace cv;

int main(){

	Mat img, gray_img;

	VideoCapture cap(0);

 	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 640);

	if (!cap.isOpened()){
		std::cout << "camera not open" << std::endl;
		return -1;
	}

	std::string cascade_name = "haarcascade_mcs_eyepair_big.xml";
	CascadeClassifier cascade;

	if (!cascade.load(cascade_name)){
		std::cout << "load failed" << std::endl;
		return -1;
	}

	namedWindow("Output", CV_WINDOW_AUTOSIZE);

	std::vector<Rect> eyeobj;

	while (waitKey(1)==-1){
		cap >> img;

		cvtColor(img, gray_img, CV_BGR2GRAY);

		cascade.detectMultiScale(gray_img, eyeobj, 1.1, 3, CV_HAAR_SCALE_IMAGE, Size(10, 10));

		for (std::vector<Rect>::const_iterator e = eyeobj.begin(); e != eyeobj.end(); ++e){
			rectangle(img, Point(e->x, e->y), Point(e->x + e->width, e->y + e->height), Scalar(0, 0, 0), -1);
		}

		imshow("Output", img);

	}

	return 0;
}