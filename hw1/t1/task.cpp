#include "task.h"

Task::Task(double execTime, double relativeDeadline, double period)
{
	mExecTime = execTime;
	mRelativeDeadline = relativeDeadline;
	mPeriod = period;
}

double Task::getUtilization()
{
	//TODO
	return 0;
}
