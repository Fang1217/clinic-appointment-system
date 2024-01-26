#include "DateTime.hpp"

// Custom DateTime class that improves readability of <ctime>
tm* DateTime::getLocalTime() const {
#pragma warning(disable: 4996)
	return localtime(&storedTime);
}

DateTime::DateTime() {
	storedTime = time(0);
}

DateTime::DateTime(const DateTime& d) {
	storedTime = d.getTime();
}

bool DateTime::setTime(string input, bool DateOnly) {
	regex pattern;
	if (DateOnly)
		pattern = (R"(^ *(\d{2,4})\/(\d{1,2})\/(\d{1,2}) *$)"); // in YYYY/MM/DD format
	else
		pattern = (R"(^ *(\d{2,4})\/(\d{1,2})\/(\d{1,2})(?: (\d{1,2}):(\d{2})(?::(\d{2}))?) *$)"); // in YYYY/MM/DD HH:MM:SS format.
	smatch matches;

	bool match = regex_match(input, matches, pattern);
	if (!match) {
		return false;
	}
	int year = stoi(matches[1]);
	year = (year < 50) ? (year += 2000) : (year < 100) ? (year += 1900) : year; // provide alias for YY format.
	int month = stoi(matches[2]);
	int day = stoi(matches[3]);

	int hour = matches[4].matched ? stoi(matches[4]) : 0;
	int minute = matches[5].matched ? stoi(matches[5]) : 0;
	int second = matches[6].matched ? stoi(matches[6]) : 0;

	return setTime(year, month, day, hour, minute, second);
}

bool DateTime::setTime(int year, int month, int day, int hour, int minute, int second) {
	tm timeInfo = {};
	timeInfo.tm_year = year - 1900;  // Years since 1900
	timeInfo.tm_mon = month - 1;    // Months are zero-based
	timeInfo.tm_mday = day;
	timeInfo.tm_hour = hour;
	timeInfo.tm_min = minute;
	timeInfo.tm_sec = second;

	storedTime = mktime(&timeInfo);

	// Check if mktime has normalized the components (e.g., handles out-of-range values)
	return (
		year == timeInfo.tm_year + 1900 &&
		month == timeInfo.tm_mon + 1 &&
		day == timeInfo.tm_mday &&
		hour == timeInfo.tm_hour &&
		minute == timeInfo.tm_min &&
		storedTime != -1);  // mktime returns -1 for invalid time
}
string DateTime::displayTime(string format) const {
	const char* formatString = format.c_str();
	std::tm* timeInfo = getLocalTime();
	std::stringstream ss;
	ss << std::put_time(timeInfo, formatString);
	return ss.str();
}

string DateTime::displayDate(string format) const {
	const char* formatString = format.c_str();
	std::tm* timeInfo = getLocalTime();
	std::stringstream ss;
	ss << std::put_time(timeInfo, formatString);
	return ss.str();
}

time_t DateTime::getTime() const {
	return storedTime;
}

int DateTime::getYear() const {
	return getLocalTime()->tm_year + 1900;  // Years since 1900
}


int DateTime::getMonth() const {
	return getLocalTime()->tm_mon + 1;  // Months are zero-based
}

int DateTime::getDay() const {
	return getLocalTime()->tm_mday;
}

int DateTime::getHour() const {
	return getLocalTime()->tm_hour;
}

int DateTime::getMinute() const {
	return getLocalTime()->tm_min;
}

int DateTime::getSecond() const {
	return getLocalTime()->tm_sec;
}

int DateTime::getDayOfWeek() const {
	return getLocalTime()->tm_wday;
}
