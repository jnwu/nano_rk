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
		if (it->rmLL == true || it->rmHB == true || it->rmWCRT)
			rmNumTaskSetsSchedulable++;
		
		if (it->sjfWCRT == true)
			sjfNumTaskSetsSchedulable++;
		
		if (it->mufWCRT == true)
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
