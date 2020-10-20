#include <opencv2/opencv.hpp>
#include <math.h>
#include <opencv/cv.h>

using namespace cv;
using namespace std;

void imshowFilterGRAY(Mat imgIn, void (filter)(Mat inPad, Mat out, int filterPhase), int filterSize)
{
	Mat out = imgIn.clone();
	filter(imgIn, out, filterSize);
	for (int i = 0; i < imgIn.rows * imgIn.cols; i++)
		imgIn.data[i] += out.data[i];
	imshow("filter<GRAY>", out);
	imshow("result<GRAY>", imgIn);
}

void imshowFilterRGB(Mat imgIn, void (filter)(Mat inPad, Mat out, int filterPhase), int filterSize)
{
	Mat out = imgIn.clone();
	filter(imgIn, out, filterSize);
	for (int h = 0; h < imgIn.rows; h++)
	{
		for (int w = 0; w < imgIn.cols; w++)
		{
			Vec3b& color = imgIn.at<Vec3b>(h, w);

			color[0] += out.at<Vec3b>(h, w)[0];
			color[1] += out.at<Vec3b>(h, w)[1];
			color[2] += out.at<Vec3b>(h, w)[2];
			imgIn.at<Vec3b>(h, w) = color;
		}
	}
	imshow("filter<RGB>", out);
	imshow("filter result<RGB>", imgIn);
}

void averageFilterGray(Mat inPad, Mat out, int filterPhase)
{
	int filterSize = 2 * filterPhase + 1;
	int filterSquare = filterSize * filterSize;
	int pad = filterSize / 2;

	uchar** temp = new uchar * [inPad.rows];
	for (int i = 0; i < inPad.rows; i++)
		temp[i] = new uchar[inPad.cols];

	for (int h = 0; h < inPad.rows; h++)
	{
		for (int w = 0; w < inPad.cols; w++)
		{
			uchar result = 0;
			for (int th = h - pad; th <= h + pad; th++)
			{
				int tempH;
				if (th < 0)
					tempH = 0;
				else if (inPad.rows <= th)
					tempH = inPad.rows - 1;
				else
					tempH = th;
				for (int tw = w - pad; tw <= w + pad; tw++)
				{
					int tempW;
					if (tw < 0)
						tempW = 0;
					else if (inPad.cols <= tw)
						tempW = inPad.cols - 1;
					else
						tempW = tw;
					result += inPad.at<uchar>(tempH, tempW);
				}
			}
			result /= filterSquare;
			temp[h][w] = result;
		}
	}
	for (int h = 0; h < out.rows; h++)
		for (int w = 0; w < out.cols; w++)
			out.at<uchar>(h, w) = temp[h][w];
}

void averageFilterRGB(Mat inPad, Mat out, int filterPhase)
{
	int filterSize = 2 * filterPhase + 1;
	int filterSquare = filterSize * filterSize;
	int pad = filterSize / 2;


	for (int h = 0; h < inPad.rows; h++)
	{
		for (int w = 0; w < inPad.cols; w++)
		{
			uchar resultR = 0;
			uchar resultG = 0;
			uchar resultB = 0;

			for (int th = h - pad; th <= h + pad; th++)
			{
				int tempH;
				if (th < 0)
					tempH = 0;
				else if (inPad.rows <= th)
					tempH = inPad.rows - 1;
				else
					tempH = th;
				for (int tw = w - pad; tw <= w + pad; tw++)
				{
					int tempW;
					if (tw < 0)
						tempW = 0;
					else if (inPad.cols <= tw)
						tempW = inPad.cols - 1;
					else
						tempW = tw;
					resultB += inPad.at<Vec3b>(tempH, tempW)[0];
					resultG += inPad.at<Vec3b>(tempH, tempW)[1];
					resultR += inPad.at<Vec3b>(tempH, tempW)[2];
				}
			}
			resultR = (uchar)(resultR / filterSquare);
			resultG = (uchar)(resultG / filterSquare);
			resultB = (uchar)(resultB / filterSquare);
			Vec3b& color = out.at<Vec3b>(h, w);
			color[0] =  resultB;
			color[1] =  resultG;
			color[2] =  resultR;
			out.at<Vec3b>(h, w) = color;
		}
	}

}

void main()
{
	Mat imgIn = imread("C:\\Users\\wjsgh\\Desktop\\img3.jpg", IMREAD_COLOR);
	Mat imgOutRgb = imgIn.clone();
	Mat imgInGray = Mat(imgIn.rows, imgIn.cols, CV_8UC1);
	Mat imgOutGray = Mat(imgIn.rows, imgIn.cols, CV_8UC1);


	imshow("original", imgIn);
	
	cvtColor(imgIn, imgInGray, CV_RGB2GRAY);
	imshow("gray", imgInGray);

	imshowFilterGRAY(imgInGray, averageFilterGray, 1);
	imshowFilterRGB(imgIn, averageFilterRGB, 1);


	waitKey(0);

}

