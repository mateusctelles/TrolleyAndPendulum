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

### MATLAB

Preliminary tests were conducted in MATLAB to obtain quick feedback on the system's behavior during the derivation of the equations. An animation of the system was created to visually assess its behavior, providing insights into the dynamics of the trolley and pendulum. 

Additionally, accelerations and energies were analyzed to validate the simulation results and ensure the accuracy of the model. This iterative process of testing and refinement helped refine the simulation and ensure its reliability before implementation in C++.

<p align="center">
  <img src="https://github.com/mateusctelles/TrolleyAndPendulum/blob/main/images/final_gif.gif?raw=true" alt="final_gif" width="450"/>
  <img src="https://github.com/mateusctelles/TrolleyAndPendulum/blob/main/images/ZeroStiffness.gif?raw=true" alt="ZeroStiffness" width="450"/>
  
  First Image: Initial Position = 0.02m; Spring Stiffness = 5000N/m; Stepsize = 0.0001 (used this value in MATLAB due to the simpler Forward Euler integrator being used).
 
  Second Image: Initial Position = 0.0m; Spring Stiffness = 0; Initial Angle = 160 degrees.
</p>

The second case was an additional event to test the stability of the simulations even under more unstable conditions. It was then concluded that the model was working properly (except when StepSize smaller than needed).

### C++

**Test Procedures**

- Evaluation of system acceleration profile
- Evaluation of Total Mechanical Energy (TME) differences
- Evaluation of the trend of change of the Total Mechanical Energy variation by looking into the Moving Average of the (TME)
  
Once implemented in C++, the results were analyzed via Excel spreadsheets, by importing the generated CSV files. The accelerations were then compared to the MATLAB results. 

A second step was to analyze the Total Mechanical Energy in the system. Since there is no friction, air resistance, or damping, the total energy must be conserved.

#### Results

For all simulations in this section, the system parameters, the duration, the energy criteria, and the initial conditions are the same.

**- Step Size: 0.001**

<p align="center">
  <img src="https://github.com/mateusctelles/TrolleyAndPendulum/blob/main/images/cpp_10e-3_Acceleration.png?raw=true" alt="Acceleration" width="450"/>
  <img src="https://github.com/mateusctelles/TrolleyAndPendulum/blob/main/images/cpp_10e-3_Energy.png?raw=true" alt="Energy" width="450"/>
</p>

These results indicate that the system's behavior aligns with expectations. However, a notable issue is the increasing accelerations over time, suggesting a lack of energy conservation. This discrepancy is often attributed to poor convergence caused by an insufficiently small Step Size for the system's parameters to converge accurately. Such issues typically arise in systems with fast dynamics, such as ours, characterized by a relatively short rod (0.1m) and a stiff spring (5000N/m).

Upon reviewing the Energy conservation plot, we can discern a trend of increasing Total Mechanical Energy, further supporting the initial assessment.

The code is designed to conduct tests on the results and evaluate their compliance with predefined criteria. In this simulation, the following message/test result was obtained:

<p align="center">
  <img src="https://github.com/mateusctelles/TrolleyAndPendulum/blob/main/images/failed.png?raw=true" alt="Failed" width="450"/>
</p>

**- Step Size: 0.0001**
<p align="center">
  <img src="https://github.com/mateusctelles/TrolleyAndPendulum/blob/main/images/cpp_10e-4_Acceleration.png?raw=true" alt="Acceleration" width="450"/>
  <img src="https://github.com/mateusctelles/TrolleyAndPendulum/blob/main/images/cpp_10e-4_Energy.png?raw=true" alt="Energy" width="450"/>
</p>

Now we can see that the acceleration profile looks more stable. To make sure of this, we then look at the Total Mechanical Energy plot. We can see that the variation over time is way smaller than the previous results. The trend also shows a way smaller variation over time.

We then look at how the results went against the defined criteria:

<p align="center">
  <img src="https://github.com/mateusctelles/TrolleyAndPendulum/blob/main/images/pass.png?raw=true" alt="Failed" width="450"/>
</p>
