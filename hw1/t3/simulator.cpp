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
		double timeIncrement = 0;
		
		timeIncrement = processJob(index);

		bool failed = adjustJobs(timeIncrement,index);
		
		currentTime += timeIncrement;
		
		cout << currentTime << " " << timeIncrement << endl;
		
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

double Simulator::processJob(int index)
{
	int currentJob = index;
	if (currentJob < 0)
		currentJob = taskVector.size() - 1;
		
	//printTaskSet();
	
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

bool Simulator::adjustJobs(double timeIncrement, int index)
{
	//printTaskSet();
	for (int i = 0; i < taskVector.size(); i++)
	{
		//failed deadline
		if (taskVector[i].remainingDeadline != 0 && taskVector[i].execTimeRemaining != 0)
		{
			taskVector[i].remainingDeadline -= timeIncrement;
			if (taskVector[i].remainingDeadline <= 0 ) {
				//cout << "task failed: " << i << endl;
				return true;
			}
		}	
		double intpart, fractpart;
		fractpart = modf((timeIncrement + currentTime)/taskVector[i].mPeriod, &intpart);
		//cout << "period count:" << fractpart << " " << intpart << endl;
		//if ((intpart - taskVector[i].periodCount) > 1)
		//	return true;
		
		if (!fractpart || intpart - taskVector[i].periodCount == 1 ||fractpart > 0.99999)
		{
			taskVector[i].execTimeRemaining = taskVector[i].mExecTime;
			taskVector[i].remainingDeadline = taskVector[i].mRelativeDeadline;
		}
		
		taskVector[i].periodCount = intpart;
	}
	
	return false;
}

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
