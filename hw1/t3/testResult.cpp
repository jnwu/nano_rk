#include "testResult.h"

using namespace std;

TestResult::TestResult()
{
	this->rmPercentSchedulable = 0;
	this->sjfPercentSchedulable = 0;
	this->mufPercentSchedulable = 0;
}

void TestResult::parseData()
{
	double rmNumTaskSetsSchedulable;
	double sjfNumTaskSetsSchedulable;
	double mufNumTaskSetsSchedulable;
	
	for (list<TestData>::iterator it = this->mData.begin(); it != this->mData.end(); it++)
	{
		if (it->rmTest)
			rmNumTaskSetsSchedulable++;
		
		if (it->sjfTest)
			sjfNumTaskSetsSchedulable++;
		
		if (it->mufTest)
			mufNumTaskSetsSchedulable++;		
	}
	
	this->rmPercentSchedulable = rmNumTaskSetsSchedulable / this->mData.size();
	this->sjfPercentSchedulable = sjfNumTaskSetsSchedulable / this->mData.size();
	this->mufPercentSchedulable = mufNumTaskSetsSchedulable / this->mData.size();
}

void TestResult::writeData(ofstream& testResultFile)
{
	stringstream s;
	s << this->rmPercentSchedulable << ", " << this->sjfPercentSchedulable << ", " << this->mufPercentSchedulable << endl;
    
    testResultFile << s.str(); 
}
