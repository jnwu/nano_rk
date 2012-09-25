#include "simulator.h"
#include <vector>

using namespace std;

bool compare_RM(Task &a, Task &b)
{
	return (a.mPeriod < b.mPeriod);
}

Simulator::Simulator(list<Task> tasks)
{
	taskSet = tasks;
	currentTime = 0;
}

void Simulator::sortRM()
{
	taskSet.sort(compare_RM);
}

bool Simulator::simulate()
{	
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
	
	while (currentTime < SIMULATION_TIME)
	{
		int index = findHighestPriority();
		int timeIncrement = 0;
		
		timeIncrement = processJob(index);
		
		bool failed = adjustJobs(timeIncrement,index);
		
		currentTime += timeIncrement;
		
		if (failed)
			return false;	
	}
	
	return true;
}

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

int Simulator::processJob(int index)
{
	if (index < 0)
		index = taskVector.size();
		
	double min = 0;
	for (int i = 0; i < index; i++)
	{
		double newMin = currentTime/taskVector[i].mPeriod +1;
		if((newMin) - currentTime < min)
			min = newMin;
	}
	
	if (index == taskVector.size())
		return min;
	
	if (taskVector[index].execTimeRemaining < min)
		min = taskVector[index].execTimeRemaining;
		
	taskVector[index].execTimeRemaining -= min;
	
	return min;
}

bool Simulator::adjustJobs(int timeIncrement, int index)
{
	for (int i = 0; i < taskVector.size(); i++)
	{
		//failed deadline
		taskVector[i].remainingDeadline -= timeIncrement;
		if (taskVector[i].remainingDeadline < 0)
			return false;
			
		if (i == index)
			continue;
			
		int periodCounts = ((timeIncrement + currentTime)/taskVector[i].mPeriod) - taskVector[i].periodCount;
		
		//missed a cycle
		if (periodCounts > 1)
			return false;
		else if (periodCounts == 1)
		{
			taskVector[i].execTimeRemaining = taskVector[i].mExecTime;
			taskVector[i].remainingDeadline = taskVector[i].mRelativeDeadline - ((timeIncrement + currentTime) - taskVector[i].periodCount * taskVector[i].mPeriod);
		}
	}
	
	return true;
}

void Simulator::printTaskSet()
{
	cout << "Debug task set print" << endl;
	list<Task>::iterator it;
	for (it=taskSet.begin(); it!=taskSet.end(); ++it)
    {
    	Task t = *it;
    	t.printTask();
    }
    
    cout << "End debug task set print" << endl;
}
