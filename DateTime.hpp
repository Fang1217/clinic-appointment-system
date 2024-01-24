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
    // Returns true if string is a valid date/time.
    bool setTime(string input);

    // Specific argument to set time.
    // Returns true all fields are valid.
    bool setTime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0);

    // Display time with %Y, %m, %d, %H, %M, %S 
    // Example: "%Y-%m-%d %H:%M:%S"
    string displayDate(string format = "%Y/%m/%d") const;
    string displayTime(string format = "%Y/%m/%d %H:%M") const;

    // Return time_t storedTime, which can be used for comparison.
    time_t getTime() const;
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    int getHour() const;
    int getMinute() const;
    int getSecond() const;
    int getDayOfWeek() const;
};

#endif