#include <iostream>
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	// C++ raw string literal
	auto imgpath1 = R"(C:\Users\chakraphan.c\Pictures\k\red-s.png)";
	auto imgpath2 = R"(C:\Users\chakraphan.c\Pictures\71932_166840493326023_2349352_n.jpg)";
	auto imgpath3 = R"(C:\Users\chakraphan.c\Pictures\830362_578876282122440_258676396_o.jpg)";

	Mat  img = imread(imgpath1, ImreadModes::IMREAD_COLOR);
	imshow("Original", img);
	waitKey(0);

	// Scalar color pattern = Blue | Green | Red

	Mat outImgBlue;
	inRange(img, Scalar(100, 0, 0), Scalar(255, 100, 100), outImgBlue);
	imshow("Blue", outImgBlue);

	Mat outImgGreen;
	inRange(img, Scalar(0, 100, 0), Scalar(100, 255, 100), outImgGreen);
	imshow("Green", outImgGreen);

	Mat outImgRed;
	inRange(img, Scalar(0, 0, 100), Scalar(100, 100, 255), outImgRed);

	// add blur to border
	GaussianBlur(outImgRed, outImgRed, Size(9, 9), 2, 2);

	imshow("Red", outImgRed);

	waitKey(0);

	return 0;
}