#ifndef _FILE_HANDLER_H_
#define _FILE_HANDLER_H_

/*
file_handler.h
Author: Student
Created: 01/01/2026
Updated: 01/01/2026
*/

#include "day_summary.h"
#include <string>

/**
 * Handles writing daily summary output files.
 */
class File_Handler
{
public:
    /**
     * Write a day's summary to a .dat file named after the date.
     * @param date the date string in DD/MM/YYYY format
     * @param summary the day's summary data
     */
    static void write_summary(const std::string& date,
                              const Day_Summary& summary);

    /**
     * Build the output filename from a date string (DD/MM/YYYY -> DDMMYYYY.dat).
     * @param date the date string in DD/MM/YYYY format
     * @return the output filename
     */
    static std::string build_filename(const std::string& date);
};

#endif
