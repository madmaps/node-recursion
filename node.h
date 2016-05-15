#ifndef __NODE__
#define __NODE__
#include<math.h>
#include<vector>
#include <X11/Xlib.h>

class node
{
	public:
		node(double inLocX,double inLocY);
		double getX()const;
		double getY()const;
		void addPartnerNode(node* inNode);
		bool isActive()const;
		double getDistance(unsigned long inIteration,unsigned int inCurrentNode=0,node* inFirstNode=0);
		unsigned long factor(const unsigned long inNumber)const;
		void setWindowSettings(Display* inDisplay,GC inGC, Window inWindow);
	private:
		double distance(node* inNode);
		std::vector<node*> nodeArray;
		bool active;
		double locX;
		double locY;
		Window win;
		GC gc;
		Display* display;
};
#endif
