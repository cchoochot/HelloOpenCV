#include <opencv2\opencv.hpp>
#include <stdint.h>

using namespace cv;
using namespace std;

void takeDft(Mat& source, Mat& destination) {

	Mat originalComplex[2] = { source, Mat::zeros(source.size(), CV_32F) };

	Mat dftReady;
	merge(originalComplex, 2, dftReady);

	dft(dftReady, destination, DftFlags::DFT_COMPLEX_OUTPUT);
}

void recenterDft(Mat& source) {
	int centerX = source.cols / 2;
	int centerY = source.rows / 2;

	Mat q1(source, Rect(0, 0, centerX, centerY));
	Mat q2(source, Rect(centerX, 0, centerX, centerY));
	Mat q3(source, Rect(0, centerY, centerX, centerY));
	Mat q4(source, Rect(centerX, centerY, centerX, centerY));

	Mat swapMap;

	q1.copyTo(swapMap);
	q4.copyTo(q1);
	swapMap.copyTo(q4);

	q2.copyTo(swapMap);
	q3.copyTo(q2);
	swapMap.copyTo(q3);
}

void showDft(Mat& source) {
	Mat splitArray[2] = { Mat::zeros(source.size(), CV_32F), Mat::zeros(source.size(), CV_32F) };

	split(source, splitArray);

	Mat dftMagnitude;

	magnitude(splitArray[0], splitArray[1], dftMagnitude);

	dftMagnitude += Scalar::all(1);

	log(dftMagnitude, dftMagnitude);

	normalize(dftMagnitude, dftMagnitude, 0, 1, CV_MINMAX);

	recenterDft(dftMagnitude);

	imshow("DFT", dftMagnitude);

	waitKey();
}

void invertDft(Mat& source, Mat& destination) {
	Mat inverse;

	// idft()
	dft(source, inverse, DftFlags::DFT_INVERSE | DftFlags::DFT_REAL_OUTPUT | DftFlags::DFT_SCALE);

	destination = inverse;
}

int main(int argc, char **argv) {

	Mat original = imread("house.jpg", ImreadModes::IMREAD_GRAYSCALE);

	Mat originalFloat;
	original.convertTo(originalFloat, CV_32FC1, 1.0 / 255.0);

	Mat dftOfOriginal;

	takeDft(originalFloat, dftOfOriginal);

	showDft(dftOfOriginal);

	Mat invertedDFT;

	invertDft(dftOfOriginal, invertedDFT);

	imshow("Invert DFT Result", invertedDFT);

	waitKey();
	return 0;
}




int main4(int argc, char **argv) {
	Mat original = imread("flower.jpg", ImreadModes::IMREAD_COLOR);

	Mat splitChannels[3];

	split(original, splitChannels);

	imshow("blue", splitChannels[0]);
	imshow("green", splitChannels[1]);
	imshow("red", splitChannels[2]);

	splitChannels[2] = Mat::zeros(splitChannels[2].size(), CV_8UC1);

	Mat output;
	merge(splitChannels, 3, output);

	imshow("merged", output);

	waitKey();

	return 0;
}


int main3(int argc, char **argv) {
	Mat original = imread("flower.jpg", ImreadModes::IMREAD_COLOR);
	Mat modified = imread("flower.jpg", ImreadModes::IMREAD_COLOR);

	for (auto r = 0, len = modified.rows; r < len; ++r) {
		for (auto c = 0, len = modified.cols; c < len; ++c) {
			modified.at<cv::Vec3b>(r, c)[2] = modified.at<cv::Vec3b>(r, c)[2] * 0.7;
		}
	}

	imshow("original", original);
	imshow("modified", modified);

	waitKey();

	return 0;
}



int main2(int argc, char **argv) {
	Mat colorimg = imread("flower.jpg", ImreadModes::IMREAD_COLOR);
	Mat greyimg = imread("flower.jpg", ImreadModes::IMREAD_GRAYSCALE);

	namedWindow("Color", WindowFlags::WINDOW_FREERATIO);
	namedWindow("Fixed", WindowFlags::WINDOW_AUTOSIZE);

	imshow("Color", colorimg);
	imshow("Fixed", greyimg);

	resizeWindow("Color", colorimg.cols / 2, colorimg.rows / 2);
	resizeWindow("Fixed", greyimg.cols / 2, greyimg.rows / 2);


	moveWindow("Color", 0, 0);
	moveWindow("Fxied", 50, 20);

	waitKey();

	return 0;
}


int main1(int argc, char **argv) {
	Mat img1 = imread("flower.jpg", ImreadModes::IMREAD_COLOR);

	Mat img2 = imread("flower.jpg", ImreadModes::IMREAD_GRAYSCALE);

	imshow("Color image", img1);
	imshow("Greyscale", img2);

	imwrite("outputGrey.jpg", img2);

	waitKey();

	return 0;
}