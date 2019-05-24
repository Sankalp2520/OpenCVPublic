#include<opencv2/opencv.hpp>

#include<iostream>

#include<time.h>

#include<unistd.h>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{

	VideoCapture cap("/home/sankalp/Desktop/Blender/movies/water/24fps.avi");

	if(cap.isOpened()==false)
	{
		cout<<"Cannot find or load 24fps.avi";
		cin.get();
		return -1;
	}
	
	double fps=cap.get(CAP_PROP_FPS);
	cout<<"Frames per sseconds :"<<fps<<endl;

	String wname="First_video";

	namedWindow(wname,WINDOW_NORMAL);

	clock_t start=0,end=0;

	while(true)
	{
		Mat frame;
		bool bSuccess=cap.read(frame);
		
		if(bSuccess==false)
		{
			cout<<"Found the end of the video"<<endl;
			break;
		}
		end=clock();
		cout<<end<<" "<<start<<" "<<CLOCKS_PER_SEC<<41667-((double)(end-start)/CLOCKS_PER_SEC)<<endl;
		usleep(25000);	
		//usleep(41667-((float)(end-start)/CLOCKS_PER_SEC));
		imshow(wname,frame);
		start=clock();
		
		if(waitKey(10)==27)
		{
			cout<<"Esc key is pressed by user. Stopping the video"<<endl;
			break;
		}
	}
	destroyWindow(wname);
	return 0;
}
