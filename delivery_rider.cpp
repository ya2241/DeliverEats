/*
delivery_rider.cpp
Author: Student
Created: 01/01/2026
Updated: 01/01/2026
*/

#include "delivery_rider.h"

Delivery_Rider::Delivery_Rider(const std::string& name, double speed_mph)
    : name(name), speed_mph(speed_mph), available_at(0.0)
{
}

std::string Delivery_Rider::get_name() const
{
    return name;
}

double Delivery_Rider::get_speed() const
{
    return speed_mph;
}

double Delivery_Rider::get_available_at() const
{
    return available_at;
}

void Delivery_Rider::set_available_at(double time)
{
    available_at = time;
}

void Delivery_Rider::reset_for_new_day()
{
    available_at = 0.0;
}

/**
 * Time = distance / speed for the delivery plus the same for the return trip,
 * so total travel time = (2 * distance) / speed hours.
 */
double Delivery_Rider::calc_return_time(double order_time,
                                        double distance) const
{
    double travel_hours = (2.0 * distance) / speed_mph;
    return order_time + travel_hours;
}
