#include<iostream>
#include<opencv2/opencv.hpp>
#include<math.h>	//for sqrt and atan
#include<vector>
#include<float.h> 	//for FLT_MAX
using namespace std;
using namespace cv;

Mat img,canny,lanes;
vector<Mat> rgbChannels(3);

class Vertex{
public:
	bool flag;

}**vertex;

class Curve{
public: 
	vector<Point> points; 
	int max;
	float linearity;
	Curve()
	{
		max=0;
	}
};

Curve findSpan(int x,int y)
{
	int i,j;
	int u=x,v=y;
	Curve curve=Curve();
	int dist;
	float mean=0,variance=0,temp;
	std::vector<float> angle;
	bool flag=0;

	while(true)
	{
		flag=0;
		vertex[v][u].flag=1;

		curve.points.push_back(Point(u,v));

		for(i=u-4;i<=u+4;i++)
			for(j=v-4;j<=v+4;j++)
			{
				if(j>0&&i>0&&j<canny.rows&&i<canny.cols)
				if(canny.at<uchar>(j,i)==255&&vertex[j][i].flag!=1)
					{
						u=i;v=j;
						flag=1;
					}
			}
		if(flag==0)
			break;

			dist=sqrt((v-y)*(v-y)+(u-x)*(u-x));
			if(curve.max<dist)
				curve.max=dist;

			if(u!=x)
			temp=atan((v-y)/(u-x))*180/3.1415;
			else
				temp=90;
			angle.push_back(temp);
			mean+=temp;

	}

	mean=mean/angle.size();
	for(i=0;i<angle.size();i++)
		variance+=(mean-angle[i])*(mean-angle[i]);
	variance=variance/angle.size();

	curve.linearity=variance;

	return curve;

}

bool isLane(Curve curve)
{
	if(curve.max>70&&curve.linearity<10)
		return true;
	return false;
}

void addLane(Curve curve)
{
	for(int i=0;i<curve.points.size();i++)
		lanes.at<uchar>((curve.points)[i])=255;

}

void detect_lane()
{
	//uchar color;
	Curve curve;
	bool lane;

	for(int x=0;x<canny.cols;x++)
	{
		for(int y=canny.rows/2;y<canny.rows;y++)
		{
			if(canny.at<uchar>(y,x)==255&&vertex[y][x].flag!=1)
				{
					curve=findSpan(x,y);

					lane=isLane(curve);

					if(lane)
						addLane(curve);
				}

		}
	}
}

/*void remove()
{

	for(int x=0;x<img.cols;x++)
	{
		for(int y=0;y<img.rows;y++)
		if(rgbChannels[0].at<uchar>(y,x)>23&&rgbChannels[0].at<uchar>(y,x)<130&&rgbChannels[1].at<uchar>(y,x)<40&&rgbChannels[1].at<uchar>(y,x)>-1&&rgbChannels[2].at<uchar>(y,x)<256&&rgbChannels[2].at<uchar>(y,x)>190)
			lanes.at<uchar>(y,x)=255;
	}
}*/

int main()
{	
	//img=imread("/home/sankalp/Desktop/opencv/lane.jpg");

	VideoCapture cap("/home/sankalp/Desktop/opencv/grass.mp4");

	if(cap.isOpened()==false)
	{
		cout<<"Cannot find or load challenge.mp4";
		cin.get();
		return -1;
	}

	namedWindow("original",WINDOW_NORMAL);
	//namedWindow("canny",WINDOW_NORMAL);
	//namedWindow("lanes",WINDOW_NORMAL);
	// namedWindow("red",WINDOW_NORMAL);
	// namedWindow("blue",WINDOW_NORMAL);
	// namedWindow("green",WINDOW_NORMAL);

	namedWindow("Control",WINDOW_NORMAL);
	namedWindow("hue",WINDOW_NORMAL);
	namedWindow("saturation",WINDOW_NORMAL);
	namedWindow("value",WINDOW_NORMAL);

	vertex= new Vertex*[(int)cap.get(CAP_PROP_FRAME_HEIGHT)];

	for(int i=0;i<(int)cap.get(CAP_PROP_FRAME_HEIGHT);i++)
	{
		vertex[i]=new Vertex[(int)cap.get(CAP_PROP_FRAME_WIDTH)];
	}


 /* int iLowH = 0;
 int iHighH = 130;

  int iLowS = 0; 
 int iHighS = 40;

  int iLowV = 222;
 int iHighV = 255;*/
 int iLowH = 0;
 int iHighH = 48;

  int iLowS = 0; 
 int iHighS = 96;

  int iLowV = 138;
 int iHighV = 255;

  //Create trackbars in "Control" window
 cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
 cvCreateTrackbar("HighH", "Control", &iHighH, 179);

  cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
 cvCreateTrackbar("HighS", "Control", &iHighS, 255);

  cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
 cvCreateTrackbar("HighV", "Control", &iHighV, 255);


while(true)
{
	bool bSuccess=cap.read(img);
		
		if(bSuccess==false)
		{
			cout<<"Found the end of the video"<<endl;
			break;
		}

	cvtColor(img,img,COLOR_BGR2HSV);
	split(img,rgbChannels);

	for(int x=0;x<img.cols;x++)
		for(int y=0;y<img.rows;y++)
			vertex[y][x].flag=0;	

	lanes=Mat::zeros(img.rows,img.cols,CV_8U);	

	//inRange(img, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), lanes);
	//erode(lanes,lanes, getStructuringElement(MORPH_ELLIPSE, Size(2,2)));
	//dilate(lanes,lanes, getStructuringElement(MORPH_ELLIPSE, Size(5,5)));
	//Canny(lanes,canny,0,0);
	//Canny(img,canny,385,400);
	//lanes.copyTo(canny);
	//lanes=Mat::zeros(img.rows,img.cols,CV_8U);
	//detect_lane();

	imshow("original",img);
	//imshow("canny",canny);
	//imshow("lanes",lanes);

	//imshow("blue",rgbChannels[0]);
	//imshow("canny",rgbChannels[1]);
	//imshow("red",rgbChannels[2]);
	imshow("hue",rgbChannels[0]);
	imshow("saturation",rgbChannels[1]);
	imshow("value",rgbChannels[2]);

	if(waitKey(300)==27)
	{
		cout<<"Esc key is pressed by user. Stopping the video"<<endl;
		break;
	}
}	

	return 0;
}