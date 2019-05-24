#include<opencv2/opencv.hpp>
#include"sankalp.cpp"
#include<iostream>
using namespace std;
using namespace cv;

VideoCapture cap("/home/sankalp/Desktop/Blender/movies/water/24fps.avi");
class thread: public ParallelLoopBody
{
public:
virtual void operator()(const Range& r)
const
{
	String wname="Original";

	namedWindow(wname,WINDOW_NORMAL);

	while(true)
	{
		Mat frame;
		bool bSuccess=cap.read(frame);
		
		if(bSuccess==false)
		{
			cout<<"Found the end of the video"<<endl;
			break;
		}
		imshow(wname,frame);
		
		if(waitKey(10)==27)
		{
			cout<<"Esc key is pressed by user. Stopping the video"<<endl;
			break;
		}
	}
	destroyWindow(wname);
}
};

int main(int argc, char** argv)
{

	if(cap.isOpened()==false)
	{
		cout<<"Cannot find or load 24fps.avi";
		cin.get();
		return -1;
	}
	
	double fps=cap.get(CAP_PROP_FPS);
	cout<<"Frames per sseconds :"<<fps<<endl;

	thread t_instance;
	parallel_for_(Range(0,0), t_instance);

	String wname="First_video";

	namedWindow(wname,WINDOW_NORMAL);
	//namedWindow("wname",WINDOW_NORMAL);
	while(true)
	{
		Mat frame,trans;
		bool bSuccess=cap.read(frame);
		
		if(bSuccess==false)
		{
			cout<<"Found the end of the video"<<endl;
			break;
		}
		
		trans=img_transform(frame,Point(0,-frame.rows),1,1,1,0,0,0,0);	
		imshow(wname,trans);
		//imshow("wname",frame);
		
		if(waitKey(10)==27)
		{
			cout<<"Esc key is pressed by user. Stopping the video"<<endl;
			break;
		}
	}
	destroyWindow(wname);
	return 0;
}
