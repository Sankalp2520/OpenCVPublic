#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img=imread("/home/sankalp/Desktop/Blender/Images/cube.png");
	Mat invert(img.rows,img.cols,CV_8UC3),invert2,hblur,gblur,mblur,bblur;

	for(int i=0;i<img.rows;i++)
	{
	for(int j=0;j<img.cols;j++)
	{
		invert.at<Vec3b>(i,j)[0]=255-img.at<Vec3b>(i,j)[0];
		invert.at<Vec3b>(i,j)[1]=255-img.at<Vec3b>(i,j)[1];
		invert.at<Vec3b>(i,j)[2]=255-img.at<Vec3b>(i,j)[2];
	}	
	}
	bitwise_not(img,invert2);
	blur(img,hblur,Size(5,5));
	GaussianBlur(img,gblur,Size(3,3),1);
	medianBlur(img,mblur,5);
	bilateralFilter(img,bblur,15,80,80);

	namedWindow("img",WINDOW_NORMAL);
	namedWindow("inverted",WINDOW_NORMAL);
	namedWindow("inverted2",WINDOW_NORMAL);
	namedWindow("hblur",WINDOW_NORMAL);
	namedWindow("gblur",WINDOW_NORMAL);
	namedWindow("mblur",WINDOW_NORMAL);
	namedWindow("bblur",WINDOW_NORMAL);

	imshow("img",img);
	imshow("inverted",invert);
	imshow("inverted2",invert2);
	imshow("hblur",hblur);
	imshow("gblur",gblur);
	imshow("mblur",mblur);
	imshow("bblur",bblur);

	waitKey(0);

	return 0;
}

	
