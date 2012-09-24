#ifndef TESTRESULT_H
#define TESTRESULT_H

#include <list>
#include <iostream>
#include <sstream>
#include <fstream>
#include "structs.h"

using namespace std;

class TestResult {

	public:
		list<TestData> mData;
		double rmPercentSchedulable;
		double sjfPercentSchedulable;
		double mufPercentSchedulable;
		
		TestResult();
		void parseData();
		void writeData(ofstream& testResultFile);
};

#endif