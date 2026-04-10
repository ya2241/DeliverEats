#ifndef _BICYCLE_RIDER_H_
#define _BICYCLE_RIDER_H_

/*
bicycle_rider.h
Author: Student
Created: 01/01/2026
Updated: 01/01/2026
*/

#include "delivery_rider.h"

/**
 * Represents a bicycle delivery rider.
 * Bicycle riders have a per-delivery distance limit of 2 miles and a
 * daily maximum distance limit.
 */
class Bicycle_Rider : public Delivery_Rider
{
private:
    double max_daily_miles;
    double miles_ridden_today;

    static const double MAX_DELIVERY_DISTANCE;

public:
    /**
     * Constructor for Bicycle_Rider.
     * @param name the rider's name
     * @param speed_mph the rider's speed in miles per hour
     * @param max_daily_miles the maximum miles they can ride in a day
     */
    Bicycle_Rider(const std::string& name, double speed_mph,
                  double max_daily_miles);

    /**
     * Bicycle riders can deliver only if within the 2-mile limit and
     * the round trip won't exceed their daily maximum.
     * @param distance the delivery distance in miles
     * @return true if the rider can take the delivery
     */
    bool can_deliver(double distance) const override;

    /**
     * Record a delivery and update the daily miles ridden.
     * @param distance the delivery distance in miles
     */
    void record_delivery(double distance) override;

    /**
     * Bicycle riders are not moped riders.
     * @return false
     */
    bool is_moped() const override;

    /**
     * Reset daily mileage at the start of a new day.
     */
    void reset_for_new_day() override;

    /**
     * Get the total miles ridden today.
     * @return miles ridden today
     */
    double get_miles_today() const;

    /**
     * Get the maximum daily miles for this rider.
     * @return maximum daily miles
     */
    double get_max_daily_miles() const;
};

#endif
