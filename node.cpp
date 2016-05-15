#include "node.h"
#include <iostream>
#include <unistd.h>
node::node(double inLocX,double inLocY)
{
	locX=inLocX;
	locY=inLocY;
	active=0;
}

double node::getX()const
{
	return locX;
}

double node::getY()const
{
	return locY;
}

void node::addPartnerNode(node* inNode)
{
	if(inNode!=this)
	{
		nodeArray.push_back(inNode);
	}
}

bool node::isActive()const
{
	return active;
}

double node::getDistance(unsigned long inIteration,unsigned int inCurrentNode,node* inFirstNode)
{
	double returnValue=0;
	active=true;
	unsigned int index=0;
	if(nodeArray.size()-inCurrentNode==0)
	{
		XDrawLine(display,win,gc,locX*30,locY*30,inFirstNode->getX()*30,inFirstNode->getY()*30);
		XFlush(display);
		usleep(100000);
		active = false;
		return distance(inFirstNode);
	}
	unsigned int divider = factor(nodeArray.size()-inCurrentNode-1);
	if(divider==0)
	{
		index=0;
	}
	else
	{
		index = floor(inIteration/divider);
	}
	int i=0;
	unsigned int counter = 0;
	do
	{
		if(!nodeArray[i]->isActive())
		{
			counter++;
		}
		i++;
	}while(counter<=index);
	i--;
	XDrawLine(display,win,gc,locX*30,locY*30,nodeArray[i]->getX()*30,nodeArray[i]->getY()*30);
	XFlush(display);
	usleep(100000);
	if(inCurrentNode == 0)
	{
		returnValue = distance(nodeArray[i]) + nodeArray[i]->getDistance(inIteration%divider,++inCurrentNode,this);
		active=false;
		return returnValue;
	}
	returnValue = distance(nodeArray[i]) + nodeArray[i]->getDistance(inIteration%divider,++inCurrentNode,inFirstNode);
	active=false;
	return returnValue;
} 

unsigned long node::factor(const unsigned long inNumber)const
{
	unsigned long returnValue=1;
	for(unsigned long i = 1;i <= inNumber; i++)
	{
		returnValue=returnValue*i;
	}
	return returnValue;
}

double node::distance(node* inNode)
{
	return sqrt(pow(locX-inNode->locX,2)+pow(locY-inNode->locY,2));
}

void node::setWindowSettings(Display* inDisplay,GC inGC, Window inWindow)
{
	display = inDisplay;
	gc = inGC;
	win = inWindow;
}



