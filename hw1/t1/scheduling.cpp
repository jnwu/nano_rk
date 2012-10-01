/**
* EECE 494 Programming Assignment #1
* scheduling.cpp
*
*/

#include "scheduling.h"

using namespace std;

/*
* sorting function for shortest job first
*/
bool compare_SJF(Task &a, Task &b)
{
	return (a.mExecTime < b.mExecTime);
}

/*
* sorting function for most utilization first
*/
bool compare_MUF(Task &a, Task &b)
{
	return (a.getUtilization() > b.getUtilization());
}

/*
* sorting function for rate monotonic
*/
bool compare_RM(Task &a, Task &b)
{
	return (a.mPeriod < b.mPeriod);
}

Scheduling::Scheduling(list<Task> tasks)
{
	taskSet = tasks;
}

void Scheduling::sortRM()
{
	taskSet.sort(compare_RM);
}

void Scheduling::sortSJF()
{
	taskSet.sort(compare_SJF);
}

void Scheduling::sortMUF()
{
	taskSet.sort(compare_MUF);
}

bool Scheduling::LLBoundTest()
{
	int start = clock();

	double utilization = 0;
	
	for (list<Task>::iterator it = this->taskSet.begin(); it != this->taskSet.end(); it++)
		if (it->mRelativeDeadline < it->mPeriod)
			utilization += it->mExecTime / it->mRelativeDeadline;
		else
			utilization += it->getUtilization();
		
	double bound = this->taskSet.size() * (pow(2, 1/this->taskSet.size()) - 1);
	
	if (utilization <= bound) {
		//cout << "Liu and Layland Bound Test: Pass" << endl;
		return true;
	} else {
		//cout << "Liu and Layland Bound Test: Fail" << endl;
		return false;

	}
}

bool Scheduling::hyperbolicBoundTest()
{
	int start = clock();
	
	double utilization = 1;
	
	for (list<Task>::iterator it = this->taskSet.begin(); it != this->taskSet.end(); it++)
	{
		if (it->mRelativeDeadline < it->mPeriod)
			utilization = utilization * (1 + it->mExecTime / it->mRelativeDeadline);
		else
			utilization = utilization * (1 + it->getUtilization());
	}
		
	if (utilization <= 2)
		//cout << "Hyperbolic Bound Test: Pass" << endl;
		return true;
	else
		//cout << "Hyperbolic Bound Test: Fail" << endl;
		return false;
}

bool Scheduling::WCRTTest()
{
	int start = clock();
	
	for (list<Task>::iterator it = ++(this->taskSet.begin()); it != this->taskSet.end(); it++)
	{				
		double response = it->mExecTime;
		
		while (response <= it->mRelativeDeadline)
		{
			double interference = 0;
			
			for (list<Task>::iterator it2 = this->taskSet.begin(); it2 != this->taskSet.end(); it2++)
			{
				if (it == it2)
					break;
					
				interference += ceil(response / it2->mPeriod) * it2->mExecTime;
			}			
			
			if ((response == interference + it->mExecTime) && (response <= it->mRelativeDeadline))
			{
				//cout << "found response: " << interference + it->mExecTime << endl;
				break;
			}
			else
				response = interference + it->mExecTime;

			//cout << "interference = " << interference << " response = " << response << endl;
		}
				
		if (response > it->mRelativeDeadline)
		{
			//cout << "WCRT Test: Fail" << endl;
			return false;
		}
		else
		{
			//cout << "add task" << endl;
		}
	}
	//cout << "WCRT Test: Pass" << endl;
	return true;
}

void Scheduling::printTaskSet()
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
