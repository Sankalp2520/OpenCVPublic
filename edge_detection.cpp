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

/*void Sankalpx(Mat src, Mat des, int size)
{
	Mat image;
	cvtColor(src,image,COLOR_BGR2YCrCb);

	for(int i=0;i<src.rows;i+=2)
	{
		for(int j=0;j<src.cols;j++)
		{
		des.at<Vec3b>(i,j)=src.at<Vec3b>(minof(image,j,i,size));
		if((i+1)<src.rows)		
		des.at<Vec3b>(i+1,j)=src.at<Vec3b>(maxof(image,j,i+1,size));
		}
	}
}
	
void Sakedgedet(Mat src,Mat des,int thickness)
{
	Mat image,img2(src.rows,src.cols,CV_8UC3);
	Sankalpx(src,img2,2);
	int k,l,threshold=100-thickness;
	cvtColor(src,image,COLOR_BGR2YCrCb);
	src.copyTo(des);

	for(int i=0;i<src.rows-2;i++)
	{
	for(int j=0;j<src.cols-3;j++)
	{
		k=(image.at<Vec3b>(i,j)[0]-image.at<Vec3b>(i+2,j)[0]);
		k=k>0?k:-k;
		l=(image.at<Vec3b>(i,j)[0]-image.at<Vec3b>(i,j+3)[0]);
		l=l>0?l:-l;
		if(k>threshold||l>threshold)
		{
		des.at<Vec3b>(i,j)=Vec3b(0,255,0);
		//if((i+1)<src.rows)
		des.at<Vec3b>(i+1,j)=Vec3b(0,255,0);
		}
	}
	}
}
*/	
void Sakedgedet(Mat src,Mat des,int threshold,int ksize)
{
	Mat image;//,img2(src.rows,src.cols,CV_8UC3);
	//Sankalpx(src,img2,2);
	int k,max,min;//,l;
	cvtColor(src,image,COLOR_BGR2YCrCb);
	src.copyTo(des);

	for(int i=0;i<src.rows-2;i++)
	{
	for(int j=0;j<src.cols-3;j++)
	{
		max=image.at<Vec3b>(maxof(image,j,i,ksize))[0];
		min=image.at<Vec3b>(minof(image,j,i,ksize))[0];
		
		k=max-min;
		if(k>threshold)
		{
		des.at<Vec3b>(i,j)=Vec3b(0,255,0);
		//if((i+1)<src.rows)
		//des.at<Vec3b>(i+1,j)=Vec3b(0,255,0);
		}
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
	//Sankalpx(image,img2,2);
	Sakedgedet(image,img3,20,5);

	String wname="original_image",n3="SANKALP edge detection";//,n2="Sankalp morphological operated image";

	namedWindow(wname,WINDOW_NORMAL);

	imshow(wname,image);

	//namedWindow(n2,WINDOW_NORMAL);

	//imshow(n2,img2);

	namedWindow(n3,WINDOW_NORMAL);

	imshow(n3,img3);

	waitKey(0);

	destroyWindow(wname);
	destroyWindow(n3);
	//destroyWindow(n2);
	return 0;

}
