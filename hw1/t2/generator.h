#ifndef GENERATOR_H
#define GENERATOR_H

#include <vector>
#include <string>

using namespace std;

class generator {

	public:
		generator();

		vector< vector<double> > generateVectorSpace(double utilRate, int nSample, int nTask);
		vector<double> generateUtilVector(vector< vector<double> > vs);
		vector<double> generatePeriod(int utilVecLength);
		vector<double> generateExec (vector<double> utilRate, vector<double> p);

		void outputFile (vector<double> e, vector<double> p, const char* fileName);
		
};

#endif
