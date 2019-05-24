#include<opencv2/opencv.hpp>
#include<iostream>
#include<math.h>
using namespace cv;
using namespace std;
int main()
{
	Mat img=imread("/home/sankalp/Desktop/Blender/Images/cube1.png");
	int h=img.rows,w=img.cols;
	Mat bwimg(h,w,CV_8U),bwimg3(h,w,CV_8U);
	Mat bwimg2,hist_equalized_img(h,w,CV_8U);
	cvtColor(img,bwimg2,COLOR_BGR2GRAY);

	Vec3b color;

	for(int i=0;i<h;i++)
	{
	for(int j=0;j<w;j++)
	{
		color=img.at<Vec3b>(i,j);
		bwimg.at<uchar>(i,j)=color.val[0]|color.val[1]|color.val[2];
		bwimg3.at<uchar>//(i,j)=9*color.val[0]*color.val[1]/255*color.val[2]/255; //faulty because values may cross 255 and will be 0 if any one comp. is 0
	//(i,j)=pow(color.val[0]*color.val[1]*color.val[2],(float)1/3); //faulty when any one component becomes 0
	//(i,j)=(color.val[0]+color.val[1]+color.val[2])/3;//no fault but less bright color
	(i,j)=.114*color.val[0]+.587*color.val[1]+.299*color.val[2];


		//cout<<color.val[0]<<" "<<color.val[1]<<" "<<color.val[2]<<" "bwimg.at<uchar>(i,j)<<endl;
	}
	}

	equalizeHist(bwimg3,hist_equalized_img);

	namedWindow("original_image",WINDOW_NORMAL);
	namedWindow("B&W image2",WINDOW_NORMAL);
	namedWindow("B&W image3",WINDOW_NORMAL);
	namedWindow("Histogramequalized ",WINDOW_NORMAL);
	//namedWindow("B&W image",WINDOW_NORMAL);
	imshow("original_image",img);
	//imshow("B&W image",bwimg);
	imshow("B&W image2",bwimg2);
	imshow("B&W image3",bwimg3);
	imshow("Histogramequalized",hist_equalized_img);

	waitKey(0);

	destroyWindow("original_image");
	//destroyWindow("B&W image");
	destroyWindow("B&W image2");
	destroyWindow("B&W image3");
	destroyWindow("Histogramequalized");
	return 0;
}
