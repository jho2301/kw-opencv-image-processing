#include <opencv2/opencv.hpp>
#include <math.h>
#include <opencv/cv.h>

using namespace cv;
using namespace std;

void main()
{


	Mat img_in = imread("C:\\Users\\wjsgh\\Desktop\\img.jpg", IMREAD_COLOR);

  //첫 번째 방법
	imshow("img_in", img_in);
	Vec3b pixel = img_in.at<Vec3b>(230, 230);
	printf("%d %d %d", pixel[0], pixel[1], pixel[2]);
	
  //두 번째 방법
	int pixel0 = img_in.data[0];
	int pixel1 = img_in.data[1];
	int pixel2 = img_in.data[2];
	printf("%d %d %d", pixel0, pixel1, pixel2);

	waitKey(0);

}
