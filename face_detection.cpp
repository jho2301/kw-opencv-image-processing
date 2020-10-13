#include <opencv2/opencv.hpp>
#include <math.h>
#include <opencv/cv.h>

using namespace cv;
using namespace std;

void main()
{
	Mat img = imread("C:\\Users\\wjsgh\\Desktop\\img3.jpg", IMREAD_COLOR);
	Mat face_color = img.clone();
	Mat face_blacknwhite;

	cvtColor(img, face_blacknwhite, CV_BGR2GRAY);
	imshow("original", img);
	
	for (int h = 0; h < img.rows; h++) 
	{
		for (int w = 0; w < img.cols; w++)
		{
			uchar b = img.at<Vec3b>(h,w)[0];
			uchar g = img.at<Vec3b>(h,w)[1];
			uchar r = img.at<Vec3b>(h,w)[2];

			if ((85 <= b && b <= 165) && (102 <= g && g <= 192) && (152 <= r && r <= 234))
			{
				face_color.at<Vec3b>(h, w)[0] = b;
				face_color.at<Vec3b>(h, w)[1] = g;
				face_color.at<Vec3b>(h, w)[2] = r;

				face_blacknwhite.at<uchar>(h, w) = 255;
			
			}
			else
			{
				face_color.at<Vec3b>(h, w)[0] = 0;
				face_color.at<Vec3b>(h, w)[1] = 0;
				face_color.at<Vec3b>(h, w)[2] = 0;

				face_blacknwhite.at<uchar>(h, w) = 0;
			}
		}
	}
	
	imshow("face part colored", face_color);
	imshow("face map", face_blacknwhite);
	waitKey(0);
}
