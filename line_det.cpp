#include<iostream>
#include<opencv2/opencv.hpp>
#include<math.h>

#define pi 3.1415

using namespace std;
using namespace cv;

Mat img,Template,result,point_res,hough;

typedef uchar Pixel;

Point findMax()
{
	Point max;
	int index=0;
	for(int x=0;x<hough.cols;x++)
		for(int y=0;y<hough.rows;y++)
		{
			if(index<hough.at<uchar>(y,x)) 
				{
					index=hough.at<uchar>(y,x);
					max=Point(x,y);
				}
		}
		return max;
}
					//correlateAt and findTemplate are functions to find circles
int correlateAt(int x,int y)
{
	long int l=0;
	for(int x1=0;x1<Template.cols;x1++)
		for(int y1=0;y1<Template.rows;y1++)
		{
			if(y-Template.rows/2+y1>0&&x-Template.cols/2+x1>0&&y-Template.rows/2+y1<img.rows&&x-Template.cols/2+x1<img.rows)
			l+=(img.at<uchar>(y-Template.rows/2+y1,x-Template.cols/2+x1)*Template.at<uchar>(y1,x1));
		}
		//cout<<x<<","<<y<<"="<<l/(255*70*61)<<"|";
		return (l/(255*16*15));
}

void findTemplate()
{
	/*cout<<"called";
	cout<<img.rows<<" "<<img.cols;*/
	/*for(int x=0;x<img.cols;x+=5)
	{
		for(int y=0;y<img.rows;y+=5)
		{
			//cout<<y;
			correlateAt(x,y);
			//cout<<result.at<uchar>(y,x)<<":";
		}
		//cout<<x<<endl;
	}*/

	result.forEach<Pixel>([](Pixel &p, const int * position) -> void {
    p=correlateAt(position[1],position[0]);
		/*cout<<position[0]<<" "<<position[1]<<"=";
		p=1;*/
		//cout<<(int)p<<"@";
});
	//findMax();	
}

void Hough(int x,int y)
{
	float d;
	Point prev=Point(-1,-1);
	int vote=40;
	for(int theta=0;theta<hough.cols;theta++)
	{
		d=450+(x*cos(theta*pi/180)+y*sin(theta*pi/180));
		if(d>0&&d<hough.rows)
		{
			hough.at<uchar>(d,theta)+=vote;
			//line(hough,prev,Point(theta,d),Scalar(hough.at<uchar>(d,theta)),0,/*CV_AA*/8,0);
		}
		//cout<<(x*cos(theta*pi/180)+y*sin(theta*pi/180))<<"@"<<theta<<"|";
		prev=Point(theta,d);
	}
}

void findLine()
{
	float y1;
		Point solution=findMax();
//cout<<"solution = "<<solution;
	Point prev=Point(-1,-1);
	//draw line on point result
	for(int x1=0;x1<point_res.cols;x1++)
	{
		y1=(-450+solution.y-x1*cos(solution.x*pi/180))/sin(solution.x*pi/180);
		if(y1>0&&y1<point_res.rows)
			line(point_res,prev,Point(x1,y1),Scalar(100),0,CV_AA,0);
		prev=Point(x1,y1);
	}
}

int main()
{
	img=imread("line.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	Template=imread("template.jpg",CV_LOAD_IMAGE_GRAYSCALE);

	result=Mat::zeros(img.rows,img.cols,CV_8U);
	hough=Mat::zeros(900,180,CV_8U);

	cout<<img.rows<<" "<<img.cols;

	findTemplate();

	inRange(result,Scalar(99),Scalar(100),point_res);

	for(int x=0;x<point_res.cols;x++)
		for(int y=0;y<point_res.rows;y++)
		{
			if(point_res.at<uchar>(y,x)==255)
			Hough(x,y);
		}

		findLine();

	namedWindow("line",WINDOW_NORMAL);
	namedWindow("result",WINDOW_NORMAL);
	namedWindow("point_result",WINDOW_NORMAL);
	namedWindow("hough",WINDOW_NORMAL);
	

    imshow("line",img);
    imshow("result",result);
    imshow("point_result",point_res);
    imshow("hough",hough);
    
    waitKey(0);

	return 0;
}