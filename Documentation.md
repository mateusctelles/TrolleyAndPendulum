# Trolley and Pendulum Simulation

## Overview

This project simulates the dynamics of a system consisting of a trolley connected to a fixed base via a spring, with a pendulum rigidly attached to the trolley. The simulation aims to provide insights into the behavior of the system under various conditions and to validate energy conservation principles.

<p align="center">
  <img src="https://github.com/mateusctelles/TrolleyAndPendulum/blob/main/images/trolleyandpendulum.png?raw=true" alt="trolleyandpendulum" width="300"/>
  <img src="https://github.com/mateusctelles/TrolleyAndPendulum/blob/main/images/final_gif.gif?raw=true" alt="final_gif" width="300"/>
  <img src="https://github.com/mateusctelles/TrolleyAndPendulum/blob/main/images/ZeroStiffness.gif?raw=true" alt="ZeroStiffness" width="300"/>
  
           Figure 2 and 3: Plots and results from the code made in Matlab, using the prototype code before building it into C++
</p>





### Key Features

- **Dynamic Simulation:** The core of the project is the simulation of the trolley and pendulum system, which is implemented using numerical integration methods to solve the equations of motion.

- **Energy Conservation Analysis:** The simulation includes a detailed analysis of the mechanical energy of the system, enabling the user to assess if the energy is conserved within a specified tolerance.

- **Parameter Tuning:** Users can easily modify system parameters such as mass, spring stiffness, and initial conditions to study their effects on the system's behavior.

### Applications

The simulation can be used for educational purposes to demonstrate fundamental concepts in physics and engineering, such as energy conservation, oscillatory motion, and system dynamics. It is also applicable in research settings for analyzing and designing similar mechanical systems.

## Getting Started

To get started with the simulation, follow these steps:

1. **Clone the Repository:**
    git clone https://github.com/mateusctelles/TrolleyAndPendulum.git

2. **Edit Simulation Parameters:**
    By editing the TrolleyAndPendulum.cpp file you can choose different initial conditions, step size, simulation time, energy conservation criteria.

3. **Choose System Parameters:**
    By editing the TrolleyAndPendulum.cpp file you can use the default parameters of the system, or change them in the components.hpp file. It is possible to change Spring Stiffness, Trolley Mass, Pendulum Mass and Rod Length.

5. **Build the Project:**
    Navigate to the project directory and use VSCode build task configured in the `.json` file to compile the project. You can do this by pressing `Ctrl+Shift+B` or by selecting `Terminal > Run Build Task` from the VSCode menu.

6. **Run the Simulation:**
Execute the simulation binary:


7. **Visualize the Results:**
Open the generated csv files in your preferred plotting tool to observe the system's behavior.

## Code Structure

- **TrolleyAndPendulum.cpp**: This is the file with the main function of the codebase. It's where the user can edit the simulation parameters. After the parameters section, it performs the function calls required to perform the calculations, test the results, and export the results to .csv files.
  
- **utilities.cpp**: Is the file that contains all of the functions called in the int main(), with exception of the ODE solver.
  
- **components.cpp**: Is the file that contains the classes of the physical components being modelled. This is the file to be edited if the user desires to change system parameters.

- **odesolver.cpp**: This file contains the solver that performs the integration on the equations of movement. It uses the Midpoint Method of numerical integration.

## Equations

The system was modelled using Lagrangian Mechanics.

Skipping initial algebraic steps, the first goal is to arrive at the equations of total Kinetic Energy T<sub>total</sub> and Total Potential Energy V<sub>total</sub>.

<p align="center">
  <img src="https://github.com/mateusctelles/TrolleyAndPendulum/blob/main/images/T_total_black.png?raw=true" alt="Total Kinetic Energy">
</p>

<p align="center">
  <img src="https://github.com/mateusctelles/TrolleyAndPendulum/blob/main/images/v_total_black.png?raw=true" alt="Total Potential Energy">
</p>

We can then build the Lagrangian equation, to then derive the equations of motion for the Acceleration of the Trolley and the Angular Acceleration of the Pendulum

<p align="center">
  <img src="https://github.com/mateusctelles/TrolleyAndPendulum/blob/main/images/x_dot_dot_black.png?raw=true" alt="x_dot_dot">
</p>

<p align="center">
  <img src="https://github.com/mateusctelles/TrolleyAndPendulum/blob/main/images/theta_dot_dot_black.png?raw=true" alt="theta_dot_dot">
</p>


## Testing and Validation

### Matlab

  Preliminary tests were conducted in MATLAB to obtain quick feedback on the system's behavior during the derivation of the equations. 
  
  An animation of the system was created to visually assess its behavior, providing insights into the dynamics of the trolley and pendulum. Additionally, accelerations and energies were analyzed to validate the simulation results and ensure the accuracy of the model. 
  
  This iterative process of testing and refinement helped refine the simulation and ensure its reliability before implementation in C++.

<p align="center">

  <img src="https://github.com/mateusctelles/TrolleyAndPendulum/blob/main/images/final_gif.gif?raw=true" alt="final_gif" width="450"/>
  <img src="https://github.com/mateusctelles/TrolleyAndPendulum/blob/main/images/ZeroStiffness.gif?raw=true" alt="ZeroStiffness" width="450"/>
 
  First Image: Initial Position = 0.02m; Spring Stiffness = 5000N/m; Stepsize = 0.0001 (used this value in matlab due to the simpler Forward Euler integrator being used).
 
  Second Image: Initial Position = 0.0m; Spring Stiffness = 0; Initial Angle = 160 degrees.
</p>

The second case was an additional event to test the stability of the simuations even under more unstable conditions. It was then concluded that the model was working properly (except when StepSize smaller than needed).

### C++

Once implemented in C++, the results were analyzed via Excel spreadsheets, by importing the generated csv files. The accelerations were then compared to the Matlab results. 

A second step was to analyze the Total Mechanical Energy in the system. Since there is no friction, air resistance or damping, the total energy must be conserved.

#### Results

For all simulations in this section, the system parameters, the duration, the energy criteria and the initial conditions are the same.

**- Step Size: 0.001**

<p align="center">
  <img src="https://github.com/mateusctelles/TrolleyAndPendulum/blob/main/images/cpp_10e-3_Acceleration_2.png" alt="Acceleration" width="450"/>
  <img src="https://github.com/mateusctelles/TrolleyAndPendulum/blob/main/images/cpp_10e-3_Energy.png" alt="Energy" width="450"/>
</p>

From these results, we can see that the behavior is similar to the expected. But a problem is the growing accelerations over time. This is a symptom of the energy not being conserve. Usually this is related to bad convergence due to the Step Size not being small enough for the system parameters to properly converge. This usually happens when fast dynamics are present. And since we have a relatively short rod (0.1m) and a stiff spring (5000N/m), we get into this sort of problem.

Looking at the Energy conservation plot, we can observe the trend of an increasing Total Mechanical Energy, which confirms the first assessment. 

The code is prepared to always perform a test on the results, and then evaluate if these results are valid under the defined criteria. For this simulation, we get the following message/test result:

<p align="center">
  <img src="https://github.com/mateusctelles/TrolleyAndPendulum/blob/main/images/failed.png" alt="Failed" width="450"/>
</p>

**- Step Size: 0.0001**