#ifndef _ORDER_H_
#define _ORDER_H_

/*
order.h
Author: Student
Created: 01/01/2026
Updated: 01/01/2026
*/

#include <string>

/**
 * Represents a single customer order.
 */
struct Order
{
    double time;        // order time in decimal hours
    double distance;    // delivery distance in miles
    bool is_priority;   // true if priority (moped only), false if standard
};

#endif
