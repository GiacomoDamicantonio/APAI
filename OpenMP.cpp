#include <stdio.h>
#include <iostream>
#include <math.h>
#include <fstream>
#include <omp.h>
#include <stdlib.h>

#define R 3
#define LAYERDIM 32
using namespace std;

inline double activationFunction( double x )
{
	return 1/(1+exp(-x));
}	

double* feedForward(double weigths[9], float bias, double layer[], int lengthLayer) 
{
    int step = R;
    double* nextLayer = new double[lengthLayer/R];
	int j = 0;
	
	#pragma omp parallel for
	for (int b = 0; b<lengthLayer; b += step) {
	    float value = 0;
		for(int i = 0; i < R; i++) { 
            value += weigths[b+i]*layer[b+i];
			cout << weigths[b+i] << " WEIGHT " << layer[b+i] << " INPUT " << bias << "\n";
        }
        value += bias;
        cout << value << " VALUE\n"; 
        nextLayer[j] = activationFunction(value);
        cout << nextLayer[j] << " NEXT LAYER " << j << " \n";
    	j += 1;
	}
    return nextLayer;
}

int main(void)
{
	double weights[LAYERDIM];
	for (int i = 0; i < LAYERDIM; i++){
		weights[i] =static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		cout << weights[i] << '\n';
	}
	double layer[LAYERDIM];
	for (int i = 0; i < LAYERDIM; i++){
		layer[i] =static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		cout << layer[i] << '\n';
	}
    float bias = 0.1;
    int lengthLayer = LAYERDIM;
    int idLayer = 0;

    double* val = feedForward(weights, bias, layer, lengthLayer);

    ofstream myfile ("C:/Users/damic/Desktop/example.txt");
    if (myfile.is_open())
    {
        for (int i = 0; i < lengthLayer/R; i++){
            myfile << val[i] << "\n";
            cout << val[i] << "\n";
        } 
        myfile.close();
    }
    else printf("UNABLE TO OPEN FILE");

    return 0;
}
