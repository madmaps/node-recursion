#include <iostream>
#include <X11/Xlib.h>
#include <unistd.h>
#include "node.h"

using namespace std;

int main()
{
	Display* display;
	display = XOpenDisplay(0);
	
	int screenNum = DefaultScreen(display);
	
	Window rootWindow = RootWindow(display, screenNum);
	unsigned long whitePixel = WhitePixel(display, screenNum);
	unsigned long blackPixel = BlackPixel(display, screenNum);
	
	Window win = XCreateSimpleWindow(display,
																				rootWindow,
																				0,0,
																				600,600,
																				0,
																				blackPixel,
																				whitePixel);

	
    XSelectInput(display, win, StructureNotifyMask);
	
	XMapWindow(display,win);
	
	GC gc = XCreateGC(display, win, 0, 0);
	
	 XSetForeground(display, gc, blackPixel);
	 XEvent e;
	do
	{
		XNextEvent(display, &e);
     }while(e.type!=MapNotify);
      
    //XDrawLine(display, win, gc, 10, 60, 20, 20); 
	XFlush(display);
	
	
	const int numberOfNodes=8;
	node** nodeList = new node*[numberOfNodes];
	nodeList[0] = new node(3,8);
	nodeList[1] = new node(3,10);
	nodeList[2] = new node(8,12);
	nodeList[3] = new node(15,11);
	nodeList[4] = new node(13,1);
	nodeList[5] = new node(12,14);
	nodeList[6] = new node(4,16);
	nodeList[7] = new node(17,3);
	/*nodeList[8] = new node(9,13);
	nodeList[9] = new node(2,5);
	nodeList[10] = new node(19,17);
	nodeList[11] = new node(5,13);*/
	for(int i = 0; i < numberOfNodes;i++)
	{
		nodeList[i]->setWindowSettings(display,gc,win);
		for(int j = 0;j<numberOfNodes;j++)
		{
			nodeList[i]->addPartnerNode(nodeList[j]);
		}
	}
	double lowestDistance=99999999;
	int lowIndex=0;
	double returnDistance=0;
	unsigned int totalPos = nodeList[0]->factor(numberOfNodes-1);
	
	for(unsigned int i = 0; i<totalPos;i++)
	{
		XClearWindow(display,win);
		XFlush(display);

		for(unsigned int j = 0;j < numberOfNodes; j++)
		{
			XDrawPoint(display,win,gc,(int)nodeList[j]->getX()*30,(int)nodeList[j]->getY()*30);
		}
		XFlush(display);
		usleep(100000);
		returnDistance = nodeList[0]->getDistance(i);
		if(lowestDistance>returnDistance)
		{
			lowIndex = i;
			lowestDistance=returnDistance;
		}
		cout << "Route[" << i << "]: " << returnDistance << endl;
	}
	cout << endl << "Shortest Distance[" << lowIndex<< "/" << totalPos << "]: " << lowestDistance << endl;
	cout << "Finished Loop" << endl;
	XCloseDisplay(display);
	return 0;
}
