#include "task.h"
#include "scheduling.h"
#include <iostream>
#include <list>
#include <math.h>

using namespace std;

bool compare_SJF(Task &a, Task &b)
{
	return (a.mExecTime < b.mExecTime);
}

bool compare_MUF(Task &a, Task &b)
{
	return (a.getUtilization() > b.getUtilization());
}

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

void Scheduling::LLBoundTest()
{
	double utilization = 0;
	
	for (list<Task>::iterator it = this->taskSet.begin(); it != this->taskSet.end(); it++)
		utilization += it->getUtilization();
		
	double bound = this->taskSet.size() * (pow(2, 1/this->taskSet.size()) - 1);
	
	if (utilization <= bound)
		cout << "Liu and Layland Bound Test: Pass" << endl;
	else
		cout << "Liu and Layland Bound Test: Fail" << endl;
}

void Scheduling::hyperbolicBoundTest()
{
	double utilization = 1;
	
	for (list<Task>::iterator it = this->taskSet.begin(); it != this->taskSet.end(); it++)
		utilization = utilization * (1 + it->getUtilization());
		
	if (utilization <= 2)
		cout << "Hyperbolic Bound Test: Pass" << endl;
	else
		cout << "Hyperbolic Bound Test: Fail" << endl;
}

void Scheduling::WCRTTest()
{
	bool skip = true;
	for (list<Task>::iterator it = ++(this->taskSet.begin()); it != this->taskSet.end(); it++)
	{				
		double response = it->mExecTime;
		
		while (response <= it->mRelativeDeadline)
		{
			double interference = 0;
			
			for (list<Task>::iterator it2 = this->taskSet.begin(); it2 != this->taskSet.end(); it2++)
			{
				if (it2 == it)
					break;
					
				interference += ceil(response / it2->mPeriod) * it2->mExecTime;
			}
			
			if ((response == interference + it->mExecTime) && (response < it->mRelativeDeadline))
				break;
			else
				response = interference + it->mExecTime;
			
			cout << "interference = " << interference << " response = " << response << endl;			
		}
		
		if (response > it->mRelativeDeadline)
		{
			cout << "WCRT Test: Fail" << endl;
			return;
		}
	}
	
	cout << "WCRT Test: Pass" << endl;
}

void Scheduling::printTaskSet()
{
	cout << "Debug task set print" << endl;
	list<Task>::iterator it;
	for (it=taskSet.begin(); it!=taskSet.end(); ++it)
    {
    	Task t = *it;
    	cout << t.mExecTime << "\t" << t.mRelativeDeadline << "\t" << t.mPeriod << endl;
    }
    
    cout << "End debug task set print" << endl;
}
