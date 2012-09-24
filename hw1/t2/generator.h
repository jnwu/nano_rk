#ifndef GENERATOR_H
#define GENERATOR_H

#include <vector>
#include <string>

using namespace std;

class generator {

	public:
		

		generator();

		vector<double> generateUtilVector(double passedUtilRate, int passedN);
		vector<double> generatePeriod(int utilVecLength);
		vector<double> generateExec (vector<double> utilRate, vector<double> p);

		void outputFile (vector<double> e, vector<double> p, const char* fileName);
		
};

#endif
