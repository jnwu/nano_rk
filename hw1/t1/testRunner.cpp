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
			begin = false;
			Scheduling schedule(taskSet);
			
			schedule.sortRM();
			result = schedule.LLBoundTest();
			
			cout << "Schedulable using RM scheduling / Liu and Layland bound test: " << (result?"Y":"N") << endl;
			
			schedule.hyperbolicBoundTest();
			cout << "Schedulable using RM scheduling / Hyperbolic bound test: " << (result?"Y":"N") << endl;
			
			schedule.WCRTTest();
			cout << "Schedulable using RM scheduling / WCRT test: " << (result?"Y":"N") << endl;
			
			schedule.sortSJF();
			schedule.WCRTTest();
			cout << "Schedulable using SJF scheduling / WCRT test: " << (result?"Y":"N") << endl;
			//schedule.printTaskSet();
			
			schedule.sortMUF();
			schedule.WCRTTest();
			cout << "Schedulable using MUF scheduling / WCRT test: " << (result?"Y":"N") << endl;
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
