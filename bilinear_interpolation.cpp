#include <opencv2/opencv.hpp>
#include <math.h>
#include <opencv/cv.h>

using namespace cv;
using namespace std;

void main()
{
	int size;
	cin >> size;


	Mat img_out(Size(size, size), 0);

	Mat img_in = imread("C:\\Users\\wjsgh\\Desktop\\Cat03.jpg", IMREAD_COLOR);


	cvtColor(img_in, img_in, COLOR_RGB2GRAY);
	imshow("img_in", img_in);
	


	double interpolations_rate = (double)img_out.rows / img_in.rows;

	for (int y = 0; y < img_out.rows; y++)
	{
		for (int x = 0; x < img_out.cols; x++)
		{
			int px = (int)((double)x / interpolations_rate);
			int py = (int)((double)y / interpolations_rate);

			if (img_in.cols - 1 <= px) px = img_in.cols - 2;
			if (img_in.rows - 1 <= py) py = img_in.rows - 2;

			uchar r1 = img_in.at<uchar>(py, px);
			uchar r2 = img_in.at<uchar>(py, px + 1);
			uchar r3 = img_in.at<uchar>(py + 1, px);
			uchar r4 = img_in.at<uchar>(py + 1, px + 1);
			double d1 = (double)x / (double)interpolations_rate - (double)px;
			double d2 = 1 - d1;
			double d3 = (double)y / (double)interpolations_rate - (double)py;
			double d4 = 1 - d3;
			uchar rx1 = d2 * r1 + d1 * r2;
			uchar rx2 = d2 * r3 + d1 * r4;

			img_out.at<uchar>(y, x) = d3 * rx2 + d4 * rx1;
		}
	}
	
	imshow("output image", img_out);


	waitKey(0);

}
