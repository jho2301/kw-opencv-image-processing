#include <opencv2/opencv.hpp>
#include <math.h>
#include <opencv/cv.h>

using namespace cv;
using namespace std;

void main()
{
	Mat img_out;
	Mat img_in = imread("C:\\Users\\wjsgh\\Desktop\\Cat03.jpg", IMREAD_COLOR);
	
	cvtColor(img_in, img_in, COLOR_RGB2GRAY);
	imshow("img_in", img_in);

	int* Hist = new int[256];
	memset(Hist, 0, sizeof(int) * 256);

	for (int h = 0; h < img_in.rows; h++)
	{
		for (int w = 0; w < img_in.cols; w++)
		{
			Hist[img_in.at<uchar>(h, w)]++;
		}
	}
	int nMax = 0;
	for (int i = 0; i < 256; i++)
	{
		if (nMax < Hist[i])
			nMax = Hist[i];
	}
	double dNormalizeFactor = 255.0 / nMax;

	Mat HistDisp = Mat(256, 256, CV_8UC1);
	HistDisp = Scalar::all(0);

	for (int w = 0; w < 256; w++)
	{
		int nNormalizedValue = (int)Hist[w] * dNormalizeFactor;
		for (int h = 255; h > 255 - nNormalizedValue; h--)
		{
			HistDisp.at<uchar>(h, w) = 255;
		}
	}

	imshow("histogram", HistDisp);


	int cmulative_histogram[256] = { 0, };
	int sum = 0;

	for (int i = 1; i < 256; i++)
	{
		sum += (int)Hist[i];
		cmulative_histogram[i] = sum;
	}

	float normalized_cmulative_histogram[256] = { 0.0, };
	int image_size = img_in.rows * img_in.cols;

	for (int i = 0; i < 256; i++)
	{
		normalized_cmulative_histogram[i] = cmulative_histogram[i] / (float)image_size;
	}

	img_out = Mat(img_in.rows, img_in.cols, CV_8UC1);
	int histogram2[256] = { 0, };
	for (int y = 0; y < img_in.rows; y++)
	{
		for (int x = 0; x < img_in.cols; x++)
		{
			img_out.at<uchar>(y, x) = normalized_cmulative_histogram[img_in.at<uchar>(y, x)] * 255;
			histogram2[img_out.at<uchar>(y, x)] += 1;
		}
	}
	imshow("output image", img_out);


	waitKey(0);

}
