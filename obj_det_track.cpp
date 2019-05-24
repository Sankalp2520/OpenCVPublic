#include<iostream>
#include<opencv2/opencv.hpp>
#include<unistd.h>

using namespace std;
using namespace cv;

Point Locate_obj(Mat img)
{
	double count_mass=0.0,m10=0.0,m01=0.0;
	for(int i=0;i<img.rows;i++)
	for(int j=0;j<img.cols;j++)
	{
		if(img.at<uchar>(i,j)==255)
		{
		m01+=i;
		m10+=j;
		count_mass++;
	
		}
		
	}

	return Point((int)(m10/count_mass),(int)(m01/count_mass));
}

int main()
{
	VideoCapture cap("/home/sankalp/Desktop/Blender/movies/ball_on_cloth/red_ball.avi");
	//VideoCapture cap(0);
	if(cap.isOpened()==false)
	{
		cout<<"Cannot find or load 24fps.avi";
		cin.get();
		return -1;
	}

	Mat img(cap.get(CAP_PROP_FRAME_HEIGHT),cap.get(CAP_PROP_FRAME_WIDTH),CV_8UC3);

	Mat thresholdedimg(img.rows,img.cols,CV_8UC3),img2(img.rows,img.cols,CV_8U),imglines(img.rows,img.cols,CV_8UC3);

	namedWindow("slider");
	namedWindow("Original image",WINDOW_NORMAL);
	namedWindow("Object_detected2",WINDOW_NORMAL);
	//namedWindow("imglines",WINDOW_NORMAL);

	int lowH=0,highH=26;
	int lowS=181,highS=255;
	int lowV=0,highV=255;

	createTrackbar("Low Hue","slider",&lowH,179);
 
	createTrackbar("high Hue","slider",&highH,179);

	createTrackbar("Low Saturation","slider",&lowS,255);
 
	createTrackbar("high Saturation","slider",&highS,255);

	createTrackbar("Low Value","slider",&lowV,255);
 
	createTrackbar("high Value","slider",&highV,255);

 	Point obj_pos,prev_obj_pos=Point(-1,-1);



while(true)
{
	if(!cap.read(img))
		{
			cout<<"Found the end of the video"<<endl;
			break;
		}

	cvtColor(img,thresholdedimg,COLOR_BGR2HSV);
	//ObjectDetection
	inRange(thresholdedimg,Scalar(lowH,lowS,lowV),Scalar(highH,highS,highV),img2);

	erode(img2,img2,getStructuringElement(MORPH_ELLIPSE,Size(5,5)));
	dilate(img2,img2,getStructuringElement(MORPH_ELLIPSE,Size(5,5)));
	dilate(img2,img2,getStructuringElement(MORPH_ELLIPSE,Size(5,5)));
	erode(img2,img2,getStructuringElement(MORPH_ELLIPSE,Size(5,5)));


	//ObjectDetection ends
	//Object Location

	obj_pos=Locate_obj(img2);

	//Object Location ends

	cout<<obj_pos<<" "<<prev_obj_pos<<endl;

	if(waitKey(10)==27)
		{
			cout<<"Esc key is pressed by user. Stopping the video"<<endl;
			break;
		}
	usleep(100000);
	//object tracking
	if((obj_pos.x>=0)&&(obj_pos.y>=0)&&(prev_obj_pos.x>=0)&&(prev_obj_pos.y>=0))
	line(imglines,obj_pos,prev_obj_pos,Scalar(255,0,0),2,CV_AA,0);
	prev_obj_pos=obj_pos;
	img=img+imglines;
	imshow("Original image",img);
	//imshow("imglines",imglines);
	imshow("Object_detected2",img2);
	//object tracking ends
	
}
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
