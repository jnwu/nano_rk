#include "simulator.h"
#include <vector>
#include <math.h>

using namespace std;

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
		
		cout << currentTime << " " << timeIncrement << endl << endl;;
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
	int currentJob = index;
	if (currentJob < 0)
		currentJob = taskVector.size() - 1;
		
	//cout << (currentTime/taskVector[0].mPeriod + 1) << " " << (currentTime/taskVector[0].mPeriod + 1) * taskVector[0].mPeriod << " " << currentTime << endl;
	double min = (int)(currentTime/taskVector[0].mPeriod + 1) * taskVector[0].mPeriod - currentTime;
	for (int i = 1; i <= currentJob; i++)
	{
		double newMin = (int)(currentTime/taskVector[i].mPeriod + 1) * taskVector[i].mPeriod - currentTime;
		if(newMin < min)
			min = newMin;
			
		//cout << "min: " << min << "newMin: " << newMin << endl;
	}

	if (index >= 0)
	{
		if (taskVector[index].execTimeRemaining < min)
			min = taskVector[index].execTimeRemaining;
		
		taskVector[index].execTimeRemaining -= min;
	}
	
	cout << index << " " << min << endl;
	
	return min;
}

bool Simulator::adjustJobs(int timeIncrement, int index)
{
	for (int i = 0; i < taskVector.size(); i++)
	{
		//failed deadline
		if (taskVector[i].remainingDeadline != 0 && taskVector[i].execTimeRemaining != 0)
		{
			taskVector[i].remainingDeadline -= timeIncrement;
			if (taskVector[i].remainingDeadline <= 0 )
				return true;
		}	
		double intpart, fractpart;
		fractpart = modf((timeIncrement + currentTime)/taskVector[i].mPeriod, &intpart);
		//cout << "period count:" << fractpart << endl;
		
		if (!fractpart)
		{
			taskVector[i].execTimeRemaining = taskVector[i].mExecTime;
			taskVector[i].remainingDeadline = taskVector[i].mRelativeDeadline;
		}
	}
	//printTaskSet();
	return false;
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
