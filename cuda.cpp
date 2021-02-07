#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define R 2
#define LAYERDIM   32

__device__ __forceinline__ double sigmoid (double a)
{
    return 1.0 / (1.0 + exp (-a));
}

__global__ void sigmoid_kernel (double weigths[], float bias, double layer[], int lengthLayer, int idLayer, double* nextLayer)
{
	int step = R;
	int start = blockIdx.x*R;  
	float value = 0;
	int end = (blockIdx.x + 1)*R;
	for (int b = start; b<end; b += 1) {
        value += weigths[b]*layer[b];
    	cout << weigths[b] << " WEIGHT " << layer[b+i] << " INPUT " << bias << "\n";
    }
    value += bias;
    cout << value << " VALUE\n"; 
    nextLayer[blockIdx.x] = activationFunction(value);
    cout << nextLayer[blockIdx.x] << " NEXT LAYER " << " \n";
}  

int main(void){
	double weights1[LAYERDIM];
	for (int i = 0; i < LAYERDIM; i++){
		weights1[i] =static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		cout << weights1[i] << '\n';
	}
	double layer[LAYERDIM];
	for (int i = 0; i < LAYERDIM; i++){
		layer[i] =static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		cout << layer[i] << '\n';
	}
    float bias = 0.1;
    int lengthLayer = LAYERDIM;
    int idLayer = 0;
    double *d_a = 0, *d_b = 0;
    int numBlock = lengthLayer/R;
    int numThread = R;
    double* nextLayer = new double[lengthLayer/R];

    cudaMalloc((void**)&d_a, sizeof(d_a[0]) * lengthLayer);
    cudaMalloc((void**)&d_b, sizeof(d_b[0]) * lenghtLayer);

    /* Push source data to device */
    cudaMemcpy (d_a, source, sizeof(d_a[0]) * lenghtLayer, cudaMemcpyHostToDevice);

    /* Compute execution configuration */
    dim3 dimBlock(256);
    int threadBlocks = (lenghtLayer + (dimBlock.x - 1)) / dimBlock.x;
    if (threadBlocks > 65520) threadBlocks = 65520;
    dim3 dimGrid(threadBlocks);

    sigmoid_kernel<<<numBlock,numThread>>>(weights, bias, layer, lengthLayer, idLayer, nextLayer);
    cudaMemcpy (result, d_b, sizeof (result[0]) * lenghtLayer,
                                cudaMemcpyDeviceToHost);
    
    cudaFree(d_a);
    cudaFree(d_b);
    free (result);
    free (source);
    return 0;
}
