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
		float g;
		float f;
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
	if(u==img.cols)
			u=0;
	for(;u<img.cols;u++)
	{
		if(v==img.rows)
			v=0;
		for(;v<img.rows;v++)
		{
			//cout<<u<<"::"<<v<<"|";
			if(vertex[v][u].ani==0)
			{
				/*cout<<u<<"::"<<v<<"|";*/
				return Point(u,v);
			}
		}
	}
}

Point fvwgwnani(int x0,int y0)
{
	int min=numeric_limits<float>::max();
	Point index;
	bool flag=0;
	for(int x=x0-1;x<=x0+1;x++)
	for(int y=y0-1;y<=y0+1;y++)
	{
		//cout<<x<<","<<y<<" "<<vertex[y][x].f;
		if(x>0&&y>0&&x<img.cols&&y<img.rows)
	  {
		if((vertex[y][x].ani==-1||vertex[y][x].ani==0)&&vertex[y][x].f<min&&(img.at<Vec3b>(y,x)[0]<100||img.at<Vec3b>(y,x)[1]<100||img.at<Vec3b>(y,x)[2]<100))
		{
			min=vertex[y][x].f;
			index=Point(x,y);
			flag=1;
		}
	  }
	}
	if(flag==0)
		return Point(x0,y0);
	return index;
}

void astar()
{
	long int y;
	int x;
	float dist;
	Point index=start;//,temp;
	//initialise all vertices with ani=false & g=numeric_limits<float>::max(); 
	for(y=0;y<img.rows;y++)
		for(x=0;x<img.cols;x++)
		{
			vertex[y][x].ani=-1;
	 		vertex[y][x].f=numeric_limits<float>::max();
	 		vertex[y][x].g=numeric_limits<float>::max();
		}
	//initialise vertex at start with g=0
	vertex[start.y][start.x].g=0;
	
	for(y=0;y<500000;y++)
	{
	//find vertex(neighbour) with minimum distance from source whose neighbours are not initialized 
	 index=fvwgwnani(index.x,index.y);
	 //cout<<index;
	 if(vertex[index.y][index.x].ani==1)
		 index=backup_plan(index);
	//make ani of vertex found true as we are gonna initialize its neighbours
	 vertex[index.y][index.x].ani=1;
	 if(index==End)
	  {/*cout<<"yayy";*/break;}
	//initialization of neighbours of vertex found
	
	 for(int x1=index.x-1;x1<=index.x+1;x1++)
	 for(int y1=index.y-1;y1<=index.y+1;y1++)
	 {
	  if(x1>0&&y1>0&&x1<img.cols&&y1<img.rows)
	  {
	  	dist=sqrt((x1-index.x)*(x1-index.x)+(y1-index.y)*(y1-index.y));
	  if(vertex[y1][x1].ani!=1&&vertex[y1][x1].g>(vertex[index.y][index.x].g + dist)&&(img.at<Vec3b>(y1,x1)[0]<100||img.at<Vec3b>(y1,x1)[1]<100||img.at<Vec3b>(y1,x1)[2]<100))
	   {
		vertex[y1][x1].g=vertex[index.y][index.x].g+dist;
	   }
	  }
     }

	 for(int x1=index.x-1;x1<=index.x+1;x1++)
	 for(int y1=index.y-1;y1<=index.y+1;y1++)
	 {
	  if(x1>0&&y1>0&&x1<img.cols&&y1<img.rows){
	  if(vertex[y1][x1].ani!=1&&vertex[y1][x1].f>(vertex[y1][x1].g + sqrt((x1-End.x)*(x1-End.x)+(y1-End.y)*(y1-End.y)))&&(img.at<Vec3b>(y1,x1)[0]<100||img.at<Vec3b>(y1,x1)[1]<100||img.at<Vec3b>(y1,x1)[2]<100))
	   {
		vertex[y1][x1].f=vertex[y1][x1].g + sqrt((x1-End.x)*(x1-End.x)+(y1-End.y)*(y1-End.y));
		vertex[y1][x1].prev=index;
		//if(vertex[y1][x1].ani!=1)
		/*if(index==start)
			cout<<x1<<","<<y1<<" "<<vertex[y1][x1].f;*/
		vertex[y1][x1].ani=0;
	   }}
	 }
	}
	
	cout<< y;
	if(index==End) while(index!=start)
		{
		 temp=vertex[index.y][index.x].prev;
		 vertex[temp.y][temp.x].next=index;
		 index=temp;

		 //cout<<index<<"no::";y--;
		}
}

int main()
{
	img=imread("path2.jpg");

	vertex=new Vertex*[img.rows];
	for(int i=0;i<img.rows;i++)
	vertex[i]=new Vertex[img.cols];

	start=find_start();
	End  =find_End();

	astar();

	/*VideoWriter oVideoWriter("pathplanner.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 
                                                               60, Size(img.cols,img.rows), true);

 	if (oVideoWriter.isOpened() == false) 
    {
        cout << "Cannot save the video to a file" << endl;
        cin.get(); //wait for any key press
        return -1;
    }*/

	namedWindow("Hello",WINDOW_NORMAL);
	Point header=start,prev=Point(-1,-1);
	//cout<<header;
	while(header!=End)
	{
	 if(prev.x>0&&prev.y>0)
	 {
 	 line(img,header,prev,Scalar(255,100,100),2,CV_AA,0);
       	 imshow("Hello",img);
       	 //oVideoWriter.write(img); 
	 }
	 if(waitKey(10)==27)
		{
			cout<<"Esc key is pressed by user. Stopping the video"<<endl;
			break;
		}
	 prev=header;
	 header=vertex[header.y][header.x].next; 
	}
	
/*	for(int y=0;y<img.rows;y++)
	for(int x=0;x<img.cols;x++)
	{		if(vertex[y][x].ani==1)
			img.at<Vec3b>(y,x)=Vec3b(255,100,100);
	}
	imshow("Hello",img);*/
	//cout<<endl<<COUNT;
	waitKey(0);
	return 0;
}

