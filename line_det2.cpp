#include<iostream>
#include<opencv2/opencv.hpp>
#include<math.h>
#include<vector>

#define pi 3.1415
#define vote 0.1
using namespace std;
using namespace cv;

Mat frame,canny,hough;
vector<Point> sols;
vector<Mat> rgbChannels(3);

void findSols()
{
	Point maxp;
	//int index=0;*/
	int max=0;
	sols.clear();
	for(int x=0;x<hough.cols-10;x+=10)
		for(int y=0;y<hough.rows-50;y+=50)
		{//cout<<x<<" ";
			max=0;
			for(int i=0;i<10;i++)
			{
				for(int j=5;j<45;j++)
				{
					if(hough.at<float>(y+j,x+i)>max) 
					{
					max=hough.at<float>(y+j,x+i);
					maxp=Point(x+i,y+j);
					}
				}
			}
			if(max>5)
			{
			/*for(int i=0;i<10;i++)
			{
				for(int j=5;j<45;j++)
				{
					if(hough.at<float>(y+j,x+i)>=max-1) 
					{*/
						sols.push_back(maxp);
					/*}
				}
			}*/
		}
		}

		//return max;
}

void Hough(int x,int y)
{
	float d;
	//Point prev=Point(-1,-1);
/*
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
	{
			if(canny.at<uchar>(y+j,x+i)==255)
		{*/
			for(int theta=0;theta<hough.cols;theta++)
			{
				d=480+((x)*cos(theta*pi/180)+(y)*sin(theta*pi/180))/3;
				if(d>0&&d<hough.rows)
				{
					hough.at<float>(d,theta)+=vote;
				}
			}
		/*}
	}
	}*/
}

void findLines()
{
	float y1;
	//cout<<sols.size();
	for(int r=0;r<sols.size();r++)
	{
		Point solution=sols[r];
	
		//cout<<"solution = "<<solution;
		Point prev=Point(-1,-1);
		//draw line on point result
		for(int x1=0;x1<frame.cols;x1++)
		{
			y1=((-480+solution.y)*3-x1*cos(solution.x*pi/180))/sin(solution.x*pi/180);
			if(y1>0&&y1<frame.rows&&prev.x!=-1)
				//if(canny.at<uchar>(y1,x1)==255)
				line(frame,prev,Point(x1,y1),Scalar(255,0,0),2,CV_AA,0);
			prev=Point(x1,y1);
		}
	}
}

void remove()
{

	for(int x=0;x<frame.cols;x++)
	{
		for(int y=0;y<frame.rows;y++)
		if(rgbChannels[0].at<uchar>(y,x)<60&&rgbChannels[1].at<uchar>(y,x)<60&&rgbChannels[2].at<uchar>(y,x)<200&&rgbChannels[2].at<uchar>(y,x)>120)
			canny.at<uchar>(y,x)=255;
		/*else
			rgbChannels[0].at<uchar>(y,x)=0;*/
	}
}

int main()
{
	//frame=imread("line.jpg",CV_LOAD_IMAGE_GRAYSCALE);

	//result=Mat::zeros(frame.rows,frame.cols,CV_8U);
	hough=Mat::zeros(1280,180,CV_32F);
	//grad=Mat::zeros(900,180,CV_32F);

	namedWindow("line",WINDOW_NORMAL);
	namedWindow("canny",WINDOW_NORMAL);
	//namedWindow("hough",WINDOW_NORMAL);


	//cout<<frame.rows<<" "<<frame.cols;
	VideoCapture cap("/home/sankalp/Desktop/opencv/grasslane.avi");

	/*if(cap.isOpened()==false)
	{
		cout<<"Cannot find or load challenge.mp4";
		cin.get();
		return -1;
	}*/
	while(true)
	{
		/*bool bSuccess=*/cap.read(frame);
		//cvtColor(frame,frame,COLOR_BGR2HSV);
		//split(frame,rgbChannels);
		hough=Mat::zeros(1280,180,CV_32F);
		/*remove();
		erode(canny,canny, getStructuringElement(MORPH_ELLIPSE, Size(2,2)));
		dilate(canny,canny, getStructuringElement(MORPH_ELLIPSE, Size(5,5)));
		*/Canny(canny,canny,50,80);
		//dilate(canny,canny, getStructuringElement(MORPH_ELLIPSE, Size(10,10)));

		for(int x=0;x<canny.cols;x+=2)
			for(int y=0;y<canny.rows;y+=2)
			{
				if(canny.at<uchar>(y,x)==255)
				Hough(x,y);
			}

			findSols();
			findLines();
    	
    	imshow("line",frame);
    	imshow("canny",canny);
   /* 	for(int x=0;x<canny.cols;x++)
    	{
			for(int y=0;y<canny.rows;y++)
			{
				cout<<hough.at<float>(y,x)<<" ";
			}
			cout<<endl;
		}
 	*/
		if(waitKey(10)==27)
		{
			cout<<"Esc key is pressed by user. Stopping the video"<<endl;
			break;
		}
	}	

    
    waitKey(0);

	return 0;
}