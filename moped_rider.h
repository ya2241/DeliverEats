#ifndef _MOPED_RIDER_H_
#define _MOPED_RIDER_H_

/*
moped_rider.h
Author: Student
Created: 01/01/2026
Updated: 01/01/2026
*/

#include "delivery_rider.h"

/**
 * Represents a moped delivery rider.
 * Moped riders have no distance limits and can take priority orders.
 */
class Moped_Rider : public Delivery_Rider
{
public:
    /**
     * Constructor for Moped_Rider.
     * @param name the rider's name
     * @param speed_mph the rider's speed in miles per hour
     */
    Moped_Rider(const std::string& name, double speed_mph);

    /**
     * Moped riders can deliver any distance.
     * @param distance the delivery distance in miles
     * @return always true
     */
    bool can_deliver(double distance) const override;

    /**
     * Record a delivery (no-op for moped as there is no daily limit).
     * @param distance the delivery distance in miles
     */
    void record_delivery(double distance) override;

    /**
     * Moped riders are always moped riders.
     * @return true
     */
    bool is_moped() const override;
};

#endif
