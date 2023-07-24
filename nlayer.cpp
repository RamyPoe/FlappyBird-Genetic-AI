#include "nlayer.hpp"
#include <cstdlib>
#include <iostream>

NLayer::NLayer(int _inputs, int _neurons) {
    inputs = _inputs;
    neurons = _neurons;

    // 2D Array
    weights = (double*) malloc( sizeof(double) * inputs * neurons );
    if (!weights) { std::cout << "MEMORY ALLOCATION FAILED" << std::endl; exit(1); }

    // Output for each neuron
    output = (double*) malloc( sizeof(double) * neurons );
    if (!output) { std::cout << "MEMORY ALLOCATION FAILED" << std::endl; exit(1); }

    // Fill random weights
    NLayer::fillRandomWeights();
}

void NLayer::fillRandomWeights() {

    // For every index
    for (int i = 0; i < inputs * neurons; i++) {

        // Value from -0.5 < x < 0.5
        // weights[i] = (double) rand() / RAND_MAX - 0.5;
        weights[i] = 0;

    }

}

// Length of input array should be same as specified in constructor
void NLayer::forward(double input[]) {


    // Matrix dot product
    for (int i = 0; i < neurons; i++) {

        double temp = 0;
        for (int j = 0; j < inputs; j++) {
            temp += weights[i*inputs + j] * input[j];
        }

        // Add result to output array
        output[i] = temp;

    }

}