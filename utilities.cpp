#include "utilities.hpp"
#include "components.hpp"
#include <cmath>

// Global variable definition
std::vector<std::vector<double>> globalDxStates;

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
