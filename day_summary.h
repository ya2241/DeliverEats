#ifndef _DAY_SUMMARY_H_
#define _DAY_SUMMARY_H_

/*
day_summary.h
Author: Student
Created: 01/01/2026
Updated: 01/01/2026
*/

#include <string>

/**
 * Holds the summary statistics accumulated over a single day.
 */
struct Day_Summary
{
    int total_deliveries;
    double total_takings;
    int bicycle_deliveries;
    double bicycle_takings;
    int moped_deliveries;
    double moped_takings;
    int missed_orders;

    /**
     * Constructor - initialises all fields to zero.
     */
    Day_Summary();
};

#endif
