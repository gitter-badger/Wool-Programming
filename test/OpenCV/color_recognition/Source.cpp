//インクルード
#include <opencv2\opencv.hpp>
#include <opencv_lib.hpp>	//libファイルリンカー用
#include <iostream>
#include <cmath>

//名前空間を使用
using namespace std;
using namespace cv;

//クリックした座標
int click_x = 100;
int click_y = 200;

//選択座標の四角形表示用
int box_x = 0, box_y = 0;

//クリックされている状態がどうかの判断
bool mouseclick = false;

//マウスイベント用関数
void onMouse(int event, int x, int y, int flags, void* param){
	Mat* img = static_cast<Mat*>(param);

	switch (event){
		//マウスを動かしている時
		case EVENT_MOUSEMOVE:
			box_x = x;
			box_y = y;
			//ドラッグしているとき
			if (mouseclick){
				click_x = x;
				click_y = y;
			}
			break;

			//左クリックされたとき
		case EVENT_LBUTTONDOWN:
			mouseclick = true;
			break;

			//指が離れた時
		case EVENT_LBUTTONUP:
			mouseclick = false;
			break;
	}
}

int main(){

	int rectsize = 2;	//選択座標の四角形の大きさ

	int low_hue = 255, high_hue = 0, low_saturation = 255, high_saturation = 0, low_value = 255, high_value = 0;	//それぞれの上限・下限値

	Mat img;	//カメラから取得した画像

	Mat low_h, high_h, low_s, high_s, low_v, high_v, hue, saturation, value, hue_saturation, mask_image, output_image;	//マスク用の画像用、結果表示用

	Mat hsv;	//HSV空間に変換用

	//カメラから取得する映像の大きさ
	int width = 640;
	int height = 480;

	//ウィンドウを作成
	namedWindow("Input");

	//マウスイベントを呼び出す
	setMouseCallback("Input", onMouse);

	//映像を取得するデバイスを選択
	VideoCapture cap(0);

	//カメラ映像の大きさを設定
	cap.set(CV_CAP_PROP_FRAME_WIDTH, width);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, height);

	//HSV空間をそれぞれの要素に分けるため
	vector<Mat> splitimage;

	while (1){
		//カメラ映像を取得
		cap >> img;

		//結果表示画像を初期化
		output_image = 0;

		//HSV空間に変換
		cvtColor(img, hsv, CV_BGR2HSV);

		//マウスのある座標に四角形を作る
		rectangle(img, Point(box_x - rectsize, box_y - rectsize), Point(box_x + rectsize, box_y + rectsize), Scalar(200, 0, 0));

		//デバッグ用にそれぞれの値をコンソールに出力
		printf("%d, %d, %d, %d, %d, %d\n", low_hue, high_hue, low_saturation, high_saturation, low_value, high_value);

		//それぞれの要素に分ける
		split(hsv, splitimage);

		if (mouseclick){
			//クリックされた座標がエラーでない場合
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

		//それぞれの上限・下限値によって2値化
		threshold(splitimage[0], low_h, low_hue, 255, THRESH_BINARY);
		threshold(splitimage[0], high_h, high_hue, 255, THRESH_BINARY_INV);
		threshold(splitimage[1], low_s, low_saturation, 255, THRESH_BINARY);
		threshold(splitimage[1], high_s, high_saturation, 255, THRESH_BINARY_INV);
		threshold(splitimage[2], low_v, low_value, 255, THRESH_BINARY);
		threshold(splitimage[2], high_v, high_value, 255, THRESH_BINARY_INV);

		//アンド演算
		bitwise_and(low_h, high_h, hue);
		bitwise_and(low_s, high_s, saturation);
		bitwise_and(low_v, high_v, value);
		bitwise_and(hue, saturation, hue_saturation);
		bitwise_and(hue_saturation, value, mask_image);

		/*dilate(mask_image, mask_image, Mat());

		erode(mask_image, mask_image, Mat());*/

		//morphologyEx(mask_image, mask_image, MORPH_OPEN, Mat());

		//マスクを使用してコピー
		img.copyTo(output_image, mask_image);

		/*dilate(output_image, output_image, Mat());

		erode(output_image, output_image, Mat());*/

		//int count=countNonZero(mask_image);

		//cout << count << endl;

		/*double L1 = 50;
		double S = sqrt(53700) / sqrt(count);

		double L2 = L1*S;

		cout << L2 << endl;*/

		//入力画像の表示
		imshow("Input", img);

		//結果表示
		imshow("Output", output_image);

		imshow("Mask", mask_image);

		splitimage.clear();

		int c = waitKey(33);
		//ENTERキーが押されたら
		if (c == 13)
			break;
		//値を初期化する
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