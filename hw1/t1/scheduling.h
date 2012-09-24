#ifndef SCHEDULING_H
#define SCHEDULING_H

#include "task.h"
#include "testResult.h"
#include <iostream>
#include <list>
#include <math.h>
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
	
	bool LLBoundTest();
	bool hyperbolicBoundTest();
	bool WCRTTest();
	
	void printTaskSet();
};

#endif
