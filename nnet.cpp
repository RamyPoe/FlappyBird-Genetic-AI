#include "nnet.hpp"
#include "constants.hpp"
#include "nlayer.hpp"
#include "activfunction.hpp"
#include <cstdlib>
#include <set>
#include <iostream>

using std::set;



// Constructor
NNet::NNet(const short layers_[], const short layers_len) {

    // Input error
    if (layers_len < 2) {
        throw std::invalid_argument("NNet constructor argument must define at least two layers!");
    }

    // Save number of layers
    numLayers = layers_len-1;

    // Allocate for all layers
    layers = (NLayer*) malloc(sizeof(NLayer) * (numLayers));

    // Create layers
    for (int i = 0; i < numLayers; i++) {
        layers[i] = NLayer(layers_[i], layers_[i+1]);
    }

    // Activation functions
    activation = new ActivFunction();

}

// Propogate entire network and return output layer
double* NNet::forward(double input[]) {

    layers[0].forward(input);
    activation->activateArr(ActivFunction::sigm, layers[0].output, layers[0].neurons);
    for (short i = 1; i < numLayers; i++) {
        layers[i].forward(layers[i-1].output);
        activation->activateArr(ActivFunction::sigm, layers[i].output, layers[i].neurons);
    }
    
    return layers[numLayers-1].output;

}

//---------------------------------------
/* GENETIC ALGORITHMS */
//---------------------------------------

void NNet::modifyWeightsRandom() {

    for (short i = 0; i < numLayers; i++) {
        NNet::mutateArray(
            layers[i].weights,
            layers[i].neurons * layers[i].inputs
        );
    }

}

void NNet::mutateArray(double weights[], int size) {

    for (int i = 0; i < size; i++) {
        if (((double) rand()/RAND_MAX) < Constants::Genetic::MUTATION_WEIGHT_MODIFY_CHANCE) {
            weights[i] = (double) rand() / RAND_MAX - 0.5;
        }
    }

}


void NNet::mixWeights(const NNet& n1, const NNet& n2) {

    for (short i = 0; i < numLayers; i++) {
        NNet::mixArray(
            n1.layers[i].weights,
            n2.layers[i].weights,
            layers[i].weights,
            layers[i].neurons * layers[i].inputs
        );
    }

}

void NNet::mixArray(double w1[], double w2[], double o[], int size) {

    // Num elements to take
    int numTake = size * Constants::Genetic::MUTATION_MIX_PERC;

    // Pick elements to take
    numSet->clear();
    while (numSet->size() < numTake) {
        numSet->insert(rand() % size);
    }

    // Choose from different onto the output
    for (int i = 0; i < size; i++) {
        o[i] = (numSet->count(i) ? w2[i] : w1[i]);
    }

}