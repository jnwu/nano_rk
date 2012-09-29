#include "task.h"
#include <iostream>

using namespace std;

Task::Task(double execTime, double relativeDeadline, double period)
{
	mExecTime = execTime;
	mRelativeDeadline = relativeDeadline;
	mPeriod = period;
}

Task::Task()
{

}

double Task::getUtilization()
{
	return (mExecTime / mPeriod);
}

void Task::printTask()
{
	cout << mExecTime << "\t" << mRelativeDeadline << "\t" << mPeriod << "\t" << execTimeRemaining << "\t" << remainingDeadline <<endl;
}
