#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat img=imread("/home/sankalp/Desktop/Blender/Images/cube.png");
	if(img.empty())
	{
	cout<< "could not open or find the image"<<endl;
	cin.get();
	return -1;
	}

	if(imwrite("/home/sankalp/Desktop/opencv/cube.jpg",img)==false)
	{
	cout<<"Failed to save the image."<<endl;
	cin.get();
	return -1;
	}

	cout<<"Image is successfully saved to opencv directory."<<endl;

	namedWindow("saved_image",WINDOW_NORMAL);
	waitKey(1000);
	Mat imgs=imread("/home/sankalp/Desktop/opencv/cube.jpg");
	imshow("saved_image",imgs);
	waitKey(0);
	destroyWindow("saved_image");

	return 0;
}
