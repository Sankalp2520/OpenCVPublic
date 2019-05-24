#ifndef MY_FX_H
#define MY_FX_H

Mat img_transform(Mat,Point,float,float,int,int,float,float,float);
/*
1. ptt=point to translate ,
2. scale=scaling factor for x direction,
3. scale_x=scaling factor for x direction,
4. scale_y=scaling factor for y direction,
5. reflect_x=0 to not reflect about x axis 1 to reflect,
6. reflect_y=0 to not reflect about y axis 1 to reflect,
7. atr= angle to rotate anticlockwise in degrees, 
8. sa_x= shear angle from x axis clockwise in degrees,
9. sa_y=shear angle from y axis clockwise in degrees
*/

#endif
