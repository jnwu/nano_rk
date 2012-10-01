/**
* EECE 494 Programming Assignment #1
* scheduling.h
*
*/

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
	
	//sort functions to sort in from highest to lowest priority
	void sortRM();
	void sortSJF();
	void sortMUF();
	
	//tests for schedulability
	bool LLBoundTest();
	bool hyperbolicBoundTest();
	bool WCRTTest();
	
	void printTaskSet();
};

#endif
