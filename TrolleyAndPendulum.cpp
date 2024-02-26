#include "components.hpp"
#include "odesolver.hpp"
#include "utilities.hpp"
#include <cmath>
#include <vector>
#include <fstream>
#include <iostream>


int main() {

    // Time settings
    const double tStart = 0;
    const double tStop = 5;
    const double tMajorStep = 1e-4;
    const int numSteps = static_cast<int>((tStop - tStart) / tMajorStep) + 1;

    // Instantiate the system components
    Spring spring;
    Trolley trolley;
    Pendulum pendulum;

    // Use getters to extract parameters
    SystemParams params{
        spring.get_kSpring(),
        trolley.get_mTrolley(),
        pendulum.get_mPendulum(),
        pendulum.get_lPendulum()
    };
    
    // Initialize the global variable with the correct size
    globalDxStates.reserve(numSteps);

    // Initial conditions
    std::vector<double> x0 = {0.02, 0.0, 0.0, 0.0};  // xTrolley, pendulumAnglePendulum, dxTrolley, dpendulumAnglePendulum

    // Initialize the matrix of derivatives (dxStates)
    std::vector<std::vector<double>> dxStates(numSteps, std::vector<double>(4, 0.0));

    // Solve the system dynamics
    auto solution = solveMidpointMethod(tStart, tStop, tMajorStep, x0, physicsFunction, &params);

    // Initialize state history vector
    std::vector<std::vector<double>> stateHistory(numSteps, std::vector<double>(4, 0.0));

    // Store the solution in the state history vector
    for (size_t i = 0; i < solution.size(); ++i) {
        for (size_t j = 0; j < solution[i].size(); ++j) {
            stateHistory[j][i] = solution[i][j];
        }
    }

    // Open a file for writing
    std::ofstream outFile("C:/Users/mateu/Desktop/Canopy/non-linear-dynamics-ckdoqt/derivatives.csv");

    // Check if the file is open
    if (outFile.is_open()) {
        // Write the header
        outFile << "Time,Trolley Acceleration,Pendulum Angular Acceleration\n";

        // Write the data
        double tCurrent = tStart;
        for (size_t i = 0; i < numSteps; ++i) {
            if (i < globalDxStates.size()) {
                outFile << tCurrent << "," << globalDxStates[i][2] << "," << globalDxStates[i][3] << "\n";
            } else {
                // In case globalDxStates has fewer entries than numSteps
                outFile << tCurrent << ",0,0\n";
            }
            tCurrent += tMajorStep;
        }
        outFile.close();
        std::cout << "Derivatives data exported to derivatives.csv\n";
    } else {
        std::cerr << "Error opening file for writing.\n";
    }

    return 0;
}


