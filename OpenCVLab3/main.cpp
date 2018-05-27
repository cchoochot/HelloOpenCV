#include <opencv2\opencv.hpp>
#include <stdint.h>

using namespace std;
using namespace cv;

const int FPS = 20;

int main(int argc, char **argv) {

	Mat frame;

	VideoCapture vid(0);

	if (!vid.isOpened()) {
		return -1;
	}

	while (vid.read(frame)) {
		//vid >> frame;

		imshow("webcam", frame);

		if (waitKey(1000 / FPS) >= 0) {
			break;
		}
	}

	return 1;
}