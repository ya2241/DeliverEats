/*
main.cpp
Author: Student
Created: 01/01/2026
Updated: 01/01/2026
*/

#include "simulation.h"
#include <iostream>

/**
 * Entry point. Expects a single command-line argument: the input file path.
 */
int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <orders_file>" << std::endl;
        return 1;
    }

    Simulation sim;
    sim.run(argv[1]);

    return 0;
}
