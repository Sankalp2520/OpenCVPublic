#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat img;

void sierpinski(Point a,Point b,Point c,int limit)
{
if(limit>0)
{	line(img,a,b,Scalar(255),1,CV_AA,0);
	line(img,b,c,Scalar(255),1,CV_AA,0);
	line(img,c,a,Scalar(255),1,CV_AA,0);
	imshow("Sierpinski",img);
	waitKey(10);
	sierpinski(a,(a+b)/2,(a+c)/2,limit-1);
	sierpinski(b,(c+b)/2,(a+b)/2,limit-1);
	sierpinski(c,(a+c)/2,(b+c)/2,limit-1);
}
else
	return;
}

int main()
{
	img=Mat::zeros(720,1080,CV_8U);
/*
	Point p0=Point(240,660),p1=Point(840,660),p2=Point(540,140);*/
	Point p0=Point(140,700),p1=Point(940,700),p2=Point(540,7);
	int limit=8;

	namedWindow("Sierpinski",WINDOW_NORMAL);

	sierpinski(p0,p1,p2,limit);
	imshow("Sierpinski",img);
	waitKey(0);
	return 0;
}