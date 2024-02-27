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
void calculateTotalMechanicalEnergy(const std::vector<std::vector<double>>& stateHistory, double springStiffness, double trolleyMass, double pendulumMass, double rodLength, double gravity, std::vector<double>& totalMechanicalEnergy);
void testEnergyConservation(const std::vector<std::vector<double>>& stateHistory, const SystemParams& params, double tStart, double tStop, double tMajorStep, double maxEnergyImbalance, double maxEnergyTrendImbalance);
std::vector<double> movingAverage(const std::vector<double>& data, int windowSize);


#endif // UTILITIES_HPP
