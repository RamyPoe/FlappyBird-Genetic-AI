#ifndef ACTIVFUNCTION_H
#define ACTIVFUNCTION_H

class ActivFunction {


public:
    // Apply function to each element
    void activateArr(double (*funcptr)(double x), double arr[], int size);

    // Functions to apply
    static double sigmoid(double x);
    static double sigm(double x);
    static double relu(double x);
    static double lkrelu(double x);

};


#endif