/**
* EECE 494 Programming assignment 1
* File: simulator.cpp
* 
*/

#include "simulator.h"
#include <vector>
#include <math.h>

using namespace std;

//sort function for SJF
bool compare_SJF(Task &a, Task &b)
{
	return (a.mExecTime < b.mExecTime);
}

bool compare_RM(Task &a, Task &b)
{
	return (a.mPeriod < b.mPeriod);
}

bool compare_MUF(Task &a, Task &b)
{
	return (a.getUtilization() > b.getUtilization());
}

Simulator::Simulator(list<Task> tasks)
{
	taskSet = tasks;
	currentTime = 0;
	printTaskSet();
}

void Simulator::sortRM()
{
	taskSet.sort(compare_RM);
}

void Simulator::sortSJF()
{
	taskSet.sort(compare_SJF);
}

void Simulator::sortMUF()
{
	taskSet.sort(compare_MUF);
}

/*
* Simulator for task sets
* Simulator is common for all fixed priority scheduling
*/
bool Simulator::simulate()
{	

	//convert list to vector for easier use
	vector<Task> tasks;
	list<Task>::iterator it;
	for ( it=taskSet.begin() ; it != taskSet.end(); it++ )
	{
		it->execTimeRemaining = it->mExecTime;
		it->remainingDeadline = it->mRelativeDeadline;
		it->periodCount = 0;
		tasks.push_back(*it);		
	}	
	
	this->taskVector = tasks;
	
	// while we are less than 100,000 units of time
	while (currentTime < SIMULATION_TIME)
	{
	
		//find highest priority task 
		int index = findHighestPriority();
		double timeIncrement = 0;
		
		//calculate time to next task drop (time%period == 0)
		timeIncrement = processJob(index);

		//adjust timing constraints of other jobs and check to see if deadlines are missed
		bool failed = adjustJobs(timeIncrement,index);
		
		currentTime += timeIncrement;
		
		cout << currentTime << " " << timeIncrement << endl;
		
		if (failed)
			return false;	
	}
	
	return true;
}

/*
* find highest priority job with time remaining
*/
int Simulator::findHighestPriority()
{
	for (int i = 0; i < taskVector.size(); i++)
	{
		if (taskVector[i].execTimeRemaining > 0)
		{
			return i;
		}
	}
	
	return -1;
}

/*
* find time to closest time%period == 0
*/
double Simulator::processJob(int index)
{
	// if all jobs done count time
	int currentJob = index;
	if (currentJob < 0)
		currentJob = taskVector.size() - 1;
		
	//printTaskSet();
	
	// current time % period
	double min = (int)(currentTime/taskVector[0].mPeriod + 1) * taskVector[0].mPeriod - currentTime;
	
	if (min < 0.000001)
		min = taskVector[0].mPeriod;
		
	for (int i = 1; i <= taskVector.size(); i++)
	{
		double newMin = (int)(currentTime/taskVector[i].mPeriod + 1) * taskVector[i].mPeriod - currentTime;
		
		//cout << "min: " << min << "newMin: " << newMin << endl;
				
		if(newMin < min && newMin > 0.000001)
			min = newMin;
			
	}

	if (index >= 0)
	{
		if (taskVector[index].execTimeRemaining < min)
			min = taskVector[index].execTimeRemaining;
		
		taskVector[index].execTimeRemaining -= min;
	}
	
	//cout << index << " " << min << endl;
	
	return min;
}

/*adjust timing constraints of other jobs and check 
* to see if deadlines are missed
*/
bool Simulator::adjustJobs(double timeIncrement, int index)
{
	//printTaskSet();
	for (int i = 0; i < taskVector.size(); i++)
	{
		//check if failed deadline
		if (taskVector[i].remainingDeadline != 0 && taskVector[i].execTimeRemaining != 0)
		{
			taskVector[i].remainingDeadline -= timeIncrement;
			if (taskVector[i].remainingDeadline <= 0 ) {
				//cout << "task failed: " << i << endl;
				return true;
			}
		}	
		
		//find the int part and the fraction part to the next period
		double intpart, fractpart;
		fractpart = modf((timeIncrement + currentTime)/taskVector[i].mPeriod, &intpart);
		//cout << "period count:" << fractpart << " " << intpart << endl;
		//if ((intpart - taskVector[i].periodCount) > 1)
		//	return true;
		
		
		//drop next task. the 0.9999 is for double number represenations
		if (!fractpart || intpart - taskVector[i].periodCount == 1 ||fractpart > 0.99999)
		{
			taskVector[i].execTimeRemaining = taskVector[i].mExecTime;
			taskVector[i].remainingDeadline = taskVector[i].mRelativeDeadline;
		}
		
		taskVector[i].periodCount = intpart;
	}
	
	return false;
}

//reset simulator for next simulation
void Simulator::reset()
{
	currentTime = 0;
}

void Simulator::printTaskSet()
{
	cout << "Debug task set print" << endl;
	for (int i = 0; i < taskVector.size(); i++)
    {
    	taskVector[i].printTask();
    }
    
    cout << "End debug task set print" << endl;
}
