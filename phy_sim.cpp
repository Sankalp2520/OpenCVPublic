#include <iostream>
#include "physics.cpp"
//#include<QApplication>

using namespace std;

void attraction(int i, vector<particle<Vec3b>> *obj, int *range)
{
	static int t = 0, m;
	Vec2f r;
	float modr;
	Vec2f com = 0;
	if ((*obj)[i].getName() != "centre")
	{
		for (m = 0; m < (*obj).size()-1; m++)
		{
			com += ((*obj)[m]).r;
			if (m != i /*&&m!=0*/)
			{
				r = Vec2f(((*obj)[m]).r[0] - ((*obj)[i]).r[0], ((*obj)[m]).r[1] - ((*obj)[i]).r[1]);
				modr = sqrt(r[0] * r[0] + r[1] * r[1]);
				if (modr > ((*obj)[i]).getSize() + ((*obj)[m]).getSize())
				{   //if(i==0)
					//((*obj)[i]).p+=r/pow(r[0]*r[0]+r[1]*r[1],1.5f);///((*obj)[m]).getSize();
					//if(i==1)
					((*obj)[i]).p += 80000 * r / pow(r[0] * r[0] + r[1] * r[1], 2);
				}
				/*((*obj)[i]).p+=Vec2f(0,0.008)-0.01*((*obj)[i]).p;
		cout<<"redball speed:"<<((*obj)[0]).p<<endl;
		cout<<"greenball speed:"<<((*obj)[1]).p<<endl;
		cout<<"****************"<<endl;*/
				//cout<<((*obj)[m]).p<<" ";
			}
		}
		((*obj)[m]).r = Vec2f(com[0] / ((*obj).size()-1), com[1] / ((*obj).size()-1));
	}
	/*
	((*obj)[i]).p+=Vec2f(0,1);
	cout<<t<<" "<<((*obj)[i]).r<<" ";
	t++;*/
}

void callback1(World<Vec3b> *world)
{
	(*world).createAnimation();
	//world2.createAnimation();
	//int fps=24;
	//VideoWriter vw("/home/sankalp/Desktop/opencv/solarsys.avi",VideoWriter::fourcc('M','J','P','G'),fps,Size(1000,1000),true);

	while (true)
	{
		(*world).Update();
		//	world2.Update();
		//vw.write((*world).getScreenshot());
		if (waitKey(10) == 27)
		{
			break;
		}
	}

	(*world).destroyAnimation();
	//world2.destroyAnimation();

	(*world).showpath();

	return;
}
/*void callback2(QApplication* app,World<Vec3b> *world)
{
		cout<<"D";
	(*world).createAnimation();

		while(true)
	{
		(*world).Update();

		if(waitKey(10)==27)
			{
				break;
			}
	}

	(*world).destroyAnimation();

}*/

int main(int argc, char *argv[])
{
	//QApplication app(argc, argv);

	particle<Vec3b> redball("red", Vec2f(500, 500), Vec2f(0,-1), Vec3b(0, 0, 255), 10), greenball("green", Vec2f(600, 500), Vec2f(0, 1), Vec3b(0, 255, 0), 10);
	particle<Vec3b> centre("centre", Vec2f(-1,-1), Vec2f(0, 0), Vec3b(255, 255, 255), 3);
	//  particle<Vec3b> b1("b1",Vec2f(500,800),Vec2f(-1,-2),Vec3b(255,10,200),10);
	// particle<Vec3b> b2("b2",Vec2f(30,41),Vec2f(-1,-2),Vec3b(255,255,0),10);
	// particle<Vec3b> b3("b3",Vec2f(900,917),Vec2f(1,-2),Vec3b(255,0,0),10);
	// particle<Vec3b> b4("b4",Vec2f(900,171),Vec2f(1,2),Vec3b(0,255,255),10);
	// particle<Vec3b> b5("b5",Vec2f(10,917),Vec2f(-1,2),Vec3b(255,0,255),10);

	int region[4] = {0, 0, 1000, 1000};
	forceField<Vec3b> attractiveForce("attractiveForce", region, attraction);

	World<Vec3b> world1("sandbox1", 1000, 1000, RGB, PASSIVE);
	//World<Vec3b> world2("sandbox2",640,640,RGB,ELASTIC);

	world1.addObject(redball);
	world1.addObject(greenball);
	// world1.addObject(b1);
	// world1.addObject(b2);
	// world1.addObject(b3);
	// world1.addObject(b4);
	// world1.addObject(b5);
	world1.addObject(centre);

	world1.addForceField(attractiveForce);
	//world2.addObject(orangeball);

	thread t1(callback1, &world1);
	//thread t2(callback2,&app,&world2);
	/*	while(1)
		cout<<"d";*/

	t1.join();
	//t2.join();

	return 0;
}