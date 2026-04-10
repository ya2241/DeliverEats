/*
simulation.cpp
Author: Student
Created: 01/01/2026
Updated: 01/01/2026
*/

#include "simulation.h"
#include "moped_rider.h"
#include "bicycle_rider.h"
#include "file_handler.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

const double Simulation::STANDARD_CHARGE = 2.0;
const double Simulation::PRIORITY_CHARGE = 3.0;

Simulation::Simulation()
{
    // Instantiate all riders in queue order (Anne first)
    all_riders.push_back(new Moped_Rider("Anne", 32.0));
    all_riders.push_back(new Moped_Rider("Jim", 28.0));
    all_riders.push_back(new Bicycle_Rider("Sue", 4.0, 23.0));
    all_riders.push_back(new Bicycle_Rider("Bill", 5.0, 17.0));
    all_riders.push_back(new Moped_Rider("James", 25.0));
    all_riders.push_back(new Moped_Rider("Amy", 24.0));
    all_riders.push_back(new Moped_Rider("Bob", 27.0));
    all_riders.push_back(new Bicycle_Rider("Steve", 3.0, 21.0));
}

Simulation::~Simulation()
{
    for (Delivery_Rider* rider : all_riders)
    {
        delete rider;
    }
}

void Simulation::reset_for_new_day()
{
    for (Delivery_Rider* rider : all_riders)
    {
        rider->reset_for_new_day();
    }

    // Rebuild queue in the original order
    queue.clear();
    for (Delivery_Rider* rider : all_riders)
    {
        queue.push_back(rider);
    }

    summary = Day_Summary();
}

/**
 * Iterate through the queue to find the first available and capable rider.
 * For priority orders only moped riders are considered.
 * Bicycle riders that cannot take the order stay in their queue position.
 * A rider who is not yet back from a delivery is also skipped.
 */
Delivery_Rider* Simulation::find_rider(const Order& order)
{
    for (size_t i = 0; i < queue.size(); ++i)
    {
        Delivery_Rider* rider = queue[i];

        // Priority orders require a moped
        if (order.is_priority && !rider->is_moped())
        {
            continue;
        }

        // Rider must have returned from any previous delivery
        if (rider->get_available_at() > order.time)
        {
            continue;
        }

        // Rider must be physically capable of the delivery
        if (!rider->can_deliver(order.distance))
        {
            continue;
        }

        // Found a suitable rider — remove from current queue position
        queue.erase(queue.begin() + static_cast<int>(i));
        return rider;
    }

    return nullptr;
}

void Simulation::process_order(const Order& order)
{
    Delivery_Rider* rider = find_rider(order);

    if (rider == nullptr)
    {
        summary.missed_orders++;
        return;
    }

    double charge = order.is_priority ? PRIORITY_CHARGE : STANDARD_CHARGE;

    // Update day summary
    summary.total_deliveries++;
    summary.total_takings += charge;

    if (rider->is_moped())
    {
        summary.moped_deliveries++;
        summary.moped_takings += charge;
    }
    else
    {
        summary.bicycle_deliveries++;
        summary.bicycle_takings += charge;
    }

    // Update rider state and send them to the back of the queue
    rider->record_delivery(order.distance);
    double return_time = rider->calc_return_time(order.time, order.distance);
    rider->set_available_at(return_time);
    queue.push_back(rider);
}

/**
 * Parse a time string of format HH.MM into decimal hours.
 * e.g. "06.30" -> 6.5
 */
static double parse_time(const std::string& token)
{
    size_t dot_pos = token.find('.');
    double hours = std::stod(token.substr(0, dot_pos));
    double minutes = std::stod(token.substr(dot_pos + 1));
    return hours + (minutes / 60.0);
}

/**
 * Parse a line in the format HH.MM:distance:Standard|Priority
 * Returns true and populates order on success, false on parse failure.
 */
static bool parse_order_line(const std::string& line, Order& order)
{
    std::istringstream ss(line);
    std::string time_token, dist_token, type_token;

    if (!std::getline(ss, time_token, ':')) return false;
    if (!std::getline(ss, dist_token, ':')) return false;
    if (!std::getline(ss, type_token)) return false;

    try
    {
        order.time = parse_time(time_token);
        order.distance = std::stod(dist_token);
    }
    catch (const std::invalid_argument&)
    {
        return false;
    }

    if (type_token == "Priority")
    {
        order.is_priority = true;
    }
    else if (type_token == "Standard")
    {
        order.is_priority = false;
    }
    else
    {
        return false;
    }

    return true;
}

/**
 * Check if a line looks like a date (DD/MM/YYYY).
 */
static bool is_date_line(const std::string& line)
{
    return line.size() == 10 && line[2] == '/' && line[5] == '/';
}

void Simulation::run(const std::string& filename)
{
    std::ifstream input(filename);
    if (!input.is_open())
    {
        std::cerr << "Error: could not open input file: " << filename
                  << std::endl;
        return;
    }

    std::string line;
    bool first_day = true;

    while (std::getline(input, line))
    {
        // Skip empty lines
        if (line.empty())
        {
            continue;
        }

        if (is_date_line(line))
        {
            // Write summary for the previous day before starting a new one
            if (!first_day)
            {
                File_Handler::write_summary(current_date, summary);
            }

            current_date = line;
            reset_for_new_day();
            first_day = false;
        }
        else
        {
            Order order;
            if (parse_order_line(line, order))
            {
                process_order(order);
            }
            else
            {
                std::cerr << "Warning: could not parse order line: "
                          << line << std::endl;
            }
        }
    }

    // Write summary for the final day
    if (!first_day)
    {
        File_Handler::write_summary(current_date, summary);
    }
}
