#include "task.h"
#include "scheduling.h"
#include <list>

using namespace std;

bool compare_SJF(Task &a, Task &b)
{
	return (a.mExecTime < b.mExecTime);
}

bool compare_MUF(Task &a, Task &b)
{
	return (a.getUtilization() < b.getUtilization());
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
