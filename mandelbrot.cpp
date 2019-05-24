#include<iostream>
#include<opencv2/opencv.hpp>
#include<complex>
#include<math.h>

using namespace std;
using namespace cv;

#define max_itr 500
#define x1 -2.1f
#define x2 0.6f
#define y1 -1.2f
#define y2 1.2f

typedef uchar Pixel;

Mat Mandelbrot;
float scalex,scaley;

//escape-time algorithm
int escTime(float x,float y) 
{
	complex<float> c(x,y),z(0,0);
	for(int i=0;i<max_itr;i++)
	{
		if(abs(z)>2)	return i;
		z=z*z+c;
	}
	return max_itr;
}

//function to find pixel value at each point depending upon convergence of z=z^2+c
uchar mandelbrotFormula(float x0,float y0)
{
	int itr=escTime(x0,y0);
	if(itr==max_itr)
		return 0;
	return cvRound(sqrt(itr/(float)max_itr)*255);
}

//sequential mandelbrot implementation
void sequentialMandelbrot()
{
/*	float x0,y0;

	for (int x = 0; x < Mandelbrot.cols; ++x)
		for (int y = 0; y < Mandelbrot.rows; ++y)
		{
			x0=x/scalex+x1;
			y0=y/scaley+y1;
			//uchar value=(uchar)mandelbrotFormula(x0,y0);
			//cout<<value<<" ";
			Mandelbrot.ptr<uchar>(y)[x] = (uchar)mandelbrotFormula(x0,y0);
		}
*/
		Mandelbrot.forEach<Pixel>([](Pixel &p, const int * position) -> void {
				float x0,y0;
				x0=position[1]/scalex+x1;
				y0=position[0]/scaley+y1;

    			p=(uchar)mandelbrotFormula(x0,y0);
			
			});	

}

//parallel mandelbrot implementation
class ParallelMandelbrot: public ParallelLoopBody
{
	public:
		virtual void operator ()(const Range& range) const /*CV_OVERRIDE*/
		{
			int x,y;
			float x0,y0;
			for(int r=range.start;r<range.end;r++)
			{
				y=r/Mandelbrot.cols;  //this will give row number
				x=r%Mandelbrot.cols;	//this will give column number

				x0=x/scalex+x1;
				y0=y/scaley+y1;

				Mandelbrot.ptr<uchar>(y)[x] = (uchar)mandelbrotFormula(x0,y0);	
			}

		/*	Mandelbrot.forEach<Pixel>([](Pixel &p, const int * position) -> void {
				float x0,y0;
				x0=position[1]/scalex+x1;
				y0=position[0]/scaley+y1;

    			p=(uchar)mandelbrotFormula(x0,y0);
			
			});	*/
		}

		ParallelMandelbrot& operator=(const ParallelMandelbrot &){
			return *this;
		};
};


int main()
{
	Mandelbrot=Mat::zeros(4800, 5400,CV_8U);

	scalex=Mandelbrot.cols/(x2-x1);
	scaley=Mandelbrot.rows/(y2-y1);

	//call to sequentialMandelbrot
	sequentialMandelbrot();


	//call to ParallelMandelbrot
	/*ParallelMandelbrot parallelMandelbrot;
	parallel_for_(Range(0,Mandelbrot.cols*Mandelbrot.rows),parallelMandelbrot);
*/
	namedWindow("Mandelbrot",WINDOW_NORMAL);
	imshow("Mandelbrot",Mandelbrot);
	waitKey(0);
	return 0;
}