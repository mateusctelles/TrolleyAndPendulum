### Coding Challenge Guidelines

This project contains:

1. Some very basic classes defining the physical components of the trolley/spring/pendulum system illustrated in the picture trolleyandpendulum.png.
2. A basic ODE solver (in odesolver.hpp). This solves the forward time marching dynamics of a system defined by the input "physicsFunction", which implements the physics in the form: physicsFunction(dxState, xState, userArgs). Where dxState is the rate of the change w.r.t. time of the state vector xState.
3. An empty main function.

The assignment we would like you to attempt is to implement code to compute the accelerations of the system degrees of freedom (the trolley position and pendulum angle), then use the solveMidpointMethod to solve the forward time marching dynamics of the system over a 5s time horizon. A suitable interface should be written such that the solution should be returned from the following call:

solveMidpointMethod(0, 5, 1e-3, ...)

Which is to be made from the main() function. The initial conditions are that xTrolley = 0.02m, dxTrolley = 0, thetaPendulum = 0, dthetaPendulum = 0.

Having successfully completed this, please also implement some suitably chosen test functions which can be called to verify that the system is behaving as you expect.

Please do not modify the odesolver, the pendulum class, the trolley class or the spring class. 

### Assumptions

- Acceleration due to gravity = 9.81m/s.
- We cannot assume that the angles subtended by the pendulum are small.

### Evaluation Criteria

Your code will be evaluated based on a mixture of the following:

1. Producing the right answers.
2. Suitable organisation.
3. Readability and commenting.
4. Adherence to C++11 or C++17 standards.
5. Test coverage.

### CodeSubmit

Please organize, design, test, and document your code as if it were
going into production - then push your changes to the master branch.

Have fun coding! 🚀
