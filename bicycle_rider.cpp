/*
bicycle_rider.cpp
Author: Student
Created: 01/01/2026
Updated: 01/01/2026
*/

#include "bicycle_rider.h"

const double Bicycle_Rider::MAX_DELIVERY_DISTANCE = 2.0;

Bicycle_Rider::Bicycle_Rider(const std::string& name, double speed_mph,
                             double max_daily_miles)
    : Delivery_Rider(name, speed_mph),
      max_daily_miles(max_daily_miles),
      miles_ridden_today(0.0)
{
}

bool Bicycle_Rider::can_deliver(double distance) const
{
    // Cannot deliver more than 2 miles in a single trip
    if (distance > MAX_DELIVERY_DISTANCE)
    {
        return false;
    }

    // Round trip must not exceed remaining daily allowance
    double round_trip = 2.0 * distance;
    return (miles_ridden_today + round_trip) <= max_daily_miles;
}

void Bicycle_Rider::record_delivery(double distance)
{
    miles_ridden_today += 2.0 * distance;
}

bool Bicycle_Rider::is_moped() const
{
    return false;
}

void Bicycle_Rider::reset_for_new_day()
{
    Delivery_Rider::reset_for_new_day();
    miles_ridden_today = 0.0;
}

double Bicycle_Rider::get_miles_today() const
{
    return miles_ridden_today;
}

double Bicycle_Rider::get_max_daily_miles() const
{
    return max_daily_miles;
}
