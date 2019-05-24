#ifndef PHYSICS_CLASS
#define PHYSICS_CLASS

#define RGB 1
#define BW 0

#define ELASTIC 1
#define PASSIVE 0

using namespace std;
using namespace cv;

typedef Mat sandbox;

template <typename T>
class World;

template <typename T>
class particle
{
private:
	String name;
	T color;	//color of the particle
	int size;
public:

	Vec2f r,p;	//r is the position of the centre of mass and p is the momentum of the centre of the mass

	particle(String n, Vec2f r1,Vec2f p1,T c,int S);

	String getName();

	void setColor(T c);

	T getColor()
	{
		return color;
	}

	int getSize();

	void putTo(sandbox box);
	
	void removeFrom(sandbox box);

};

template <typename T>
class forceField
{
private:
	String name;
	void (*definition) (int,vector<particle<T>>*,int* );
public:

	int *Range;  //Range[0]=startx,Range[1]=starty,Range[2]=endx,Range[3]=endy

	forceField(String n,int R[4],void (*f)(int,vector<particle<T>>*,int*));
	
	String getName();

	void addDefinition(void (*f)(int,vector<particle<T>>*,int*));

	void addRange(int R[4]);

	int* getRange();
/*
	void (*)(Vec2f&) getDefinition()
	{
		return definition;
	}*/

	void applyOn(int i,vector<particle<T>>* obj);
};

template <typename T>
class World
{
private:
	String name;
	sandbox mysandbox;
	int rows;
	int cols;
	vector<particle<T>> obj;
	vector<forceField<T>> fields;
	Mat path;
	int natureOfWalls;
	short status;	//status = -1 -> world has been constructed but animation has not been created
	//status = 0 -> animation has been created
	//status = 1 -> animation has been destroyed

public:
	World(String n,int r,int c,int flags,int now);

	String getName();

	void addObject(particle<T> p1);

	void removeObject(particle<T> p1);

	void addForceField(forceField<T> f1);

	void removeForceField(forceField<T> f1);

	int NoOfObjects();

	void createAnimation();

	void Update();

	void destroyAnimation();

	short getStatusOfAnimation();

	Mat getScreenshot();

	void showpath();
};

#endif