#include <iostream>
#include <string>
#include "DateTime.hpp"
#include "Appointment.hpp"

void Appointment::displayCalendar(DateTime& selectedMonth)
{
    int numOfDays = 0;
    int month = selectedMonth.getMonth();
    int year = selectedMonth.getYear();
    int firstDayOfMonth = selectedMonth.getDayOfWeek();

    bool oddMonth = ((month > 7) ? (month % 2 == 0) : (month % 2 == 1));
    numOfDays = oddMonth ? 31 : 30;

    // Check for leap year if month is February
    bool leapYear = ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
    if (month == 2) numOfDays = leapYear ? 29 : 28;

    static string dayName[] = {
        "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"  // all 3 chars
    };

    static string monthName[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    // Count number of appointments in each day.
    int* numbersOfAppointments = new int[numOfDays];
    for (int i = 0; i < numOfDays; i++)
        numbersOfAppointments[i] = 0;

    sortEntry(headNodePointer); // Sort entries in start date.
    AppointmentNode* current = headNodePointer;
    
    DateTime today;
    bool todayIsThisMonth = (today.getYear() == year) && (today.getMonth() == month);
    DateTime nextMonth;
    nextMonth.setTime(month == 12 ? year + 1 : year, ((month + 1) % 12) + 1);

    // For each appointment, count the appointments for each day that are in the same month.
    while (current != NULL && current->appointmentEntry.startTime.getTime() < nextMonth.getTime())
    {
        DateTime startTime = current->appointmentEntry.startTime;
        if (startTime.getYear() == year && startTime.getMonth() == month)
            numbersOfAppointments[startTime.getDay() - 1]++;

        current = current->nextNode;
    }

    // Display month and year
    cout << "Showing events in " << monthName[month - 1] << " " << year << ": " << endl;
    cout << "--------------------------------------------------------" << endl;

    for (string i : dayName)
        cout << i << "\t";
    endl(cout);

    cout << "--------------------------------------------------------" << endl;

    int currentDay = 1;     // the current day to display

    // Display the first week
    for (int i = 0; i < firstDayOfMonth; i++)
        cout << "\t";

    for (int i = firstDayOfMonth; i < 7; i++)
    {
        // If there are appointments on the current day
        cout << currentDay;
        if (numbersOfAppointments[currentDay - 1] > 0)
            cout << "[" << numbersOfAppointments[currentDay - 1] << "]";
        if (today.getDay() == currentDay && todayIsThisMonth)
            cout << "*";
        cout << "\t";
        currentDay++;
    }
    endl(cout);

    // Display the remaining weeks.
    while (currentDay <= numOfDays)
    {
        // for each week
        for (int i = 0; i < 7; i++)
        {
            if (currentDay <= numOfDays)
            {
                cout << currentDay;
                if (numbersOfAppointments[currentDay - 1] > 0)
                    cout << "[" << numbersOfAppointments[currentDay - 1] << "]";
                if (today.getDay() == currentDay && todayIsThisMonth)
                    cout << "*";
                cout << "\t";
                currentDay++;
            }
        }
        endl(cout);
    }
    cout << "\n[n]: Number of Appointments in that day.\n*: Today\n";
}