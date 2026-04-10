/*
moped_rider.cpp
Author: Student
Created: 01/01/2026
Updated: 01/01/2026
*/

#include "moped_rider.h"

Moped_Rider::Moped_Rider(const std::string& name, double speed_mph)
    : Delivery_Rider(name, speed_mph)
{
}

bool Moped_Rider::can_deliver(double distance) const
{
    // Moped riders have no distance restrictions
    (void)distance;
    return true;
}

void Moped_Rider::record_delivery(double distance)
{
    // Moped riders have no daily limit to track
    (void)distance;
}

bool Moped_Rider::is_moped() const
{
    return true;
}
