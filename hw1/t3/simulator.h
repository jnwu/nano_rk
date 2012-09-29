#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "task.h"
#include "testResult.h"
#include <iostream>
#include <list>
#include <math.h>
#include <list>
#include <vector>

using namespace std;

class Simulator {

	private:
		static const long SIMULATION_TIME = 100000;
		
		int findHighestPriority();
		double processJob(int index);
		bool adjustJobs(double timeIncrement, int index);
		
		double currentTime;
		
	public:
	list<Task> taskSet;
	vector<Task> taskVector;
	
	Simulator(list<Task> tasks);
	
	void sortRM();
	void sortSJF();
	void sortMUF();
	bool simulate();
	void printTaskSet();
	
	void reset();
};

#endif
