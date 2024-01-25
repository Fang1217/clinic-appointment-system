#pragma once
#ifndef DateTime_HPP
#define DateTime_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <regex>
#include <iomanip>

using namespace std;

// Custom DateTime class that improves readability of <ctime>
class DateTime {
private:
    time_t storedTime;
    tm* getLocalTime() const;
public:
    // Default Constructor: Initiate current time.
    DateTime();
    // Copy Constructor
    DateTime(const DateTime& d);

    // Using Regular Expressions to extract information from string.
    // Returns false if input string is an invalid.
    bool setTime(string input);

    // Specific argument to set time.
    // Returns true all fields are valid.
    bool setTime(int year, int month, int day = 1, int hour = 0, int minute = 0, int second = 0);

    // Display current date with %Y, %m, %d
    // Default format: YYYY/MM/DD
    string displayDate(string format = "%Y/%m/%d") const;
    // Display current date time with %Y, %m, %d, %H, %M, %S 
    // Default format: YYYY/MM/DD HH:MM
    string displayTime(string format = "%Y/%m/%d %H:%M") const;

    // Return time_t storedTime, which can be used for comparison.
    time_t getTime() const;
    // Get the year of the DateTime object. Returns int from 1900 to 2038.
    int getYear() const;
    // Get the month of the DateTime object. Returns int from 1 to 12.
    int getMonth() const;
    // Get the day of the DateTime object. Returns int from 1900 to 2038.
    int getDay() const;
    // Get the hour of the DateTime object. Returns int from 0 to 23 (24 hour format).
    int getHour() const;
    // Get the minute of the DateTime object. Returns int from 0 to 59.
    int getMinute() const;
    // Get the second of the DateTime object. Returns int from 0 to 59.
    int getSecond() const;
    // Get the day of the week of the DateTime object. Returns int from 0 (Sunday) to 6 (Saturday).
    int getDayOfWeek() const;
};

#endif