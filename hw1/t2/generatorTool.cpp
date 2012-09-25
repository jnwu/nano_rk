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
	vector< vector<double> > vs;
	vector<double> u; 	
	vector<double> p;
	vector<double> e;
	generator g;
	string fileName;
	double uRate;
	int n;
	srand(time(NULL));



	cout << "Generate Task Sets for T3.1" << endl;
	// Rate
	for (int i = 1; i<=20; i++){
		uRate = 0.05*i;

		// Task Size
		for (int j = 3; j<=6; j++){
			n = pow(2,j);
			fileName = getFileName(uRate, n, "inputFile1");
			vs = g.generateVectorSpace(uRate, 1250, n);

			cout << "utilRate: " << uRate << "\tnTask: " << n << endl;
			// Task Set
			for (int k = 0; k<1250; k++){	

				u = g.generateUtilVector(vs);
				p = g.generatePeriod(u.size(), 1, 6);
				e = g.generateExec(u, p);
				g.outputFile(e,p, fileName.c_str());
			}
		}
	}
	cout << endl;

	cout << "Generate Task Sets for T3.2" << endl;
	for (int i = 1; i<=9; i++){
		uRate = 0.1*i;
	  	fileName = getFileName(uRate, 16, "inputFile2");
		vs = g.generateVectorSpace(uRate, 100, 16);
		
		cout << "utilRate: " << uRate << endl;
		for (int k = 0; k<100; k++){	
			u = g.generateUtilVector(vs);
			p = g.generatePeriod(u.size(), 1,5);
			e = g.generateExec(u, p);
			g.outputFile(e,p, fileName.c_str());
		}
	}
}


