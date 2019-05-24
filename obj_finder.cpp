#include<iostream>
#include<opencv2/opencv.hpp>
#include<math.h>
typedef uchar Pixel;

using namespace std;
using namespace cv;

Mat img,Template,result,filtered;

int correlateAt(int x,int y)
{
	long int l=0;
	for(int x1=0;x1<Template.cols;x1++)
		for(int y1=0;y1<Template.rows;y1++)
		{
			if(y-Template.rows/2+y1>0&&x-Template.cols/2+x1>0&&y-Template.rows/2+y1<img.rows&&x-Template.cols/2+x1<img.rows)
			l+=((img.at<uchar>(y-Template.rows/2+y1,x-Template.cols/2+x1)-127)*(Template.at<uchar>(y1,x1))-127);
		}
		//cout<<x<<","<<y<<"="<<l/(255*70*61)<<"|";
		if(l<0)l=0;
		return (l/(127*70*61));
}

void gradient()
{
	for(int x=1;x<result.cols-1;x++)
		for(int y=1;y<result.rows-1;y++)
		{
			filtered.at<uchar>(y,x) =5*
		sqrt((result.at<uchar>(y,x+1)-result.at<uchar>(y,x-1))*(result.at<uchar>(y,x+1)-result.at<uchar>(y,x-1))+(result.at<uchar>(y+1,x)-result.at<uchar>(y-1,x))*(result.at<uchar>(y+1,x)-result.at<uchar>(y-1,x)));
		//cout<<filtered.at<uchar>(y,x)<<"|";		
	}
}

void findTemplate()
{
	result.forEach<Pixel>([](Pixel &p, const int * position) -> void {
    p=correlateAt(position[1],position[0]);
		/*cout<<position[0]<<" "<<position[1]<<"=";
		p=1;*/
		//cout<<(int)p<<"@";
});	
}

int main()
{
	img=imread("dense.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	Template=imread("thunder",CV_LOAD_IMAGE_GRAYSCALE);

	result=Mat::zeros(img.rows,img.cols,CV_8U);
    filtered=Mat::zeros(img.rows,img.cols,CV_8U);
	findTemplate();
	gradient();
	namedWindow("original",WINDOW_NORMAL);
	namedWindow("result",WINDOW_NORMAL);
	namedWindow("filtered",WINDOW_NORMAL);

	imshow("original",img);
    imshow("result",result);
    imshow("filtered",filtered);
    
    waitKey(0);

    return 0;
}