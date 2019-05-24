#include<opencv2/opencv.hpp>
// #include <opencv2/imgproc/imgproc.hpp>
// #include <opencv2/objdetect/objdetect.hpp>
// #include <opencv2/highgui/highgui.hpp>
#include<iostream>
//#define CV_AA 16
using namespace std;
using namespace cv;
//int mouse_x,mouse_y,x_prev,y_prev;
Point mouse[4];
void mouse_callback(int  event, int  x, int  y, int  flag, void *param)
{
    if (event == EVENT_MOUSEMOVE) {
	//x_prev=(x_prev==-1)?x:mouse_x;
	//y_prev=(y_prev==-1)?y:mouse_y;     
	//x_prev=mouse_x;y_prev=mouse_y; 
	//mouse_x=x;mouse_y=y;
	mouse[0]=mouse[1];
	mouse[1]=mouse[2];
	mouse[2]=mouse[3];
	//mouse[3]=mouse[4];
	mouse[3]=Point(x,y);
	
    }
}

int main(int argc, char** argv)
{
	Mat image(600,800,CV_8UC3,Scalar(250,40,40));

	String windowname="Blank image";

	namedWindow(windowname);

	setMouseCallback(windowname,mouse_callback);

	imshow(windowname,image);

	int esc=27;//to read the value of esc key

	char ch=waitKey(0);
	//Vec3b color;

	while(ch!=esc)
	{
		if(ch=='k')
		{//image.at<Vec3b>(Point(mouse_x,mouse_y))=Vec3b(255,255,255);

	//line(image,mouse[4],mouse[3],Scalar(255,255,255),1,CV_AA,0);
	line(image,mouse[3],mouse[2],Scalar(255,255,255),1,CV_AA,0);
		line(image,mouse[2],mouse[1],Scalar(255,255,255),1,CV_AA,0);	
		line(image,mouse[1],mouse[0],Scalar(255,255,255),1,CV_AA,0);	
		imshow(windowname,image);
		}
		ch=waitKey(10);
	}
	

	destroyWindow(windowname);

	return 0;
}
