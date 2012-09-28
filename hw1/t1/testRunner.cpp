/*
*	File: 		testRunner.cpp
*
*	Course:		EECE 494
*	Description:
*
*	Team:		Nick Adams
*				Oscar Lee
*				Catherine Wang
*				Jack Wu
*
*/


#include <iostream>
#include <sstream>
#include <fstream>
#include <list>
#include <string>

#include "task.h"
#include "scheduling.h"

using namespace std;

int main (int argc, char *argv [])
{	
	ifstream in(argv[1],ifstream::in);
	if (!in.is_open())
	{
		cout << "error, unable to open file" << endl;
		return -1;
		
	}
	
	ofstream testResultFile;
	testResultFile.open ("results.csv",ios_base::app);
	if (!testResultFile.is_open())
	{
		cout << "error, unable to open file" << endl;
		return -1;
	}
	
	TestResult *testResult = new TestResult();
	
	string line; 
	
	list<Task> taskSet;
	bool begin = false;
  	while (in.good())
    {
    	getline(in,line);
    	
		if (line.find("begin") != string::npos)
		{
			begin = true;
			continue;
		}
		
		if (line.find("end") != string::npos)
		{
			int ticksAtStart;
			TestData testData;
			
			begin = false;
			Scheduling schedule(taskSet);
			
			schedule.sortRM();
			
			ticksAtStart = clock();
			testData.rmLLTest = schedule.LLBoundTest();
			cout << "Schedulable using RM scheduling / Liu and Layland bound test: " << (testData.rmLLTest?"Y":"N") << endl;
			cout << "Time Taken: " << (float)(clock() - ticksAtStart) / CLOCKS_PER_SEC << " seconds" << endl << endl;
			
			ticksAtStart = clock();
			testData.rmHBTest = schedule.hyperbolicBoundTest();
			cout << "Schedulable using RM scheduling / Hyperbolic bound test: " << (testData.rmHBTest?"Y":"N") << endl;
			cout << "Time Taken: " << (float)(clock() - ticksAtStart) / CLOCKS_PER_SEC << " seconds" << endl << endl;
			
			ticksAtStart = clock();
			testData.rmWCRTTest = schedule.WCRTTest();
			cout << "Schedulable using RM scheduling / WCRT test: " << (testData.rmWCRTTest?"Y":"N") << endl;
			cout << "Time Taken: " << (float)(clock() - ticksAtStart) / CLOCKS_PER_SEC << " seconds" << endl << endl;
			
			schedule.sortSJF();
			
			ticksAtStart = clock();
			testData.sjfWCRTTest = schedule.WCRTTest();
			cout << "Schedulable using SJF scheduling / WCRT test: " << (testData.sjfWCRTTest?"Y":"N") << endl;
			cout << "Time Taken: " << (float)(clock() - ticksAtStart) / CLOCKS_PER_SEC << " seconds" << endl << endl;
			//schedule.printTaskSet();
			
			schedule.sortMUF();
			
			ticksAtStart = clock();
			testData.mufWCRTTest = schedule.WCRTTest();
			cout << "Schedulable using MUF scheduling / WCRT test: " << (testData.mufWCRTTest?"Y":"N") << endl;
			cout << "Time Taken: " << (float)(clock() - ticksAtStart) / CLOCKS_PER_SEC << " seconds" << endl << endl;
			//schedule.printTaskSet();
			
			taskSet.clear();
			cout << endl;
			
			testResult->mData.push_back(testData);
			
			continue;
		}
		
		if (begin)
		{
			Task task;
		
			stringstream doublestream;
			doublestream << line;
			double f;
			
			doublestream >> f;
			task.mExecTime = f;
			
			doublestream >> f;
			task.mRelativeDeadline = f;
			
			doublestream >> f;
			task.mPeriod = f;
			
			taskSet.push_back(task);
			//cout << task.mExecTime << " " << task.mRelativeDeadline << " " << task.mPeriod << endl;
		}
		
    }

  	in.close();
  	
  	testResult->parseData();
  	testResult->writeData(testResultFile);
  	testResultFile.close();

	return 0;
}
