#ifndef TASK_H
#define TASK_H

class Task {

	public:
	
		double mExecTime;
		double mRelativeDeadline;
		double mPeriod;
		double execTimeRemaining;
		double remainingDeadline;
		int periodCount;
	
		Task(double execTime, double relativeDeadline, double period);
		Task();
	
		double getUtilization();
		
		void printTask();
};

#endif
