/*
tests.cpp
Author: Student
Created: 01/01/2026
Updated: 01/01/2026
*/

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "moped_rider.h"
#include "bicycle_rider.h"
#include "day_summary.h"
#include "file_handler.h"

// ---- Moped_Rider tests ----

TEST_CASE("Moped_Rider: can deliver any distance", "[moped]")
{
    Moped_Rider rider("Anne", 32.0);
    REQUIRE(rider.can_deliver(0.5) == true);
    REQUIRE(rider.can_deliver(2.0) == true);
    REQUIRE(rider.can_deliver(10.0) == true);
    REQUIRE(rider.can_deliver(100.0) == true);
}

TEST_CASE("Moped_Rider: is_moped returns true", "[moped]")
{
    Moped_Rider rider("Jim", 28.0);
    REQUIRE(rider.is_moped() == true);
}

TEST_CASE("Moped_Rider: calc_return_time is correct", "[moped]")
{
    // Anne: 32 mph, 1.6 mile delivery ordered at 6.0 hours
    // round trip = 3.2 miles / 32 mph = 0.1 hours -> returns at 6.1
    Moped_Rider rider("Anne", 32.0);
    double ret = rider.calc_return_time(6.0, 1.6);
    REQUIRE(ret == Approx(6.1));
}

TEST_CASE("Moped_Rider: available_at updated correctly", "[moped]")
{
    Moped_Rider rider("Bob", 27.0);
    REQUIRE(rider.get_available_at() == Approx(0.0));
    rider.set_available_at(8.5);
    REQUIRE(rider.get_available_at() == Approx(8.5));
}

TEST_CASE("Moped_Rider: reset_for_new_day resets available_at", "[moped]")
{
    Moped_Rider rider("Amy", 24.0);
    rider.set_available_at(22.0);
    rider.reset_for_new_day();
    REQUIRE(rider.get_available_at() == Approx(0.0));
}

// ---- Bicycle_Rider tests ----

TEST_CASE("Bicycle_Rider: cannot deliver more than 2 miles", "[bicycle]")
{
    Bicycle_Rider rider("Sue", 4.0, 23.0);
    REQUIRE(rider.can_deliver(1.9) == true);
    REQUIRE(rider.can_deliver(2.0) == true);
    REQUIRE(rider.can_deliver(2.1) == false);
    REQUIRE(rider.can_deliver(5.0) == false);
}

TEST_CASE("Bicycle_Rider: cannot deliver if round trip exceeds daily max",
          "[bicycle]")
{
    // Bill: max 17 miles/day, 5 mph
    Bicycle_Rider rider("Bill", 5.0, 17.0);

    // Record 8 deliveries of 1 mile each = 16 miles total
    for (int i = 0; i < 8; ++i)
    {
        REQUIRE(rider.can_deliver(1.0) == true);
        rider.record_delivery(1.0);
    }

    // 16 miles used, 1 mile left - a 1-mile trip needs 2 miles round trip
    REQUIRE(rider.can_deliver(1.0) == false);

    // But a 0.5-mile trip needs 1 mile round trip - still fits
    REQUIRE(rider.can_deliver(0.5) == true);
}

TEST_CASE("Bicycle_Rider: is_moped returns false", "[bicycle]")
{
    Bicycle_Rider rider("Steve", 3.0, 21.0);
    REQUIRE(rider.is_moped() == false);
}

TEST_CASE("Bicycle_Rider: reset_for_new_day resets mileage and availability",
          "[bicycle]")
{
    Bicycle_Rider rider("Sue", 4.0, 23.0);
    rider.record_delivery(2.0); // 4 miles round trip
    rider.set_available_at(10.0);

    rider.reset_for_new_day();

    REQUIRE(rider.get_miles_today() == Approx(0.0));
    REQUIRE(rider.get_available_at() == Approx(0.0));
    REQUIRE(rider.can_deliver(2.0) == true);
}

TEST_CASE("Bicycle_Rider: calc_return_time is correct", "[bicycle]")
{
    // Steve: 3 mph, 1.5 mile delivery at 7.0 hours
    // round trip = 3.0 miles / 3 mph = 1.0 hour -> returns at 8.0
    Bicycle_Rider rider("Steve", 3.0, 21.0);
    double ret = rider.calc_return_time(7.0, 1.5);
    REQUIRE(ret == Approx(8.0));
}

// ---- Day_Summary tests ----

TEST_CASE("Day_Summary: initialises to zero", "[summary]")
{
    Day_Summary s;
    REQUIRE(s.total_deliveries == 0);
    REQUIRE(s.total_takings == Approx(0.0));
    REQUIRE(s.bicycle_deliveries == 0);
    REQUIRE(s.bicycle_takings == Approx(0.0));
    REQUIRE(s.moped_deliveries == 0);
    REQUIRE(s.moped_takings == Approx(0.0));
    REQUIRE(s.missed_orders == 0);
}

// ---- File_Handler tests ----

TEST_CASE("File_Handler: build_filename produces correct output", "[file]")
{
    REQUIRE(File_Handler::build_filename("01/11/2025") == "01112025.dat");
    REQUIRE(File_Handler::build_filename("12/01/2026") == "12012026.dat");
}
