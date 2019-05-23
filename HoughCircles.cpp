#include<iostream>
#include<opencv2/opencv.hpp>
#include<math.h>
#include<float.h>
//typedef unsigned char uchar;
//#define UP 1234.567
//#define DOWN 9876.543
#define NONE 49.12345
#define votes 1
using namespace std;
using namespace cv;

Mat img;
Mat hough;

float getGradtheta(int x, int y)
{
	float dfy, dfx;

	dfy = img.at<uchar>(y,x)- img.at<uchar>(y-1, x);
	dfx = img.at<uchar>(y, x) - img.at<uchar>(y, x - 1);

	if (dfx != 0)
		return tan(dfy / (float)dfx);
	/*else {
		if (dfy > 0)
			return FLT_MAX;
		if (dfy < 0)
			return -FLT_MAX;
	}*/
    // (dfy == 0)
	return NONE;

}

void Houghcircles()
{
	float tan;
	int b;
	for(int x=1;x<img.cols;x++)
		for (int y = 1; y < img.rows; y++)
		{
			tan = getGradtheta(x,y);
			
			if (tan != NONE && tan !=0)
			{
				for (int a = 0; a < img.cols; a++)
				{
					b = y - tan * (x - a);
					if (b > 0 && b < img.rows)
						hough.at<uchar>(b, a) += votes;
				}
			}
		}
}

int main()
{
	img = imread("circle.jpg",0);
	hough = Mat::zeros(img.rows, img.cols, CV_8U);

	GaussianBlur(img, img, Size(3, 3), 1, 1);

	namedWindow("CIRCLES", WINDOW_NORMAL);
	namedWindow("HOUGH_CIRCLES", WINDOW_NORMAL);

	Houghcircles();

	imshow("CIRCLES", img);
	imshow("HOUGH_CIRCLES", hough);

	waitKey(0);

	return 0;
}