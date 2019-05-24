#include<opencv2/opencv.hpp>
#include<iostream>
#include<limits.h>
#include <math.h>

using namespace std;
using namespace cv;

Mat img;

Point start,End,temp;
//int COUNT = 0;
class Vertex
{	public:
		short ani;
		Point prev,next;
}**vertex;

Point find_End()
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

Point backup_plan(Point index)
{
	//COUNT++;
	static int v=0,u=0;
	//cout<<u<<"::"<<v<<"|";
	for(;u<img.cols;u++)
	{
		if(v==img.rows)
			v=0;
		for(;v<img.rows;v++)
		{
			//cout<<u<<"::"<<v<<"|";
			if(vertex[v][u].ani==2)
			{
				/*cout<<u<<"::"<<v<<"|";*/
				return Point(u,v);
			}
		}
	}
}

void heuristic()
{
	float dist,min;
	Point index=start;
	long int count=0;
	while(true)
	{
		count++;
	min=INT_MAX;
	if(vertex[index.y][index.x].ani==1)
		index=backup_plan(index);
	//make ani of vertex found true as we are gonna initialize its neighbours
	 vertex[index.y][index.x].ani=1;
		//cout<<index<<":";
	 if(index==End)
	  {/*cout<<"yayy";*/break;}
	//initialization of neighbours of vertex found
	 for(int x1=index.x-2;x1<=index.x+2;x1++)
	 for(int y1=index.y-2;y1<=index.y+2;y1++)
	 {
	  if(x1>0&&y1>0&&x1<img.cols&&y1<img.rows)
	  {
	  	if(vertex[y1][x1].ani!=1&&(img.at<Vec3b>(y1,x1)[0]<100||img.at<Vec3b>(y1,x1)[1]<100||img.at<Vec3b>(y1,x1)[2]<100))
	  	{
	  	vertex[y1][x1].ani=2;
	  	vertex[y1][x1].prev=index;
	    }
	  	dist=sqrt((x1-End.x)*(x1-End.x)+(y1-End.y)*(y1-End.y));
	  if(min>dist&&vertex[y1][x1].ani!=1&&(img.at<Vec3b>(y1,x1)[0]<100||img.at<Vec3b>(y1,x1)[1]<100||img.at<Vec3b>(y1,x1)[2]<100))
	   {
		min=dist;
		temp=Point(x1,y1);
	   }
	  }
	 }
	 vertex[temp.y][temp.x].prev=Point(index.x,index.y);
	 index=temp;

	}
	 
	cout<<count;
	
	if(index==End) while(index!=start)
		{
		 temp=vertex[index.y][index.x].prev;
		 vertex[temp.y][temp.x].next=index;
		 index=temp;

		 //cout<<index<<"no::";
		}
}

int main()
{
	img=imread("q12.png");

	vertex=new Vertex*[img.rows];
	for(int i=0;i<img.rows;i++)
	vertex[i]=new Vertex[img.cols];

	start=find_start();
	End  =find_End();

	heuristic();

	/*VideoWriter oVideoWriter("heuristic.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 
                                                               60, Size(img.cols,img.rows), true);

 	if (oVideoWriter.isOpened() == false) 
    {
        cout << "Cannot save the video to a file" << endl;
        cin.get(); //wait for any key press
        return -1;
    }*/

	namedWindow("Hello",WINDOW_NORMAL);
	namedWindow("Hello1",WINDOW_NORMAL);
	imshow("Hello1",img);
	Point header=start,prev=Point(-1,-1);
	//cout<<header;
	long int n=0;
	while(header!=End)
	{
	 if(prev.x>0&&prev.y>0)
	 {
 	 line(img,header,prev,Scalar(255,100,100),2,CV_AA,0);
       	 imshow("Hello",img);
       	 /*if(n%30==0)
       	 oVideoWriter.write(img);*/ 
	 }
	 //if(n%10==0)
	 if(waitKey(10)==27)
		{
			cout<<"Esc key is pressed by user. Stopping the video"<<endl;
			break;
		}
	 prev=header;
	 header=vertex[header.y][header.x].next; 
	 n++;
	}
	
	/*for(int y=0;y<img.rows;y++)
	for(int x=0;x<img.cols;x++)
	{
		if(vertex[y][x].ani==1)
			img.at<Vec3b>(y,x)=Vec3b(255,100,100);
	}*/
	imshow("Hello",img);
	//cout<<endl<<COUNT;
	waitKey(0);
	delete vertex;
	return 0;
}

