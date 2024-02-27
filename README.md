# Trolley and Pendulum Simulation

## Overview

This project simulates the dynamics of a system consisting of a trolley connected to a fixed base via a spring, with a pendulum rigidly attached to the trolley. The simulation aims to provide insights into the behavior of the system under various conditions and to validate energy conservation principles.

<p align="center">
  <img src="https://github.com/mateusctelles/TrolleyAndPendulum/blob/main/images/trolleyandpendulum.png?raw=true" alt="Trolley and Pendulum"/>
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
  <img src="https://github.com/mateusctelles/TrolleyAndPendulum/blob/main/images/black_theta_dot_dot_.gif?raw=true" alt="Black Theta Double Dot">
</p>


