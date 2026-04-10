#ifndef _SIMULATION_H_
#define _SIMULATION_H_

/*
simulation.h
Author: Student
Created: 01/01/2026
Updated: 01/01/2026
*/

#include "delivery_rider.h"
#include "day_summary.h"
#include "order.h"
#include <vector>
#include <deque>
#include <string>

/**
 * Manages the delivery simulation: maintains the rider queue,
 * processes orders, and accumulates daily statistics.
 */
class Simulation
{
private:
    std::vector<Delivery_Rider*> all_riders; // owned pointers, in initial order
    std::deque<Delivery_Rider*> queue;       // current day queue
    Day_Summary summary;
    std::string current_date;

    static const double STANDARD_CHARGE;
    static const double PRIORITY_CHARGE;

    /**
     * Reset all riders and rebuild the queue for a new day.
     */
    void reset_for_new_day();

    /**
     * Find the first suitable rider in the queue for the given order.
     * Returns nullptr and records a missed order if none found.
     * @param order the order to process
     * @return pointer to the chosen rider, or nullptr if missed
     */
    Delivery_Rider* find_rider(const Order& order);

    /**
     * Process a single order: assign a rider, update their state,
     * and update the day summary.
     * @param order the order to process
     */
    void process_order(const Order& order);

public:
    /**
     * Constructor - sets up all riders in the correct initial order.
     */
    Simulation();

    /**
     * Destructor - cleans up dynamically allocated riders.
     */
    ~Simulation();

    /**
     * Run the simulation by reading and processing the given input file.
     * @param filename path to the input orders file
     */
    void run(const std::string& filename);
};

#endif
