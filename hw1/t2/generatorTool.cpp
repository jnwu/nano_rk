/**
this is the main function for generating the fileinput
*/

#include <iostream>
#include <vector>
#include "generator.h"

//this function is here for testing purpose.
double getUtilRate();

//this function is here temporarily for testing purpose
vector<double> genU(double utilRate);

int main (){

	double utilRate;
	utilRate = getUtilRate();
	vector<double> u; 	//u is being hard coded for now
	vector<double> p;
	vector<double> e;
	generator g(utilRate);
	u = genU(utilRate);
	p = g.generatePeriod(u.size());
	e = g.generateExec(u, p);
	g.outputFile(e,p);
	
	
}

//test
double getUtilRate(){
	double r;
	cout<<"enter the util rate between 0 and 1: "<<endl;
	cin>>r;
	return r;
}

vector<double> genU(double util){
	vector<double> u;
	int n;
	cout<<"please enter n for the size of vector: "<<endl; 
	cin >> n;
	cout<<"make sure the sum equals to "<<util<<endl;
	for (int i=0; i<n; i++){
		double rate;
		cout<<"please enter U "<<i<<endl;
		cin >>rate;
		u.push_back(rate);
	}
	return u;
}
