#ifndef SCHEDULING_H
#define SCHEDULING_H

#include "task.h"
#include <list>

using namespace std;

class Scheduling {

	private:

	public:
	list<Task> taskSet;
	
	Scheduling(list<Task> tasks);
	
	void sortRM();
	void sortSJF();
	void sortMUF();
	
	void LLBoundTest();
	void hyperbolicBoundTest();
	void WCRTTest();
	
};

#endif
