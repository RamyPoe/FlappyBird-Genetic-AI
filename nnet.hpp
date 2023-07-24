#ifndef NNET_H
#define NNET_H

#include "constants.hpp"
#include "nlayer.hpp"
#include "activfunction.hpp"
#include <set>

using std::set;

/*

2 input -> 5 hidden -> 1 output

*/

class NNet {

private:
    // Changes some of the weights to a new random value
    static void mutateArray(double weights[], int size);

    // Mixes the weights of two into another array
    static void mixArray(double w1[], double w2[], double o[], int size);

    // For picking random weights
    static inline set<int>* numSet = new set<int>;

public:
    // Define the layers
    NLayer* layers;

    // Number of layers
    short numLayers;

    // Activation functions
    ActivFunction* activation;

    // Constructor
    NNet(const short layers_[], const short numLayers);

    // Propogate entire network
    double* forward(double input[]);

    // Genetic algorithm
    void modifyWeightsRandom();
    void mixWeights(const NNet& n1, const NNet& n2);

};

#endif