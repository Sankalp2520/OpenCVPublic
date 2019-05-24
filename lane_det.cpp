#include<iostream>
#include<opencv2/opencv.hpp>
#include<math.h>
#include<vector>

#define pi 3.1415
#define vote 2
//#define partition 50
using namespace std;
using namespace cv;

Mat frame,canny,hough,lines,lines2;
vector<Point> sols;

void findSols(int x1,int y1,Point partition,Mat des,int threshold)
{
	Point maxp,prev=Point(-1,-1);
	int max=0;
	//sols.clear();
	
	float j;
	for(int x=0;x<hough.cols;x++)
		for(int y=0;y<hough.rows;y++)
		{
		// 	if(t2==6)
		// cout<<(int)hough.at<uchar>(y,x)<<" ";
			if(hough.at<uchar>(y,x)>max)
			{
				max=hough.at<uchar>(y,x);
				maxp=Point(x,y);
			}
		}

			if(max>threshold)	
			for(int i=0;i<partition.x;i++)
			{
				j=((-partition.x*1.414+maxp.y)-i*cos(maxp.x*pi/180))/sin(maxp.x*pi/180);
				if(j>0&&j<partition.y&&prev.x!=-1)
					//if(canny.at<uchar>(y1+j,x1+i)==255)
					line(lines,prev,Point(x1+i,y1+j),Scalar(255,255,255),2,CV_AA,0);
					prev=Point(x1+i,y1+j);
					//des.at<uchar>(y1+j,x1+i)=255;
			}
		
		//cout<<"hell";
		//return max;
	
}
void findSols2(int x1,int y1,Point partition,Mat des,int threshold,int t2)
{
	//Point maxp;
	int max=0;
	//sols.clear();
	
	float j;
	for(int x=0;x<hough.cols;x++)
		for(int y=0;y<hough.rows;y++)
		{
		 //cout<<(int)hough.at<uchar>(y,x)<<" ";
			if(hough.at<uchar>(y,x)>max)
			{
				max=hough.at<uchar>(y,x);
				//maxp=Point(x,y);
			}
		}

	if(max>threshold)
	{
				// sols.push_back(Point(y,x));
				//Point prev=Point(-1,-1);
				//draw line on point result
	for(int x=0;x<hough.cols;x++)
		for(int y=0;y<hough.rows;y++)
		{
			if(hough.at<uchar>(y,x)>max-t2)	
			for(int i=0;i<partition.x;i++)
			{
				j=((-partition.x*1.414+y)-i*cos(x*pi/180))/sin(x*pi/180);
				if(j>0&&j<partition.y/*&&prev.x!=-1*/)
					if(canny.at<uchar>(y1+j,x1+i)==255)
					//line(lines,prev,Point(x1+i,y1+j),Scalar(255,255,255),2,CV_AA,0);
				//prev=Point(x1+i,y1+j);
					des.at<uchar>(y1+j,x1+i)=255;
			}
		}
		//cout<<"hell";
		//return max;
	}
}

/*void findLines(int x,int y)
{
	float j;
	//cout<<sols.size();
	for(int r=0;r<sols.size();r++)
	{
		Point solution=sols[r];
	
		//cout<<"solution = "<<solution;
		Point prev=Point(-1,-1);
		//draw line on point result
		for(int i=0;i<partition;i++)
		{
			j=((-partition*1.414+solution.y)-i*cos(solution.x*pi/180))/sin(solution.x*pi/180);
			if(j>0&&j<partition&&prev.x!=-1)
				//if(canny.at<uchar>(y+j,x+i)==255)
				line(frame,prev,Point(x+i,y+j),Scalar(255,0,0),0,CV_AA,0);
			prev=Point(x+i,y+j);
		}
	}
}*/

void Hough(Mat img,Mat des,Point partition,int threshold)
{
	float d;
	//Point prev=Point(-1,-1);
	//Mat part=Mat(partition,partition,CV_8U);
	for(int x=0;x<img.cols-partition.x;x+=partition.x)
	{
		for(int y=img.rows/2;y<img.rows-partition.y;y+=partition.y)
	{
		hough=Mat::zeros((int)(partition.x*2*1.414),180,CV_8U);
		for(int i=0;i<partition.x;i++)
			{
				for(int j=0;j<partition.y;j++)
				{

					//part.at<uchar>(j,i)=canny.at<uchar>(y+j,x+i);
					if(img.at<uchar>(y+j,x+i)==255)
					{
						for(int theta=0;theta<hough.cols;theta++)
						{
							d=partition.x*1.414+((i)*cos(theta*pi/180)+(j)*sin(theta*pi/180));

							if(d>0&&d<hough.rows)
							{
								hough.at<uchar>(d,theta)+=vote;
							}
						}
					}
				}
			}
		/*namedWindow("hough",WINDOW_NORMAL);
		imshow("hough",hough);

waitKey(1);*/
		//lines=Mat::zeros(frame.rows,frame.cols,CV_8U);
		findSols(x,y,partition,des,threshold);
		//findLines(x,y);
	}
	}
}

void Hough2(Mat img,Mat des,Point partition,int threshold,int t2)
{
	float d;
	//Point prev=Point(-1,-1);
	//Mat part=Mat(partition,partition,CV_8U);
	for(int x=0;x<img.cols-partition.x;x+=partition.x)
	{
		for(int y=img.rows/2;y<img.rows-partition.y;y+=partition.y)
	{
		hough=Mat::zeros((int)(partition.x*2*1.414),180,CV_8U);
		for(int i=0;i<partition.x;i++)
			{
				for(int j=0;j<partition.y;j++)
				{

					//part.at<uchar>(j,i)=canny.at<uchar>(y+j,x+i);
					if(img.at<uchar>(y+j,x+i)==255)
					{
						for(int theta=0;theta<hough.cols;theta++)
						{
							d=partition.x*1.414+((i)*cos(theta*pi/180)+(j)*sin(theta*pi/180));

							if(d>0&&d<hough.rows)
							{
								hough.at<uchar>(d,theta)+=vote;
							}
						}
					}
				}
			}
		/*namedWindow("hough",WINDOW_NORMAL);
		imshow("hough",hough);

waitKey(1);*/
		//lines=Mat::zeros(frame.rows,frame.cols,CV_8U);
		findSols2(x,y,partition,des,threshold,t2);
		//findLines(x,y);
	}
	}
}
int main()
{
	namedWindow("original",WINDOW_NORMAL);
	namedWindow("lines",WINDOW_NORMAL);
	namedWindow("canny",WINDOW_NORMAL);
	namedWindow("lines2",WINDOW_NORMAL);
	

	VideoCapture cap("/home/sankalp/Desktop/opencv/challenge.mp4");

	while(true)
	{
		/*bool bSuccess=*/cap.read(frame);
		
		/*if(bSuccess==false)
		{
			cout<<"Found the end of the video"<<endl;
			break;
		}*/
		Canny(frame,canny,340,360);
		lines=Mat::zeros(frame.rows,frame.cols,CV_8U);
		lines2=Mat::zeros(frame.rows,frame.cols,CV_8U);
		Hough(canny,lines,Point(50,50),2);
		Hough2(lines,lines2,Point(frame.cols-1,frame.rows/2-1),10,2);

		imshow("original",frame);
	 	imshow("lines",lines);
    	imshow("canny",canny);
    	imshow("lines2",lines2);

    	if(waitKey(10)==27)
		{
			cout<<"Esc key is pressed by user. Stopping the video"<<endl;
			break;
		}
	}	

    
    waitKey(0);

	return 0;
}