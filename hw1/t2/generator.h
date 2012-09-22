#ifndef GENERATOR_H
#define GENERATOR_H

#include <vector>

using namespace std;

class generator {

	public:
		double utilRate;

		generator(double passedUtilRate);

		vector<double> generateUtilVector();
		vector<double> generatePeriod(int utilVecLength);
		vector<double> generateExec (vector<double> utilRate, vector<double> p);

		void outputFile (vector<double> e, vector<double> p);
		
};

#endif
