#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat image(600,800,CV_8UC3,Scalar(250,40,40));

	String windowname="Blank image";

	namedWindow(windowname);

	imshow(windowname,image);

	waitKey(0);

	destroyWindow(windowname);

	return 0;
}
