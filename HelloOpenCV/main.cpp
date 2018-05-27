#include <iostream>

#include <opencv2\core.hpp>
#include <opencv2\imgcodecs.hpp>
#include <opencv2\highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc, char * argv[]) {
	/*if (argc != 2) {
		cout << "Usage: display_image ImageToLoadAndDisplay" << endl;
		return -1;
	}*/

	Mat img;
	// ft9bpzm1sjqz.png
	// UjeiuLt.jpg
	img = imread("C:/Users/chakraphan.c/Pictures/ft9bpzm1sjqz.png", IMREAD_COLOR);

	if (img.empty()) {
		cout << "Could not open image file." << endl;
		return -1;
	}

	namedWindow("Display window", WINDOW_AUTOSIZE);
	imshow("Display window", img);

	waitKey(0);


	return 0;
}