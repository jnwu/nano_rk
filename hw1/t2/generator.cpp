/*
* EECE 494 Programming Assignment #1
* generator.cpp
*
*/


#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#include "generator.h"

#define SAMPLE_SIZE 100000
#define MAX_VECTOR_SIZE 64

using namespace std;

generator::generator(){}

/*
* generate the utilization vector space
*/
vector< vector<double> > generator::generateVectorSpace() {
	vector<double>* r = NULL;
	vector< vector<double> > vs;

	// Set the vector space size to 100,000
	for (int i = 0; i<SAMPLE_SIZE; i++){	
		r = new vector<double>();
		double u = 0.0;

		// Per vector, set max vector size to 64
		for(int j=0; j<MAX_VECTOR_SIZE; j++) { 
			u = ((double)rand()/RAND_MAX) * (1.00);
			r->push_back(u);
		}
		
		vs.push_back(*r);
	}

	return vs;
}

/*
* pseudo-randomly picks a vector in the vector space
*/
vector<double> generator::generateUtilVector(vector< vector<double> >& vs, double utilRate, int vectorSize) {
	vector<double> r;
	double sum = 0.0;
	int n = ((double)rand()/RAND_MAX) * (vs.size());
	
	// Extract values from the selected vector
	for(int i=0 ; i<vectorSize ; i++) {
		r.push_back(vs.at(n).at(i));
		sum += r.at(i);
	}

	// Scale utilization rate to the provided utilRate
	for(int i=0 ; i<r.size() ; i++) 
		r.at(i) = r.at(i) * (utilRate/sum);	
		
	return r;
}

/*
* generate a uniform random number between lower and upper bounds
*/ 
double generator::uniRandom(int lower, int upper){
	int x, y, n;
	double e;
	n = (int)( (upper - lower)/0.01 )+ 1;
	x = rand();
	y = (x%n) + 100;
	e = y / 100.00;
	return e;
}

/*
* generate log-uniformly distributed period for the utilization vector
*/
vector<double> generator::generatePeriod(int utilVecLength, int lower, int upper){
	vector<double> r;
	double e;

	for (int i = 0; i<utilVecLength; i++){
		 e = this->uniRandom(lower, upper);
		r.push_back(pow(10,e));
	}
	
	return r;
}

/*
* generate execution time for the utilization and period vectors
*/
vector<double> generator::generateExec (vector<double>& utilRate, vector<double>& p){
	vector<double> e;
	for (int i = 0; i<utilRate.size(); i++){
		e.push_back(utilRate.at(i) * p.at(i));
	}
	
	return e;
}

/*
* output task sets
*/ 
void generator::outputFile (vector<double>& e, vector<double>& p, const char* fileName){
	ofstream myfile;
  	myfile.open (fileName,ios_base::app);
        myfile << "<begin task set>\n";
	for (int i =0; i< e.size();i++){
		myfile << e.at(i) << " " << p.at(i)<< " "<< p.at(i)<<endl;
	}
	myfile << "<end task set>\n";
	myfile<<"\n";
  	myfile.close();
}

