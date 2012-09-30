#ifndef GENERATOR_H
#define GENERATOR_H

#include <vector>
#include <string>

using namespace std;

class generator {

	public:
		generator();
		
		double uniRandom(int lower, int upper);

		vector< vector<double> > generateVectorSpace();
		vector<double> generateUtilVector(vector< vector<double> > vs, double utilRate, int vectorSize);
		vector<double> generatePeriod(int utilVecLength,int lower, int upper);
		vector<double> generateExec (vector<double> utilRate, vector<double> p);

		void outputFile (vector<vector<double> > es, vector<vector<double> > ps, const char* fileName);
		
};

#endif
