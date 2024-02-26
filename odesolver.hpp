#ifndef ODE_HPP
#define ODE_HPP

#include <functional>
#include <vector>
#include <iostream>
#include "utilities.hpp"

std::vector<std::vector<double>> solveMidpointMethod(double tStart, double tStop, double tMajorStep, std::vector<double> x0, std::function<void(std::vector<double>&, const std::vector<double>&, void*)> physicsFunction, void* userArgs)
{
					
	std::vector<double> xState = x0;
	std::vector<double> xStateMidPoint(x0.size());
	std::vector<double> dxState(x0.size());
	
	std::vector<std::vector<double>> xStateHistory(x0.size());

	double tCurrent = tStart;

	/* enter a loop */
	while (true)
	{			
		/* Now call the model */
		physicsFunction(dxState, xState, userArgs);
		
		/* Update the estimate of the state for the midpoint */
		for (int i = 0; i < x0.size(); i++)
			xStateMidPoint[i] = xState[i] + tMajorStep * dxState[i] / 2;

		/* Now call the model at the mid point */
		physicsFunction(dxState, xStateMidPoint, userArgs);

		/* Now update the trim states for the next go around */
		for (int i = 0; i < x0.size(); i++) {
			xState[i] = xState[i] + tMajorStep * dxState[i];
			xStateHistory[i].push_back(xState[i]);
		}
		
		/* Should we exit? */
		tCurrent += tMajorStep;

		if (tCurrent >= tStop)
		{
			std::cout << "Time marching simulation finished\n";
			break;
		}

	}

	return xStateHistory;	
}





#endif

