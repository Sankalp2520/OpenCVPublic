#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat img=imread("/home/sankalp/Desktop/Blender/movies/ball_on_cloth/0033.png");
	Mat img2(img.rows,img.cols,CV_8U),img3(img.rows,img.cols,CV_8U);

	namedWindow("Hello",WINDOW_NORMAL);
	namedWindow("Bye",WINDOW_NORMAL);
	namedWindow("Wall",WINDOW_NORMAL);

	img.copyTo(img2);

	inRange(img,Scalar(100,100,100),Scalar(200,200,200),img);

	for(int i=0;i<img.rows;i++)
	for(int j=0;j<img.cols;j++)
	{
	 img3.at<uchar>(i,j)=img.at<Vec3b>(i,j)[0];
	}
	imshow("Hello",img);
	imshow("Bye",img2);
	imshow("Wall",img3);
	waitKey(0);
	return 0;
}
