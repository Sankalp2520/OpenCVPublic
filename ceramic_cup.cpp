#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc,char** argv)
{
	Mat image=imread("/home/sankalp/Desktop/Blender/Images/cup1.png");

	if(image.empty())
	{
		cout<<"\n Couldn't find or open the image.\n";
		cin.get();
		return -1;
	}

	String windowname="GIFT";

	namedWindow(windowname,WINDOW_NORMAL);

	imshow(windowname,image);

	waitKey(0);

	destroyWindow(windowname);

	return 0;

}
	
	

	
