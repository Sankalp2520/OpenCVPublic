#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

Mat img,weight;

Point find_end()
{
	Mat hsv,bw;

	cvtColor(img,hsv,COLOR_BGR2HSV);

	inRange(hsv,Scalar(0,177,46),Scalar(36,255,255),bw);  //hue of red is 0-20
	Moments omoments=moments(bw);
	double m10=omoments.m10;
	double m01=omoments.m01;
	double m00=omoments.m00;
	//cout<<m10/m00<<" "<<m01/m00<<" "<<(int)(m10/m00)<<" "<<(int)(m01/m00);
	
	return Point(m10/m00,m01/m00);
}

Point find_start()
{
	Mat hsv,bw;
	//namedWindow("END",WINDOW_NORMAL);
	cvtColor(img,hsv,COLOR_BGR2HSV);
	inRange(hsv,Scalar(35,177,46),Scalar(117,255,255),bw);  //hue of green is 110-130
	Moments omoments=moments(bw);
	double m10=omoments.m10;
	double m01=omoments.m01;
	double m00=omoments.m00;
	//imshow("END",bw);
	//waitKey(0);

	return Point(m10/m00,m01/m00);
}

int min_of_neighbours_of(int x,int y)
{
	int min=5000;
	for(int x1=x-1;x1<=x+1;x1++)
		for(int y1=y-1;y1<=y+1;y1++)
		{
			if(x1!=x||y1!=y){
			if(img.at<Vec3b>(y1,x1)[0]!=255||img.at<Vec3b>(y1,x1)[1]!=255||img.at<Vec3b>(y1,x1)[2]!=255)
			{if(weight.at<int>(y1,x1)<min)
			    {
				min=weight.at<int>(y1,x1);
			    }
			}}
		}
	return min;
}

Point min_neighbour_of(int x,int y)
{
	int min=5000;
	int x0,y0;
	for(int x1=x-1;x1<=x+1;x1++)
		for(int y1=y-1;y1<=y+1;y1++)
		{
			if(x1!=x||y1!=y){
			if(img.at<Vec3b>(y1,x1)[0]!=255||img.at<Vec3b>(y1,x1)[1]!=255||img.at<Vec3b>(y1,x1)[2]!=255)
			{if(weight.at<int>(y1,x1)<min)
			    {
				min=weight.at<int>(y1,x1);
				x0=x1;
				y0=y1;
			    }
			}}
		}
return Point(x0,y0);
}

void planner()
{
	
	Point end=find_end();

	//weight.at<int>(end.y,end.x)=0;
	//cout<<weight.at<int>(end.y,end.x);
	int x,y;
	
//initialize weight of neighbours of end point as 1;
	for(x=end.x-1;x<=end.x+1;x++)
		for(y=end.y-1;y<=end.y+1;y++)
		weight.at<int>(y,x)=1;
//iterate from all directions to distribute weights
	for(x=1;x<img.cols-1;x++)
	for(y=1;y<img.rows-1;y++)
	weight.at<int>(y,x)=min_of_neighbours_of(x,y)+1;//if(weight.at<int>(y,x)!=5001)cout<<weight.at<int>(y,x)<<"::"<<x<<":"<<y<<"|";}

	for(x=img.cols-1;x>0;x--)
	for(y=1;y<img.rows-1;y++)
	weight.at<int>(y,x)=min_of_neighbours_of(x,y)+1;

	for(x=img.cols-1;x>0;x--)
	for(y=img.rows-1;y>0;y--)
	weight.at<int>(y,x)=min_of_neighbours_of(x,y)+1;

	for(x=1;x<img.cols-1;x++)
	for(y=img.rows-1;y>0;y--)
	weight.at<int>(y,x)=min_of_neighbours_of(x,y)+1;

	for(y=1;y<img.rows-1;y++)
	for(x=1;x<img.cols-1;x++)
	weight.at<int>(y,x)=min_of_neighbours_of(x,y)+1;

	for(y=img.rows-1;y>0;y--)
	for(x=1;x<img.cols-1;x++)
	weight.at<int>(y,x)=min_of_neighbours_of(x,y)+1;

	for(y=img.rows-1;y>0;y--)
	for(x=img.cols-1;x>0;x--)
	weight.at<int>(y,x)=min_of_neighbours_of(x,y)+1;

	for(y=1;y<img.rows-1;y++)
	for(x=img.cols-1;x>0;x--)
	weight.at<int>(y,x)=min_of_neighbours_of(x,y)+1;	
}

int main()
{
	img=imread("path.jpg");
	weight=Mat(img.rows,img.cols,CV_32S);
	weight.setTo(Scalar(5000));

	planner();
	//Point end=find_end();
	//cout<<weight.at<int>(header.y,header.x);
	//header = min_neighbour_of(header.x,header.y);
	//cout<<weight.at<int>(end.y-1,end.x-1);	
/*
	for(int x=1;x<img.cols-1;x+=2)
	for(int y=1;y<img.rows-1;y+=2)
	if(weight.at<int>(y,x)!=5002)
	cout<<weight.at<int>(y,x)<<" ";
*/
	Point header=find_start();
	//cout<<header.x<<" "<<header.y;
	//waitKey(5000);
	Point end=find_end();
int i=0;
	while(i<30000)//(weight.at<int>(header.y,header.x)!=9)
	{
	img.at<Vec3b>(header.y,header.x)=Vec3b(255,100,100);
	header = min_neighbour_of(header.x,header.y);i++;
	//cout<<header.y<<"::"<<header.x<<"|";
	}
	namedWindow("Hello",WINDOW_NORMAL);
	imshow("Hello",img);
	waitKey(0);
	destroyWindow("Hello");
	return 0;
}
