#include <vector>
#include <opencv2/opencv.hpp>
#include <math.h>
#include <thread>
#include "physics.hpp"

using namespace cv;

/*particle class definitions*/
template <typename T>
particle<T>::particle(String n, Vec2f r1, Vec2f p1, T c, int S)
{
	name = n;
	r = r1;
	p = p1;
	color = c;
	size = S;
}
template <typename T>
String particle<T>::getName()
{
	return name;
}
template <typename T>
void particle<T>::setColor(T c)
{
	color = c;
}

/*template <typename T>
	T paticle<T>::getColor()
	{
		return color;
	}
*/
template <typename T>
int particle<T>::getSize()
{
	return size;
}

template <typename T>
void particle<T>::putTo(sandbox box)
{
	circle(box, Point(r[0], r[1]), size, Scalar(color), -1, CV_AA, 0);
}

template <typename T>
void particle<T>::removeFrom(sandbox box)
{
	circle(box, Point(r[0], r[1]), size + 1, Scalar(0, 0, 0), -1, CV_AA, 0);
}

/*forceField class definitions*/
template <typename T>
forceField<T>::forceField(String n, int R[4], void (*f)(int, vector<particle<T>> *, int *))
{
	name = n;
	Range = R;
	definition = f;
}

template <typename T>
String forceField<T>::getName()
{
	return name;
}

template <typename T>
void forceField<T>::addDefinition(void (*f)(int, vector<particle<T>> *, int *))
{
	definition = f;
}

template <typename T>
void forceField<T>::addRange(int R[4])
{
	Range = R;
}

template <typename T>
int *forceField<T>::getRange()
{
	return Range;
}
/*
	void (*)(Vec2f&) getDefinition()
	{
		return definition;
	}*/

template <typename T>
void forceField<T>::applyOn(int i, vector<particle<T>> *obj)
{
	(*definition)(i, obj, Range);
}

/*World class definitions*/
template <typename T>
World<T>::World(String n, int r, int c, int flags, int now)
{
	name = n;
	rows = r;
	cols = c;
	status = -1;
	natureOfWalls = now;
	path = Mat::zeros(rows, cols, CV_8U);
	switch (flags)
	{
	case RGB:
		mysandbox = Mat::zeros(rows, cols, CV_8UC3);
		break;
	case BW:
	default:
		mysandbox = Mat::zeros(rows, cols, CV_8U);
	}
}

template <typename T>
String World<T>::getName()
{
	return name;
}

template <typename T>
void World<T>::addObject(particle<T> p1)
{
	obj.push_back(p1);
}

template <typename T>
void World<T>::removeObject(particle<T> p1)
{
	for (int i = obj.begin(); i != obj.end(); i++)
	{
		if (obj[i].getName() == p1.getName())
		{
			obj.erase(i);
		}
	}
}
template <typename T>
void World<T>::addForceField(forceField<T> f1)
{
	fields.push_back(f1);
}

template <typename T>
void World<T>::removeForceField(forceField<T> f1)
{
	for (auto i = fields.begin(); i != fields.end(); i++)
	{
		if ((fields[(int)i]).getName() == f1.getName())
		{
			fields.erase(i);
		}
	}
}

template <typename T>
int World<T>::NoOfObjects()
{
	return obj.size();
}

template <typename T>
void World<T>::createAnimation()
{

	namedWindow(name, WINDOW_NORMAL);
	for (int i = 0; i < obj.size(); i++)
	{
		obj[i].putTo(mysandbox);
	}
	imshow(name, mysandbox);
	status = 0;
}

template <typename T>
void World<T>::Update()
{
	for (int i = 0; i < obj.size(); i++)
	{
		path.at<uchar>((obj[i].r)[1], (obj[i].r)[0]) = 255;
		obj[i].removeFrom(mysandbox);
		for (int j = 0; j < fields.size(); j++)
		{
			if (((obj[i]).r)[0] >= fields[j].Range[0] && ((obj[i]).r)[0] <= fields[j].Range[2] && ((obj[i]).r)[1] >= fields[j].Range[1] && ((obj[i]).r)[1] <= fields[j].Range[3])
				fields[j].applyOn(i, &obj);
		}
	}
	for (int i = 0; i < obj.size(); i++)
	{
		if ((obj[i].r)[0] + (obj[i].p)[0] > 0 && (obj[i].r)[1] + (obj[i].p)[1] > 0 && (obj[i].r)[0] + (obj[i].p)[0] < cols && (obj[i].r)[1] + (obj[i].p)[1] < rows)
			obj[i].r = obj[i].r + obj[i].p;

		else
		{
			if (natureOfWalls == ELASTIC)
			{
				if ((obj[i].r)[0] + (obj[i].p)[0] <= 0)
					(obj[i].p)[0] = -(obj[i].p)[0];
				if ((obj[i].r)[1] + (obj[i].p)[1] <= 0)
					(obj[i].p)[1] = -(obj[i].p)[1];
				if ((obj[i].r)[0] + (obj[i].p)[0] >= cols)
					(obj[i].p)[0] = -(obj[i].p)[0];
				if ((obj[i].r)[1] + (obj[i].p)[1] >= rows)
					(obj[i].p)[1] = -(obj[i].p)[1];
			}

			if (natureOfWalls == PASSIVE)
			{
				if ((obj[i].r)[0] + (obj[i].p)[0] <= 0)
					(obj[i].r)[0] = cols - 1;
				if ((obj[i].r)[1] + (obj[i].p)[1] <= 0)
					(obj[i].r)[1] = rows - 1;
				if ((obj[i].r)[0] + (obj[i].p)[0] >= cols)
					(obj[i].r)[0] = 1;
				if ((obj[i].r)[1] + (obj[i].p)[1] >= rows)
					(obj[i].r)[1] = 1;
			}
		}

		obj[i].putTo(mysandbox);
	}

	imshow(name, mysandbox);
}

template <typename T>
void World<T>::destroyAnimation()
{
	destroyWindow(name);
	status = 1;
}

template <typename T>
short World<T>::getStatusOfAnimation()
{
	return status;
}

template <typename T>
Mat World<T>::getScreenshot()
{
	return (Mat)mysandbox;
}

template <typename T>
void World<T>::showpath()
{
	namedWindow("PATH", WINDOW_NORMAL);
	imshow("PATH", path);
	waitKey(0);
}
