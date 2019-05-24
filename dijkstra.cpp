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
		float mdfs;
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
	/*imshow("red",bw);
	waitKey(0);
	destroyWindow("red");*/
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
	/*imshow("green",bw);
	waitKey(0);
	destroyWindow("green");*/
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

Point fvwmdfswnani(int x0,int y0)
{
	int min=INT_MAX;
	Point index;
	bool flag=0;
	for(int x=x0-1;x<=x0+1;x++)
	for(int y=y0-1;y<=y0+1;y++)
	{
		if(x>0&&y>0&&x<img.cols&&y<img.rows){
		if((vertex[y][x].ani==-1||vertex[y][x].ani==0)&&vertex[y][x].mdfs<min&&(img.at<Vec3b>(y,x)[0]<100||img.at<Vec3b>(y,x)[1]<100||img.at<Vec3b>(y,x)[2]<100))
		{
			min=vertex[y][x].mdfs;
			index=Point(x,y);
			flag=1;
		}}
	}
	if(flag==0)
		return Point(x0,y0);
	return index;
}

void dijkstra()
{
	long int y;
	int x;
	float dist;
	Point index=start;//,temp;
	//initialise all vertices with ani=false & mdfs=INT_MAX 
	for(y=0;y<img.rows;y++)
	for(x=0;x<img.cols;x++)
	{
	 vertex[y][x].ani=-1;
	 vertex[y][x].mdfs=INT_MAX;
	}
	//initialise vertex at start with mdfs=0
	vertex[start.y][start.x].mdfs=0;
	
	for(y=0;y<500000;y++)
	{
	//find vertex(neighbour) with minimum distance from source whose neighbours are not initialized 
	 index=fvwmdfswnani(index.x,index.y);
	 //cout<<index;
	 if(vertex[index.y][index.x].ani==1)
		 index=backup_plan(index);
	//make ani of vertex found true as we are gonna initialize its neighbours
	 //cout<<vertex[index.y][index.x].ani;
	 vertex[index.y][index.x].ani=1;
	 if(index==End)
	  {/*cout<<"yayy";*/break;}
	//initialization of neighbours of vertex found
	 for(int x1=index.x-1;x1<=index.x+1;x1++)
	 for(int y1=index.y-1;y1<=index.y+1;y1++)
	 {
	  if(x1>0&&y1>0&&x1<img.cols&&y1<img.rows){
	  	dist=sqrt((x1-index.x)*(x1-index.x)+(y1-index.y)*(y1-index.y));
	  if(vertex[y1][x1].ani!=1&&vertex[y1][x1].mdfs>(vertex[index.y][index.x].mdfs+dist)&&(img.at<Vec3b>(y1,x1)[0]<100||img.at<Vec3b>(y1,x1)[1]<100||img.at<Vec3b>(y1,x1)[2]<100))
	   {
		vertex[y1][x1].mdfs=vertex[index.y][index.x].mdfs+dist;
		vertex[y1][x1].prev=index;
		//if(vertex[y1][x1].ani!=1)
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
	img=imread("q12.png");
	int k=0;
	vertex=new Vertex*[img.rows];
	for(int i=0;i<img.rows;i++)
	vertex[i]=new Vertex[img.cols];

	start=find_start();
	End  =find_End();
	cout<<start<<":::"<<End;
	dijkstra();

	/*VideoWriter oVideoWriter("pathplanner.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 
                                                               60, Size(img.cols,img.rows), true);

 	if (oVideoWriter.isOpened() == false) 
    {
        cout << "Cannot save the video to a file" << endl;
        cin.get(); //wait for any key press
        return -1;
    }*/

	namedWindow("Hello",WINDOW_NORMAL);
	/*Point header=start,prev=Point(-1,-1);
	//cout<<header;
	while(header!=End)
	{
	 if(prev.x>0&&prev.y>0)
	 {
 	 line(img,header,prev,Scalar(255,100,100),0,CV_AA,0);
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
	}*/
	
	for(int y=0;y<img.rows;y++)
	for(int x=0;x<img.cols;x++)
	{
		if(vertex[y][x].ani==1)
		{
			img.at<Vec3b>(y,x)=Vec3b(255,100,100);
			
			//if(k%10==0)
			//{
				imshow("Hello",img);
			waitKey(1);k++;
			//}
		}
	}
	imshow("Hello",img);
	//cout<<endl<<COUNT;
	waitKey(0);
	return 0;
}

