#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <vector>

// Define a global variable to store the derivatives to export results
extern std::vector<std::vector<double>> globalDxStates;  // Extern declaration

struct SystemParams {
    double springStiffness;
    double trolleyMass;
    double pendulumMass;
    double rodLength;
};

void physicsFunction(std::vector<double>& dxState, const std::vector<double>& xState, void* userArgs);

#endif // UTILITIES_HPP
