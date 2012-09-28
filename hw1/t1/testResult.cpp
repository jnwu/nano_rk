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
	cout << "Number of task sets: " << this->mData.size() << endl;
	
	double rmNumTaskSetsSchedulable;
	double sjfNumTaskSetsSchedulable;
	double mufNumTaskSetsSchedulable;
	
	for (list<TestData>::iterator it = this->mData.begin(); it != this->mData.end(); it++)
	{
		if (it->rmLLTest == true || it->rmHBTest == true || it->rmWCRTTest)
			rmNumTaskSetsSchedulable++;
		
		if (it->sjfWCRTTest == true)
			sjfNumTaskSetsSchedulable++;
		
		if (it->mufWCRTTest == true)
			mufNumTaskSetsSchedulable++;		
	}
	
	this->rmPercentSchedulable = rmNumTaskSetsSchedulable / this->mData.size();
	this->sjfPercentSchedulable = sjfNumTaskSetsSchedulable / this->mData.size();
	this->mufPercentSchedulable = mufNumTaskSetsSchedulable / this->mData.size();
	
	cout << "Number of RM Test Passes: " << rmNumTaskSetsSchedulable << endl;
	cout << "Number of SJF Test Passes: " << sjfNumTaskSetsSchedulable << endl;
	cout << "Number of MUF Test Passes: " << mufNumTaskSetsSchedulable << endl;
}

void TestResult::writeData(ofstream& testResultFile)
{
	stringstream s;
	s << this->rmPercentSchedulable << ", " << this->sjfPercentSchedulable << ", " << this->mufPercentSchedulable << endl;
    
    testResultFile << s.str(); 
}
