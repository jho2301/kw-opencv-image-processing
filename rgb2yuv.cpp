#include <opencv2/opencv.hpp>
#include <math.h>
#include <opencv/cv.h>

using namespace cv;
using namespace std;

void main()
{


	Mat img = imread("C:\\Users\\wjsgh\\Desktop\\img2.jpg", IMREAD_COLOR);
	Mat imgYUVConverted(img.rows, img.cols, CV_8UC1);

	imshow("original", img);
	cvtColor(img, imgYUVConverted, CV_BGR2YCrCb);
	
	imshow("cvtColored", imgYUVConverted);

	printf("rgb		b: %d g: %d r: %d\n", img.data[0], img.data[1], img.data[2]);
	printf("cvt		y: %d u: %d v: %d\n", imgYUVConverted.data[0], imgYUVConverted.data[1], imgYUVConverted.data[2]);

	for (int i = 0; i < img.rows * img.cols; i++)
	{
			uchar b = img.data[i];
			uchar g = img.data[i + 1];
			uchar r = img.data[i + 2];

			imgYUVConverted.data[i] = (0.299 * r) + (0.587 * g) + (0.114 * b);
			imgYUVConverted.data[i + 1] = 0.713 * (r - imgYUVConverted.data[i]) + 128;
			imgYUVConverted.data[i + 2] = 0.564 * (b - imgYUVConverted.data[i]) + 128;

			i += 2;
	}
	
	imshow("YUV converted by me", imgYUVConverted );

	printf("mine		y: %d u: %d v: %d \n", imgYUVConverted.data[0], imgYUVConverted.data[1], imgYUVConverted.data[2]);



	waitKey(0);

}
