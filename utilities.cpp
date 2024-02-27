#include "utilities.hpp"
#include "components.hpp"
#include <cmath>
#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <algorithm>


// Global variable definition
std::vector<std::vector<double>> globalDxStates;



void testEnergyConservation(const std::vector<std::vector<double>>& stateHistory, const SystemParams& params, double tStart, double tStop, double tMajorStep, double maxEnergyImbalance, double maxEnergyTrendImbalance) {
    // Calculate the total mechanical energy of the system
    std::vector<double> totalMechanicalEnergy;
    calculateTotalMechanicalEnergy(stateHistory, params.springStiffness, params.trolleyMass, params.pendulumMass, params.rodLength, 9.81, totalMechanicalEnergy);
    
    double minEnergy = *std::min_element(totalMechanicalEnergy.begin(), totalMechanicalEnergy.end());
    double maxEnergy = *std::max_element(totalMechanicalEnergy.begin(), totalMechanicalEnergy.end());
    double energyDifference = maxEnergy - minEnergy;
    
    int windowSize = (tStop - tStart) / (6 * tMajorStep);
    std::vector<double> energyMovingAvg = movingAverage(totalMechanicalEnergy, windowSize);
    double firstValue = energyMovingAvg.front();
    double lastValue = energyMovingAvg.back();
    double differenceAvg = lastValue - firstValue;
    
    std::cout << "Energy Difference Average: " << differenceAvg << std::endl;
    
    if (energyDifference > maxEnergyImbalance) {
        std::cout << "\nThe simulation results FAILED the Max Energy Imbalance Criteria. \nMax Difference: " << energyDifference << " > Tolerance: " << maxEnergyImbalance << std::endl;
        std::cout << "It is recommended to reduce Step Size or check model properties.\n" << std::endl;
    }
    
    if (differenceAvg > maxEnergyTrendImbalance) {
        std::cout << "\nThe simulation results FAILED the Energy Trend Imbalance Criteria. \nTotal Trend Difference: " << differenceAvg << " > Tolerance: " << maxEnergyTrendImbalance << std::endl;
        std::cout << "It is recommended to reduce Step Size or check model properties.\n" << std::endl;
    }
    
    if (differenceAvg < maxEnergyTrendImbalance && energyDifference < maxEnergyImbalance) {
        std::cout << "\nSimulation successful. It satisfies all of the energy conservation criteria.\n" << std::endl;
    }
    
    // Write the total mechanical energy to a file
    std::ofstream energyFile("C:/Users/mateu/Desktop/Canopy/TrolleyAndPendulum/total_mechanical_energy.csv");
    if (energyFile.is_open()) {
        energyFile << "Time,Total Mechanical Energy,Moving Average\n";
        double tCurrent = tStart;
        for (size_t i = 0; i < totalMechanicalEnergy.size(); ++i) {
            energyFile << tCurrent << "," << totalMechanicalEnergy[i] << "," << energyMovingAvg[i] << "\n";
            tCurrent += tMajorStep;
        }
        energyFile.close();
        std::cout << "Total mechanical energy data exported to total_mechanical_energy.csv\n";
    } else {
        std::cerr << "Error opening file for writing.\n";
    }
}

// Function to calculate the total mechanical energy of the system
void calculateTotalMechanicalEnergy(const std::vector<std::vector<double>>& stateHistory, double springStiffness, double trolleyMass, double pendulumMass, double rodLength, double gravity, std::vector<double>& totalMechanicalEnergy) {
    for (const auto& state : stateHistory) {
        double trolleyPosition = state[0];
        double pendulumAngle = state[1];
        double trolleyVelocity = state[2];
        double pendulumAngVelocity = state[3];

        double Ttotal = 0.5 * (trolleyMass + pendulumMass) * trolleyVelocity * trolleyVelocity +
                        0.5 * pendulumMass * rodLength * rodLength * pendulumAngVelocity * pendulumAngVelocity +
                        pendulumMass * rodLength * std::cos(pendulumAngle) * trolleyVelocity * pendulumAngVelocity;

        double Vtotal = 0.5 * springStiffness * trolleyPosition * trolleyPosition - pendulumMass * gravity * std::cos(pendulumAngle);

        double E = Ttotal + Vtotal;
        totalMechanicalEnergy.push_back(E);
    }
}

// Function to calculate the moving average of a vector
std::vector<double> movingAverage(const std::vector<double>& data, int windowSize) {
    std::vector<double> movingAvg;
    double sum = 0.0;

    for (int i = 0; i < data.size(); ++i) {
    sum += data[i];
    if (i >= windowSize) {
        sum -= data[i - windowSize];
    }
    int divisor = std::min(i + 1, windowSize); // Use the smaller of i + 1 or windowSize
    movingAvg.push_back(sum / divisor);
    }

    return movingAvg;
}

// Definition of the physics function that calculates the derivatives of the state variables
void physicsFunction(std::vector<double>& dxState, const std::vector<double>& xState, void* userArgs) {
    
    // Components Instantiation
    Spring spring;
    Trolley trolley;
    Pendulum pendulum;

    // Constants
    const double gravity = 9.81;  

    // Use the parameters from userArgs
    // Extract system parameters from userArgs

    auto* params = static_cast<SystemParams*>(userArgs);
    const double springStiffness = params->springStiffness;
    const double trolleyMass = params->trolleyMass;
    const double pendulumMass = params->pendulumMass;
    const double rodLength = params->rodLength;  

    // State variables
    const double trolleyPosition = xState[0];  
    const double pendulumAngle = xState[1];  
    const double trolleyVelocity = xState[2];  
    const double pendulumAngVelocity = xState[3];  

    // Equations of Motion
    double trolleyAcc = (-pendulumMass * rodLength * std::cos(pendulumAngle) * dxState[3] + pendulumMass * rodLength * std::sin(pendulumAngle)
    * pendulumAngVelocity * pendulumAngVelocity - springStiffness * trolleyPosition) / (trolleyMass + pendulumMass);

    double rodAngularAcc = (-std::cos(pendulumAngle) * trolleyAcc - gravity * std::sin(pendulumAngle)) / rodLength;

    // Update derivatives
    dxState[0] = trolleyVelocity;  // Derivative of position is velocity
    dxState[1] = pendulumAngVelocity;  // Derivative of angle is angular velocity
    dxState[2] = trolleyAcc;  // Derivative of velocity is acceleration
    dxState[3] = rodAngularAcc;  // Derivative of angular velocity is angular acceleration

   // Store the current derivatives in the global variable
    globalDxStates.push_back(dxState);
}
