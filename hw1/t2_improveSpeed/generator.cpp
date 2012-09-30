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


vector< vector<double> > generator::generateVectorSpace() {
	vector<double>* r = NULL;
	vector< vector<double> > vs;

	for (int i = 0; i<SAMPLE_SIZE; i++){	
		r = new vector<double>();
		double u = 0.0;

		for(int j=0; j<MAX_VECTOR_SIZE; j++) {
			u = ((double)rand()/RAND_MAX) * (1.00);
			r->push_back(u);
		}
		
		vs.push_back(*r);
	}

	return vs;
}


vector<double> generator::generateUtilVector(vector< vector<double> > vs, double utilRate, int vectorSize) {
	vector<double> r;
	double sum = 0.0;
	int n = ((double)rand()/RAND_MAX) * (vs.size());
	
	for(int i=0 ; i<vectorSize ; i++) {
		r.push_back(vs.at(n).at(i));
		sum += r.at(i);
	}

	for(int i=0 ; i<r.size() ; i++) 
		r.at(i) = r.at(i) * (utilRate/sum);	// Scale utilization rate
	return r;
}

double generator::uniRandom(int lower, int upper){
	int x, y, n;
	double e;
	n = (int)( (upper - lower)/0.01 )+ 1;
	x = rand();
	y = (x%n) + 100;
	e = y / 100.00;
	return e;
}

vector<double> generator::generatePeriod(int utilVecLength,int lower,int upper){
	vector<double> r;

	double e;

	for (int i = 0; i<utilVecLength; i++){
		 e = this->uniRandom(lower, upper);
		r.push_back(pow(10,e));
	}
	
	return r;
}

vector<double> generator::generateExec (vector<double> utilRate, vector<double> p){
	vector<double> e;
	for (int i = 0; i<utilRate.size(); i++){
		e.push_back(utilRate.at(i) * p.at(i));
	}
	
	return e;
}

void generator::outputFile (vector<double> e, vector<double> p, const char* fileName){
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

