class Task {

	public:
	
		double mExecTime;
		double mRelativeDeadline;
		double mPeriod;
	
		Task(double execTime, double relativeDeadline, double period);
	
		double getUtilization();
};
