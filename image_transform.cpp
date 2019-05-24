#include<iostream>
#include<opencv2/opencv.hpp>
#include<math.h>
using namespace std;
using namespace cv;
typedef Vec3b Pixel;

Mat img_transform(Mat img,Point ptt=Point(0,0),float scale_x=1,float scale_y=1,int reflect_x=0,int reflect_y=0,float atr=0,float sa_x=0,float sa_y=0)
/*
ptt=point to translate ,
scale=scaling factor for x direction,
scale_x=scaling factor for x direction,
scale_y=scaling factor for y direction,
reflect_x=0 to not reflect about x axis 1 to reflect,
reflect_y=0 to not reflect about y axis 1 to reflect,
atr= angle to rotate anticlockwise in degrees, 
sa_x= shear angle from x axis clockwise in degrees,
sa_y=shear angle from y axis clockwise in degrees
*/
{
	Mat res(img.rows,img.cols,CV_8UC3);
	Mat vec(3,1,CV_32F),res_vec(3,1,CV_32F);//,prev_res_vec=(Mat_<float>(3,1)<<0,0,0);;
//	float m[3][3]={{1,0,0},{0,-1,img.rows},{0,0,1}};//for reflection about x axis
//	float m[3][3]={{1,0,100},{0,1,100},{0,0,1}};//for translation 
//	float m[3][3]={{3,0,-img.cols/2},{0,3,-img.rows/2},{0,0,1}};//for scaling
	float m[3][3]={{pow(-1,reflect_y)*scale_x*(cos(-3.14*atr/180)),scale_x*(sin(-3.14*atr/180)-tan(-3.14*sa_x/180)),-1*ptt.x},{scale_y*(-1*sin(-3.14*atr/180)-tan(-3.14*sa_y/180)),pow(-1,reflect_x)*scale_y*(cos(-3.14*atr/180)),-1*ptt.y},{0,0,1}};//for scaling

	Mat affineMat(3,3,CV_32F,m);
	for(int y=0;y<img.rows;y++)
	for(int x=0;x<img.cols;x++)
	{
	vec=(Mat_<float>(3,1)<<x,y,1);
		
	res_vec=affineMat*vec; 
		
	if(((float*)res_vec.data)[1]>0&&((float*)res_vec.data)[0]>0&&((float*)res_vec.data)[1]<img.rows&&((float*)res_vec.data)[0]<img.cols)
		res.at<Vec3b>(y,x)=img.at<Vec3b>(((float*)res_vec.data)[1],((float*)res_vec.data)[0]);
	}

	/*res.forEach<Pixel>([&](Pixel &p, const int * position) -> void {
				
	vec=(Mat_<float>(3,1)<<position[1],position[0],1);
	res_vec=affineMat*vec; 
		
	if(((float*)res_vec.data)[1]>0&&((float*)res_vec.data)[0]>0&&((float*)res_vec.data)[1]<img.rows&&((float*)res_vec.data)[0]<img.cols)
		p=img.at<Vec3b>(((float*)res_vec.data)[1],((float*)res_vec.data)[0]);
			
			});*/	

return res;
}
		
	
int main()
{
	Mat img=imread("/home/sankalp/Desktop/Blender/movies/multicolor balls/0019.png");
	
	namedWindow("1",WINDOW_NORMAL);
	namedWindow("2",WINDOW_NORMAL);

	Mat x_reflected=img_transform(img,Point(0,-img.rows),1,1,1,0,0,0,0);

	imshow("1",img);imshow("2",x_reflected);
	waitKey(0);
 return 0;
}
