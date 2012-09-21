#ifndef TASK_H
#define TASK_H

class Task {

	public:
	
		double mExecTime;
		double mRelativeDeadline;
		double mPeriod;
	
		Task(double execTime, double relativeDeadline, double period);
	
		double getUtilization();
};

#endif
