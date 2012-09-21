#include "task.h"

Task::Task(double execTime, double relativeDeadline, double period)
{
	mExecTime = execTime;
	mRelativeDeadline = relativeDeadline;
	mPeriod = period;
}

double Task::getUtilization()
{
	return (mExecTime / mPeriod);
}
