#include <iostream>
#include<opencv2/opencv.hpp>
#include <thread>
#include<stdio.h>
#include<poll.h>
#include<unistd.h>
using namespace std;

using namespace cv;
//This is the function that will run in parallel
// It will be passed to the thread
void thread_method(Mat img) {
   	struct pollfd mypoll = { STDIN_FILENO, POLLIN|POLLPRI };
    	char ch;
	std::cout << "Function running in thread "<< std::endl;
	//Mat img=imread("/home/sankalp/Desktop/Blender/Images/cup1.png");
	//long long int i=0;
	namedWindow("Hello");
	while(true)
	{
		if(poll(&mypoll,1,10))
		{
			scanf("%c",&ch);
			if(ch==27)
			return;
		}
	}
}
int main() {
	//This statement will launch thread in parallel to main function
	Mat img=imread("/home/sankalp/Desktop/Blender/Images/cup1.png");
	std::thread t(thread_method,img);
	std::cout << "\nThe main function execution\n";
	//This is how we join the new thread with main
	//Mat img=imread("/home/sankalp/Desktop/Blender/Images/cube1.png");
	//imshow("Hello1",img);
	//cin.get();
	t.join();
	//getchar();
	return 0;
}
