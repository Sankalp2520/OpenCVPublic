#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;
//Sankalps morphological operation :
//values of pixel at even places of y coordinate are replaced by min value of pixel in the kernel
//values of pixel at odd places of y coordinate are replaced by max value of pixel in the kernel

Point minof(Mat img,int x, int y,int size)
{
	int min=255,m;
	Point minp;
for(int i=y-size/2;i<=y+size/2;i++)
	{
	for(int j=x-size/2;j<=x+size/2;j++)
	{
	if(i>-1&&j>-1&&i<img.rows&&j<img.cols)
	{
		m=img.at<Vec3b>(i,j)[0];
		if(m<min)
			{
			min=m;
			minp=Point(i,j);
			}
	}
	}
	}
	return minp;
}

Point maxof(Mat img,int x,int y,int size)
{
	int max=0,m;
	Point maxp;
for(int i=y-size/2;i<=y+size/2;i++)
	{
	for(int j=x-size/2;j<=x+size/2;j++)
	{
	if(i>-1&&j>-1&&i<img.rows&&j<img.cols)
	{
		m=img.at<Vec3b>(i,j)[0];
		if(m>max)
		{
			max=m;
			maxp=Point(i,j);
		}
	}
	}
	}
	return maxp;
}

void Sankalpx(Mat src, Mat des, int size)
{
	cout<<src.rows<<" "<<src.cols;
	for(int i=0;i<src.rows;i+=2)
	{
		for(int j=0;j<src.cols;j++)
		{
		des.at<Vec3b>(i,j)=src.at<Vec3b>(minof(src,j,i,size));
		if((i+1)<src.rows)		
		des.at<Vec3b>(i+1,j)=src.at<Vec3b>(maxof(src,j,i+1,size));
		}}
}

int main()
{
	//Mat image=imread("/home/sankalp/Desktop/Blender/Images/cup1.png"),img2;

	cout<<"Hello";
	Mat image(3,5,CV_8UC3),img2(3,5,CV_8UC3);
	uchar array[]={
		   255,255,255 , 255,255,255 , 0,0,0 , 255,255,255 , 255,255,255,
		   255,255,255 ,    0,0,0    , 0,0,0 ,    0,0,0    , 255,255,255,
		   255,255,255 , 255,255,255 , 0,0,0 , 255,255,255 , 255,255,255
		  };
	image.data=array;
	if(image.empty())
	{
		cout<<"\n Couldn't find or open the image.\n";
		cin.get();
		return -1;
	}



	cvtColor(image,image,COLOR_BGR2YCrCb);

	Sankalpx(image,img2,2);

	//cout<<"\n "<<img2.data;
	
	return 0;
}

