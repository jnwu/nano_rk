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
			bool result;
			int ticksAtStart;
			
			begin = false;
			Scheduling schedule(taskSet);
			
			schedule.sortRM();
			
			ticksAtStart = clock();
			result = schedule.LLBoundTest();
			cout << "Schedulable using RM scheduling / Liu and Layland bound test: " << (result?"Y":"N") << endl;
			cout << "Time Taken: " << (float)(clock() - ticksAtStart) / CLOCKS_PER_SEC << " seconds" << endl << endl;
			
			ticksAtStart = clock();
			schedule.hyperbolicBoundTest();
			cout << "Schedulable using RM scheduling / Hyperbolic bound test: " << (result?"Y":"N") << endl;
			cout << "Time Taken: " << (float)(clock() - ticksAtStart) / CLOCKS_PER_SEC << " seconds" << endl << endl;

			
			ticksAtStart = clock();
			schedule.WCRTTest();
			cout << "Schedulable using RM scheduling / WCRT test: " << (result?"Y":"N") << endl;
			cout << "Time Taken: " << (float)(clock() - ticksAtStart) / CLOCKS_PER_SEC << " seconds" << endl << endl;

			
			schedule.sortSJF();
			
			ticksAtStart = clock();
			schedule.WCRTTest();
			cout << "Schedulable using SJF scheduling / WCRT test: " << (result?"Y":"N") << endl;
			cout << "Time Taken: " << (float)(clock() - ticksAtStart) / CLOCKS_PER_SEC << " seconds" << endl << endl;
			//schedule.printTaskSet();
			
			schedule.sortMUF();
			
			ticksAtStart = clock();
			schedule.WCRTTest();
			cout << "Schedulable using MUF scheduling / WCRT test: " << (result?"Y":"N") << endl;
			cout << "Time Taken: " << (float)(clock() - ticksAtStart) / CLOCKS_PER_SEC << " seconds" << endl << endl;
			//schedule.printTaskSet();
			
			taskSet.clear();
			cout << endl;
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

	return 0;
}
