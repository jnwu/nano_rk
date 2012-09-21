#include "task.h"
#include "scheduling.h"
#include <iostream>
#include <list>

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

}

void Scheduling::hyperbolicBoundTest()
{

}

void Scheduling::WCRTTest()
{

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
