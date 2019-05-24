#include<math.h>
#include<opencv2/opencv.hpp>
#include"sankalp.hpp"
using namespace cv;
Mat img_transform(Mat img,Point ptt=Point(0,0),float scale_x=1,float scale_y=1,int reflect_x=0,int reflect_y=0,float atr=0,float sa_x=0,float sa_y=0)
/*
1. ptt=point to translate ,
2. scale_x=scaling factor for x direction,
3. scale_y=scaling factor for y direction,
4. reflect_x=0 to not reflect about x axis 1 to reflect,
5. reflect_y=0 to not reflect about y axis 1 to reflect,
6. atr= angle to rotate anticlockwise in degrees, 
7. sa_x= shear angle from x axis clockwise in degrees,
8. sa_y=shear angle from y axis clockwise in degrees
*/
{
	Mat res(img.rows,img.cols,CV_8UC3);
	Mat vec(3,1,CV_32F),res_vec(3,1,CV_32F);
	float m[3][3]={
{pow(-1,reflect_y)*scale_x*(cos(-3.14*atr/180)),scale_x*(sin(-3.14*atr/180)-tan(-3.14*sa_x/180)),-1*ptt.x}
,{scale_y*(-1*sin(-3.14*atr/180)-tan(-3.14*sa_y/180)),pow(-1,reflect_x)*scale_y*(cos(-3.14*atr/180)),-1*ptt.y}
,{0,0,1}
},a;

	Mat affineMat(3,3,CV_32F,m);
	for(int y=0;y<img.rows;y++)
	for(int x=0;x<img.cols;x++)
	{
	//vec=(Mat_<float>(3,1)<<x,y,1);
	a=cos(x);	
	//res_vec=affineMat*vec; 
		
	//if(((float*)res_vec.data)[1]>0&&((float*)res_vec.data)[0]>0&&((float*)res_vec.data)[1]<img.rows&&((float*)res_vec.data)[0]<img.cols)
	//	res.at<Vec3b>(y,x)=img.at<Vec3b>(((float*)res_vec.data)[1],((float*)res_vec.data)[0]);
	}

return img;
}

