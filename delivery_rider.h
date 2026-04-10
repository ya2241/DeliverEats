#ifndef _DELIVERY_RIDER_H_
#define _DELIVERY_RIDER_H_

/*
delivery_rider.h
Author: Student
Created: 01/01/2026
Updated: 01/01/2026
*/

#include <string>

/**
 * Abstract base class representing a delivery rider.
 * Stores common attributes and provides interface for derived classes.
 */
class Delivery_Rider
{
private:
    std::string name;
    double speed_mph;
    double available_at; // time in decimal hours when rider is next available

public:
    /**
     * Constructor for Delivery_Rider.
     * @param name the rider's name
     * @param speed_mph the rider's speed in miles per hour
     */
    Delivery_Rider(const std::string& name, double speed_mph);

    /**
     * Virtual destructor.
     */
    virtual ~Delivery_Rider() = default;

    /**
     * Get the rider's name.
     * @return the rider's name
     */
    std::string get_name() const;

    /**
     * Get the rider's speed in mph.
     * @return speed in mph
     */
    double get_speed() const;

    /**
     * Get the time (decimal hours) at which the rider becomes available.
     * @return available time in decimal hours
     */
    double get_available_at() const;

    /**
     * Set the time at which the rider becomes available.
     * @param time the time in decimal hours
     */
    void set_available_at(double time);

    /**
     * Reset the rider's state at the start of a new day.
     */
    virtual void reset_for_new_day();

    /**
     * Check if rider can take a delivery of a given distance.
     * @param distance the delivery distance in miles
     * @return true if the rider can take the delivery
     */
    virtual bool can_deliver(double distance) const = 0;

    /**
     * Record that a delivery of the given distance was taken.
     * @param distance the delivery distance in miles
     */
    virtual void record_delivery(double distance) = 0;

    /**
     * Check if this is a moped rider (used for priority orders).
     * @return true if moped rider
     */
    virtual bool is_moped() const = 0;

    /**
     * Calculate the return time after a delivery.
     * @param order_time the time the order was placed (decimal hours)
     * @param distance the delivery distance in miles
     * @return the time the rider will return (decimal hours)
     */
    double calc_return_time(double order_time, double distance) const;
};

#endif
