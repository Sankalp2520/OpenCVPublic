#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Point Locate_obj(Mat img)
{
	double count_mass=0.0,m10=0.0,m01=0.0;
	//Mat temp(img.rows,img.cols,CV_8UC3);
	//cvtColor(img,img,COLOR_HSV2BGR);
	//cvtColor(img,temp,COLOR_BGR2GRAY);
	for(int i=0;i<img.rows;i++)
	for(int j=0;j<img.cols;j++)
	{
		if(img.at<uchar>(i,j)==255)
		{
		m01+=i;
		m10+=j;
		count_mass++;//}
	
		}
	//	cout<<j<<","<<i<<"	"<<img.at<uchar>(i,j)<<endl;	
	}
	//cout<<m01<<" "<<m10<<" "<<count_mass<<endl;
	return Point((int)(m10/count_mass),(int)(m01/count_mass));
}

int main()
{
	Mat img=imread("/home/sankalp/Desktop/Blender/movies/ball_on_cloth/0033.png");

	Mat thresholdedimg(img.rows,img.cols,CV_8UC3),img2(img.rows,img.cols,CV_8U);
	//Mat img3(img.rows,img.cols,CV_8U);
	cvtColor(img,thresholdedimg,COLOR_BGR2HSV);



	namedWindow("slider");
	namedWindow("Original image",WINDOW_NORMAL);
	//namedWindow("Object_detected",WINDOW_NORMAL);
	namedWindow("Object_detected2",WINDOW_NORMAL);
	//namedWindow("Object_detected3",WINDOW_NORMAL);

	int lowH=0,highH=26;
	int lowS=181,highS=255;
	int lowV=0,highV=255;

	createTrackbar("Low Hue","slider",&lowH,179);
 
	createTrackbar("high Hue","slider",&highH,179);

	createTrackbar("Low Saturation","slider",&lowS,255);
 
	createTrackbar("high Saturation","slider",&highS,255);

	createTrackbar("Low Value","slider",&lowV,255);
 
	createTrackbar("high Value","slider",&highV,255);

 	Point obj_pos;

	imshow("Original image",img);

//while(true)
//{
	//ObjectDetection
	inRange(thresholdedimg,Scalar(lowH,lowS,lowV),Scalar(highH,highS,highV),img2);

		//thresholdedimg.copyTo(img2);

		//cvtColor(img2,img2,COLOR_BGR2GRAY);

	//erode(thresholdedimg,thresholdedimg,getStructuringElement(MORPH_ELLIPSE,Size(5,5)));
	//dilate(thresholdedimg,thresholdedimg,getStructuringElement(MORPH_ELLIPSE,Size(5,5)));
	//dilate(thresholdedimg,thresholdedimg,getStructuringElement(MORPH_ELLIPSE,Size(5,5)));
	//erode(thresholdedimg,thresholdedimg,getStructuringElement(MORPH_ELLIPSE,Size(5,5)));
	erode(img2,img2,getStructuringElement(MORPH_ELLIPSE,Size(5,5)));
	dilate(img2,img2,getStructuringElement(MORPH_ELLIPSE,Size(5,5)));
	dilate(img2,img2,getStructuringElement(MORPH_ELLIPSE,Size(5,5)));
	erode(img2,img2,getStructuringElement(MORPH_ELLIPSE,Size(5,5)));
	//ObjectDetection ends

	//inRange(thresholdedimg,Scalar(255,255,255),Scalar(255,255,255),img2);

		//imshow("Object_detected",thresholdedimg);
			imshow("Object_detected2",img2);
		//imshow("xyz",img2);
	//if(waitKey(0)==27)
	//{ //Object Position
	
/*
for(int i=0;i<img2.rows;i++)
	for(int j=0;j<img2.cols;j++)
	{
		img3.at<uchar>(i,j)=img2.at<uchar>(i,j);
		if((thresholdedimg.at<Vec3b>(i,j)[2]+thresholdedimg.at<Vec3b>(i,j)[1]+thresholdedimg.at<Vec3b>(i,j)[0])==765)
		{
			cout<<j<<","<<i<<"	"<<thresholdedimg.at<Vec3b>(i,j)<<endl;
		}
	
	}
	imshow("Object_detected3",img3);
	waitKey(0);*/

	obj_pos=Locate_obj(img2);

	//Object Postion ends

	cout<<obj_pos<<endl;

	waitKey(0);

	//break;


//}
/*
 //Calculate the moments of the thresholded image
  Moments oMoments = moments(img2);

   double dM01 = oMoments.m01;
  double dM10 = oMoments.m10;
  double dArea = oMoments.m00;

   // if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero 
  if (dArea > 10000)
  {
   //calculate the position of the ball
   int posX = dM10 / dArea;
   int posY = dM01 / dArea; 

	cout<<"posX,posY "<<posX<<posY;     
}*/

	destroyWindow("Original image");
	destroyWindow("Object_detected");
	destroyWindow("slider");
  return 0;
}
