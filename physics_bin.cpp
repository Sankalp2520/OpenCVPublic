//#include<thread>

/*void callback(String name,vector<particle<Vec3b>> obj,sandbox mysandbox,int rows,int cols)
{
		namedWindow(name,WINDOW_NORMAL);

	while(true)
		{
			for(int i=0;i<obj.size();i++)
			{
				obj[i].removeFrom(mysandbox);
				if((obj[i].r)[0]+(obj[i].p)[0]>0&&(obj[i].r)[1]+(obj[i].p)[1]>0&&(obj[i].r)[0]+(obj[i].p)[0]<cols&&(obj[i].r)[1]+(obj[i].p)[1]<rows)
				obj[i].r=obj[i].r+obj[i].p;
			}

			for(int i=0;i<obj.size();i++)
			{
				obj[i].putTo(mysandbox);				
			}

			imshow(name,mysandbox);
			if(waitKey(10)==27)
			{
				break;
			}
		}

		destroyWindow(name);
}*/

/*std::thread t(callback,name,obj,mysandbox,rows,cols);
		t.join();
		t.~thread();*/

	/*long long int c=0;
	while(true)
		{
			(obj[1].p)[0]=2*sin(c/10);
			(obj[1].p)[1]=2*cos(c/10);
			(obj[0].p)[1]=2*cos(c/10);
			for(int i=0;i<obj.size();i++)
			{
				obj[i].removeFrom(mysandbox);
				if((obj[i].r)[0]+(obj[i].p)[0]>0&&(obj[i].r)[1]+(obj[i].p)[1]>0&&(obj[i].r)[0]+(obj[i].p)[0]<cols&&(obj[i].r)[1]+(obj[i].p)[1]<rows)
				obj[i].r=obj[i].r+obj[i].p;
			}

			for(int i=0;i<obj.size();i++)
			{
				obj[i].putTo(mysandbox);				
			}

			imshow(name,mysandbox);
			if(waitKey(10)==27)
			{
				break;
			}
			c++;
		}

		destroyWindow(name);*/


	/*std::thread *t1=*///world1.Animate();
	//cout<<"what?";
	//cin.get();
	/*std::thread *t2=*///world2.Animate();

	//t1->join();
	//t2->join();

void boundary1(int i ,vector <particle<Vec3b>>* obj,int* range)
{
	static int t=0;
	float px;
		px=-1*((*obj)[i]).p[0];
			//if((((*obj)[i]).r)[0]==range[0]+1)
			//((*obj)[i]).p=((*obj)[i]).p-Vec2f(((*obj)[i]).r[0]-995,0)*2/25;
			while(((*obj)[i]).p[0]!=px)
			{
				//usleep(1000);
				//cout<<"|calledinside|";
				((*obj)[i]).p=Vec2f(px,((*obj)[i]).p[1]);
			}	

	t++;
	//cout<<t<<"|";
}
void boundary2(int i,vector <particle<Vec3b>>* obj,int* range)
{
	static int t=0;
	float py;
		py=-1*((*obj)[i]).p[1];
			//if((((*obj)[i]).r)[0]==range[0]+1)
			//((*obj)[i]).p=((*obj)[i]).p-Vec2f(((*obj)[i]).r[0]-995,0)*2/25;
			while(((*obj)[i]).p[1]!=py)
			{
				//usleep(1000);
				//cout<<"|calledinside|";
				((*obj)[i]).p=Vec2f(((*obj)[i]).p[0],py);
			}	

	t++;
	//cout<<"called";
}

void boundary3(int i,vector <particle<Vec3b>>* obj,int* range)
{
	static int t=0;
	float px;
		px=-1*((*obj)[i]).p[0];
			//if((((*obj)[i]).r)[0]==range[0]+1)
			//((*obj)[i]).p=((*obj)[i]).p-Vec2f(((*obj)[i]).r[0]-995,0)*2/25;
			while(((*obj)[i]).p[0]!=px)
			{
				//usleep(1000);
				//cout<<"|calledinside|";
				((*obj)[i]).p=Vec2f(px,((*obj)[i]).p[1]);
			}	

	t++;
	//cout<<"called";
}

void boundary4(int i,vector <particle<Vec3b>>* obj,int* range)
{
	static int t=0;
	float py;
		py=-1*((*obj)[i]).p[1];
			//if((((*obj)[i]).r)[0]==range[0]+1)
			//((*obj)[i]).p=((*obj)[i]).p-Vec2f(((*obj)[i]).r[0]-995,0)*2/25;
			while(((*obj)[i]).p[1]!=py)
			{
				//usleep(1000);
				//cout<<"|calledinside|";
				((*obj)[i]).p=Vec2f(((*obj)[i]).p[0],py);
			}	

	t++;
	//cout<<"called";
}

	int r1[4]={950,0,1000,1000},r2[4]={0,950,1000,1000},r3[4]={0,0,50,1000},r4[4]={0,0,1000,50};

	forceField<Vec3b> Boundary1("Boundary1",r1,boundary1);
	forceField<Vec3b> Boundary2("Boundary2",r2,boundary2);
	forceField<Vec3b> Boundary3("Boundary3",r3,boundary3);
	forceField<Vec3b> Boundary4("Boundary4",r4,boundary4);

		/*world1.addForceField(Boundary1);
	world1.addForceField(Boundary2);
	world1.addForceField(Boundary3);
	world1.addForceField(Boundary4);*/