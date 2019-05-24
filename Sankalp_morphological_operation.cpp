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
			minp=Point(j,i);
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
			maxp=Point(j,i);
		}
	}
	}
	}
	return maxp;
}

void Sankalpx(Mat src, Mat des, int size)
{
	Mat image;
	cvtColor(src,image,COLOR_BGR2YCrCb);

	for(int i=0;i<src.rows;i+=2)
	{
		for(int j=0;j<src.cols;j++)
		{
		des.at<Vec3b>(i,j)=src.at<Vec3b>(minof(image,j,i,size));
				
		des.at<Vec3b>(i+1,j)=src.at<Vec3b>(maxof(image,j,i+1,size));
		}
	}
}
			
int main()
{
	Mat image=imread("/home/sankalp/Desktop/Blender/Images/cup1.png"),img2(image.rows,image.cols,CV_8UC3),img3(image.rows,image.cols,CV_8UC3);

	//Mat image(3,5,CV_8UC3),img2;
	/*uchar array[]={
		   255,255,255 , 255,255,255 , 0,0,0 , 255,255,255 , 255,255,255,
		   255,255,255 ,    0,0,0    , 0,0,0 ,    0,0,0    , 255,255,255,
		   255,255,255 , 255,255,255 , 0,0,0 , 255,255,255 , 255,255,255
		  };
	image.data=array;*/
	if(image.empty())
	{
		cout<<"\n Couldn't find or open the image.\n";
		cin.get();
		return -1;
	}

	Sankalpx(image,img2,2);
	Sankalpx(image,img3,5);

	String wname="original_image",n="Sankalp morphological operated image",n2="Sankalp morphological operated image2";

	namedWindow(wname,WINDOW_NORMAL);

	imshow(wname,image);

	namedWindow(n,WINDOW_NORMAL);

	imshow(n,img2);

	namedWindow(n2,WINDOW_NORMAL);

	imshow(n2,img3);

	waitKey(0);

	destroyWindow(wname);
	destroyWindow(n);
	destroyWindow(n2);
	return 0;

}
