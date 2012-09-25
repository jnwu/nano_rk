#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#include "generator.h"


using namespace std;

generator::generator(){
	
}


vector< vector<double> > generator::generateVectorSpace(double utilRate, int nSample, int nTask) {
	vector<double>* r = NULL;
	vector< vector<double> > vs;

	for (int i = 0; i<nSample; i++){	
		double u;
		double tmpRate = utilRate;

		r = new vector<double>();
		for(int i = 0; i<nTask ; i++) 
			r->push_back(0);

		for(int i=0; i<nTask; i++) {
			if(i == (nTask-1)) {
				r->at(i) = tmpRate;
				break;
			}

			u = ((double)rand()/RAND_MAX) * (tmpRate/3);
			if(u < 1e-4) continue;		// Bound minimum rate 
			r->at(i) = u;

			tmpRate -= u;
		}
		
		vs.push_back(*r);
	}

	return vs;
}


vector<double> generator::generateUtilVector(vector< vector<double> > vs) {
	vector<double> r;
	int n = ((double)rand()/RAND_MAX) * (vs.size());
	
	for(int i = 0 ; i < vs.at(n).size() ; i++) 
		r.push_back(vs.at(n).at(i));
	
	return r;
}

vector<double> generator::generatePeriod(int utilVecLength){
	vector<double> r;
	int x, y;
	double e;
	//srand(time(NULL));
	for (int i = 0; i<utilVecLength; i++){
		 x = rand();
		 y = (x%101) * 5 + 100;
		 e = y / 100.00;
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
	myfile << "<begin task set>\n";
	myfile<<"\n";
  	myfile.close();
}

