#include "activfunction.hpp"
#include <cmath>

void ActivFunction::activateArr(double (*funcptr)(double x), double arr[], int size) {

    for (int i = 0; i < size; i++) {
        arr[i] = funcptr(arr[i]);
    }

}

double ActivFunction::sigmoid(double x) {
    return 1 / ( 1 + exp(-x) ); 
}

double ActivFunction::sigm(double x) {
    return x / (1 + abs(x)); 
}

double ActivFunction::relu(double x) {
    return (x > 0 ? x : 0);
}

double ActivFunction::lkrelu(double x) {
    return (x > 0 ? x : 0.01*x);
}