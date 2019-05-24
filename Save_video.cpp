#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main()
{
	VideoCapture cam(0);

	if(cam.isOpened()==false)
	{
		cout<<"Unable to open web_cam.";
		cin.get();
		return -1;
	}

	Size frame_size(cam.get(CAP_PROP_FRAME_WIDTH),cam.get(CAP_PROP_FRAME_HEIGHT));

	int fps=24;

	VideoWriter vw("/home/sankalp/Desktop/opencv/web_cam.avi",VideoWriter::fourcc('M','J','P','G'),fps,frame_size,true);

	if(vw.isOpened()==false)
	{
	cout<<"Unable to open the video writer. Cannot save the video to opencv directory."<<endl;
	cin.get();
	return -1;
	}

	string wname = "Camera feed";
	namedWindow(wname,WINDOW_NORMAL);

	while(true)
	{
	Mat frame;
	bool success=cam.read(frame);

	if(success==false)
	{
		cout<<"Web cam disconnected."<<endl;
		cin.get();
		break;
	}
	vw.write(frame);
	imshow(wname,frame);

	if(waitKey(10)==27)
	{
		cout<<"Esc is pressed by the user. Stopping the video."<<endl;
		break;
	}
	}
	vw.release();
	destroyWindow(wname);
	return 0;
}
