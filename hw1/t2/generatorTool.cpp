/**
this is the main function for generating the fileinput
*/

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <math.h>
#include "generator.h"

string getFileName(double uRate, int n, string s);

string getFileName(double uRate, int n, string s){
   stringstream ss;
   ss <<"+"<<uRate <<"+"<<n;
   return s.append(ss.str());
}

int main (){

	//utilRate = getUtilRate();
	vector<double> u; 	
	vector<double> p;
	vector<double> e;
	generator g;
	string fileName;
	double uRate;
	int n;
	srand(time(NULL));

for (int i = 1; i<=20; i++){
	uRate = 0.05*i;
	for (int j = 3; j<=6; j++){
		n = pow(2,j);
		fileName = getFileName(uRate, n, "inputFile1");
	for (int k = 0; k<100000; k++){	
		u = g.generateUtilVector(uRate,n);
		p = g.generatePeriod(u.size());
		e = g.generateExec(u, p);
		g.outputFile(e,p, fileName.c_str());
	
	}
   }

}

	for (int i = 1; i<=9; i++){
	  uRate = 0.1*i;
	  fileName = getFileName(uRate, 16, "inputFile2");
	for (int k = 0; k<100; k++){	
		u = g.generateUtilVector(uRate,16);
		p = g.generatePeriod(u.size());
		e = g.generateExec(u, p);
		g.outputFile(e,p, fileName.c_str());
	
	    }
   

	}
	
}


