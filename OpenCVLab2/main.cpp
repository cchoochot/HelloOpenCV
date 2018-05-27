#include <opencv2\opencv.hpp>
#include <stdint.h>

using namespace std;
using namespace cv;

void createGaussian(Size& size, Mat& output, int uX, int uY, float sigmaX, float sigmaY, float amplitude = 1.0f) {
	Mat temp = Mat(size, CV_32F);

	for (auto r = 0; r < size.height; ++r) {
		for (auto c = 0; c < size.width; ++c) {
			float x = ((c - uX) * (static_cast<float>(c) - uX)) / (2.0f * sigmaX * sigmaX);
			float y = ((r - uY) * (static_cast<float>(r) - uY)) / (2.0f * sigmaY * sigmaY);
			float value = amplitude * exp(-(x + y));

			temp.at<float>(r, c) = value;
		}
	}

	normalize(temp, temp, 0.0f, 1.0f, NormTypes::NORM_MINMAX);

	output = temp;
}

int main() {
	Mat output;
	createGaussian(Size(256, 256), output, 256 / 2, 256 / 2, 10, 10);

	imshow("Gaussian", output);

	waitKey();
}