#include<opencv2/opencv.hpp>
#include<iostream>
#include<math.h>
using namespace std;
using namespace cv;

void Gradedgedet(Mat src,Mat des,int threshold1,int threshold2,int dx)
{
	Mat image;//,img2(src.rows,src.cols,CV_8UC3);
	//Sankalpx(src,img2,2);
	float delf,fx,fy;//,l;
	cvtColor(src,image,COLOR_BGR2YCrCb);

	for(int i=0;i<src.rows-2;i++)
	{
	for(int j=0;j<src.cols-3;j++)
	{
		fx=image.at<Vec3b>(i+dx,j)[0]-image.at<Vec3b>(i-dx,j)[0];
		fy=image.at<Vec3b>(i,j+dx)[0]-image.at<Vec3b>(i,j-dx)[0];
		delf=sqrt(fx*fx+fy*fy);		

		if(delf>=threshold1)
		{
		des.at<Vec3b>(i,j)=src.at<Vec3b>(i,j);
		//if((i+1)<src.rows)
		//des.at<Vec3b>(i+1,j)=Vec3b(0,255,0);
		}
		if(delf<threshold1&&delf>threshold2)
		{
		for(int k=i-1;k<=i+1;k++)
		for(int l=j-1;l<=j+1;l++)
		{
			if(des.at<Vec3b>(k,l)!=Vec3b(0,0,0))
			{  des.at<Vec3b>(i,j)=src.at<Vec3b>(i,j);
			   break;
			}
		}
		}
	}
	}

	//erode(des,des, getStructuringElement(MORPH_RECT, Size(3, 3)));
	  //morphological opening (remove small objects from the foreground)
  erode(des,des, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) );
  dilate( des,des, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 

   //morphological closing (fill small holes in the foreground)
  dilate( des,des, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) ); 
  erode( des,des, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
}
	
int main()
{
	Mat image=imread("/home/sankalp/Desktop/Blender/Images/cup1.png"),img2(image.rows,image.cols,CV_8UC3),img3(image.rows,image.cols,CV_8UC3);

	if(image.empty())
	{
		cout<<"\n Couldn't find or open the image.\n";
		cin.get();
		return -1;
	}
	
	Gradedgedet(image,img3,15,11,2);

	String wname="original_image",n3="Gardient edge detection";//,n2="Sankalp morphological operated image";

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
