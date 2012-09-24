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

vector<double> generator::generateUtilVector(double utilRate, int n){
	//srand(time(NULL));
	vector<double> r;
	double tmpRate =utilRate;
	double u;

	int y = n;
	for (int i = 0; i< y-1; i++){
		u = ((double)rand()/RAND_MAX) * (tmpRate/2);
		r.push_back(u);
		tmpRate -= u;
		
		
	}
	r.push_back(tmpRate);

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

