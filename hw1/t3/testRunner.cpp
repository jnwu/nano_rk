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
#include "simulator.h"

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
	
	TestResult testResult;
	
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
			Simulator simulator(taskSet);
			
			simulator.sortRM();
			
			ticksAtStart = clock();
			
			bool simulationResult = simulator.simulate();
			
			cout << "Simulation result = " << (simulationResult?"Success":"Fail") << endl;
			cout << "Time Taken: " << (float)(clock() - ticksAtStart) / CLOCKS_PER_SEC << " seconds" << endl << endl;
			
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
  	
  	//testResult.parseData();
  	//testResult.writeData(testResultFile);
  	//testResultFile.close();

	return 0;
}
