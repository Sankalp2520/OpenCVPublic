#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc,char** argv)
{

	VideoCapture cam(0);

	if(cam.isOpened()==false);
	{
		cout<<"Unable to find WebCam";
	}

	cout<<"\nCamera Width"<<cam.get(CAP_PROP_FRAME_WIDTH)<<" Camera Height"<<cam.get(CAP_PROP_FRAME_HEIGHT)<<endl;
	
	String wname="WEB_CAM";
	namedWindow(wname,WINDOW_AUTOSIZE);	
	
	while(true)
	{
		Mat frame;
		bool Success=cam.read(frame);

		if(Success==false)
		{
			cout<<"failed to read frames from webcam";
			return -1;
		}	
		imshow(wname,frame);

		if(waitKey(10)==27)
		{
			cout<<"Esc pressed. Quit.";
			return 0;
		}
	}
		destroyWindow(wname);
		return 0;
}
