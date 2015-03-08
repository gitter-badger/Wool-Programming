#include <opencv2\opencv.hpp>
#include <opencv_lib.hpp>
#include <stdio.h>

#define ENTER 13

#define SCALE 1.3

int main(void){

	CvCapture* capture = cvCreateCameraCapture(0);
	double base = 350;
	double w = base * 4, h = base * 3;
	double small = base / 60;

	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, w);
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, h);

	IplImage* frame = cvQueryFrame(capture);
	IplImage* frame_copy = 0;
	int c;
//	IplImage* image = cvLoadImage("baboon.jpg");
	IplImage* image = cvLoadImage("d03a3d0296aa49322741f8a506656948_plus.png");
	IplImage* image_re = 0;
	IplImage* resize = 0;
	IplImage* image2 = cvLoadImage("37_20140501235232ea1.png");
	IplImage* image2_re = 0;
	IplImage* image3 = cvLoadImage("board.jpg");
	IplImage* image3_re = 0;
	IplImage* copy = cvCreateImage(cvGetSize(frame), frame->depth, frame->nChannels);
	int count = 0;

	CvHaarClassifierCascade* cvHcc = (CvHaarClassifierCascade*)cvLoad("haarcascade_frontalface_alt2.xml");
	CvSeq* face;
	CvMemStorage* cvMstr = cvCreateMemStorage(0);
	char str[50] = { 0 };
	char str2[50] = { 0 };
	CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_TRIPLEX, 1, 1);

	cvNamedWindow("Capture", CV_WINDOW_AUTOSIZE);

	while (1){
		frame = cvQueryFrame(capture);

		cvCopy(frame, copy);

		CvMemStorage* cvMstr = cvCreateMemStorage(0);

		resize = cvCreateImage(cvSize(frame->width / small, frame->height / small), frame->depth, frame->nChannels);
		cvResize(frame, resize);

		face = cvHaarDetectObjects(resize, cvHcc, cvMstr, 1.1, 2, CV_HAAR_DO_CANNY_PRUNING,cvSize(10,10));

		for (int i = 0; i < (face->total); i++){
			CvRect* faceRect = (CvRect*)cvGetSeqElem(face, i);

			image_re = cvCreateImage(cvSize(faceRect->width*small, faceRect->height*small), frame->depth, frame->nChannels);
			cvResize(image, image_re);
			image2_re = cvCreateImage(cvSize(faceRect->width*small, faceRect->height*small), frame->depth, frame->nChannels);
			cvResize(image2, image2_re);
			image3_re = cvCreateImage(cvSize(faceRect->width*small, faceRect->height*small), frame->depth, frame->nChannels);
			cvResize(image3, image3_re);

			//if (i == 0){

				cvSetImageROI(frame, cvRect(faceRect->x*small, faceRect->y*small, faceRect->width*small, faceRect->height*small));
				cvCopy(image_re, frame);
			/*}
			else if (i == 1){
				cvSetImageROI(frame, cvRect(faceRect->x*small, faceRect->y*small, faceRect->width*small, faceRect->height*small));
				cvCopy(image2_re, frame);
			}
			else if (i > 1){
				cvSetImageROI(frame, cvRect(faceRect->x*small, faceRect->y*small, faceRect->width*small, faceRect->height*small));
				cvCopy(image3_re, frame);
			}*/


			cvResetImageROI(frame);

			//int xp = faceRect->x*small + faceRect->width*small / 2;
			//int yp = faceRect->y*small + faceRect->height*small / 2;

			////sprintf(str,"%d",i);
			//str = (char*)i;

			//printf("%s\n", str);

			//if (i==0)
			//cvPutText(frame,"0", cvPoint(xp, yp),&font, cvScalar(0, 200, 200));
			//if (i==1)
			//	cvPutText(frame, "1", cvPoint(xp, yp), &font, cvScalar(0, 200, 200));

			////cv::putText(frame, "Moon", cv::Point(50, 50), CV_FONT_NORMAL, 1.5, cv::Scalar(0, 200, 200), 2, CV_AA);
		}



		cvShowImage("Capture", frame);

		c = cvWaitKey(1);
		if (c == ENTER)
			break;
		if (c == 's'){
			sprintf(str, "screenshot%d.jpg", count);
			sprintf(str2, "hogeshot%d.jpg", count);
			printf("%s, %s\n", str, str2);
			cvSaveImage(str, frame);
			cvSaveImage(str2, copy);
			count++;
		}
	}
	cvReleaseMemStorage(&cvMstr);
	cvReleaseCapture(&capture);
	cvReleaseHaarClassifierCascade(&cvHcc);
	cvDestroyAllWindows();

	return 0;
}