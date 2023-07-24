#ifndef NLAYER_HPP
#define NLAYER_HPP

class NLayer {

private:
    // For initializing weights
    void fillRandomWeights();
    
public:
    // Array sizes
    int inputs;
    int neurons;
    
    // Array pointer (-0.5 < weight < 0.5)
    double* weights;
    // Array pointer
    double* output;

    // Constructor
    NLayer(int inputs, int neurons);

    // Propogate inputs through layer
    void forward(double input[]);

};


#endif