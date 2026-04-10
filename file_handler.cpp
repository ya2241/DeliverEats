/*
file_handler.cpp
Author: Student
Created: 01/01/2026
Updated: 01/01/2026
*/

#include "file_handler.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <stdexcept>

/**
 * Convert DD/MM/YYYY to DDMMYYYY.dat
 */
std::string File_Handler::build_filename(const std::string& date)
{
    // date format: DD/MM/YYYY - extract digits, skip slashes
    std::string filename;
    for (char c : date)
    {
        if (c != '/')
        {
            filename += c;
        }
    }
    filename += ".dat";
    return filename;
}

void File_Handler::write_summary(const std::string& date,
                                 const Day_Summary& summary)
{
    std::string filename = build_filename(date);
    std::ofstream out(filename);

    if (!out.is_open())
    {
        std::cerr << "Error: could not open output file: " << filename
                  << std::endl;
        return;
    }

    out << std::fixed << std::setprecision(2);
    out << "Date: " << date << "\n";
    out << "Total deliveries: " << summary.total_deliveries << "\n";
    out << "Total takings: £" << summary.total_takings << "\n";
    out << "Bicycle deliveries: " << summary.bicycle_deliveries << "\n";
    out << "Bicycle takings: £" << summary.bicycle_takings << "\n";
    out << "Moped deliveries: " << summary.moped_deliveries << "\n";
    out << "Moped takings: £" << summary.moped_takings << "\n";
    out << "Missed orders: " << summary.missed_orders << "\n";
}
