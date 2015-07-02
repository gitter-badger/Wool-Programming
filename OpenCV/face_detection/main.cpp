#include <opencv_lib.hpp>
#include <opencv2\opencv.hpp>
#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

#define ENTER 13

int main(){
	const int base = 350;
	const int w = base * 4, h = base * 3;
	const int small = base / 60;
	const int deviation = 20;

	cv::VideoCapture cap(0);

	if (!cap.isOpened()){
		std::cout << "Camera not open" << std::endl;
		return -1;
	}

	cap.set(CV_CAP_PROP_FRAME_WIDTH, w);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, h);

	cv::Mat frame;
	cv::Mat image = cv::imread("baymax_mask1.jpg");
	cv::Mat image_re;
	cv::Mat msking = cv::imread("baymax_mask2.jpg");
	cv::Mat msking_re;
	cv::Mat copy;
	cv::Mat detect;
	cv::Mat roi_img;
	int count = 0;

	time_t timer = time(NULL);
	struct tm *local = localtime(&timer);
	int year = local->tm_year + 1900;
	int month = local->tm_mon + 1;
	int day = local->tm_mday;
	int hour = local->tm_hour;
	int minute = local->tm_min;

	std::ostringstream ostr;

	std::string str1;
	std::string str2;

	cv::CascadeClassifier cascade;

	if (!cascade.load("haarcascade_frontalface_alt2.xml")){
		std::cout << "load failed" << std::endl;
		return -1;
	}

	std::vector<cv::Rect> faceobj;

	cv::namedWindow("Capture", CV_WINDOW_AUTOSIZE);

	for (;;){
		cap >> frame;
		frame.copyTo(copy);
		frame.copyTo(detect);

		resize(detect, detect, cv::Size(detect.cols / small, detect.rows / small));

		cvtColor(detect, detect, CV_BGR2GRAY);

		cascade.detectMultiScale(detect, faceobj, 1.1, 2, CV_HAAR_DO_CANNY_PRUNING, cv::Size(10, 10));

		for (std::vector<cv::Rect>::iterator f = faceobj.begin(); f != faceobj.end(); f++){
			image_re = image.clone();
			msking_re = msking.clone();

			cvtColor(msking_re, msking_re, CV_BGR2GRAY);
			threshold(msking_re, msking_re, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);

			roi_img = frame(cv::Rect(cv::Point(f->x*small - deviation, f->y*small - deviation), cv::Point((f->x + f->width)*small + deviation, (f->y + f->height)*small + deviation)));

			resize(image_re, image_re, cv::Size(roi_img.cols, roi_img.rows));
			resize(msking_re, msking_re, cv::Size(roi_img.cols, roi_img.rows));

			image_re.copyTo(roi_img, msking_re);
		}

		imshow("Capture", frame);

		int c = cv::waitKey(1);
		if (c == ENTER){
			break;
		}
		else if (c == 's'){
			ostr << "screenshotnemo"
				<< count << "_"
				<< year
				<< std::setfill('0') << std::setw(2) << month
				<< std::setfill('0') << std::setw(2) << day
				<< std::setfill('0') << std::setw(2) << hour
				<< std::setfill('0') << std::setw(2) << minute << ".jpg";
			str1 = ostr.str();
			ostr.str("");
			ostr << "hogeshotnemo"
				<< count << "_"
				<< year
				<< std::setfill('0') << std::setw(2) << month
				<< std::setfill('0') << std::setw(2) << day
				<< std::setfill('0') << std::setw(2) << hour
				<< std::setfill('0') << std::setw(2) << minute << ".jpg";
			str2 = ostr.str();
			ostr.str("");
			cv::imwrite(str1, frame);
			cv::imwrite(str2, copy);
			std::cout << str1 << ", " << str2 << std::endl;
			count++;
		}
	}
}