#ifndef DATE_UTILS_H
#define DATE_UTILS_H

#include <ctime>

// Overloading < operator for std::tm
inline bool operator<(const std::tm& lhs, const std::tm& rhs) {
    if (lhs.tm_year != rhs.tm_year) return lhs.tm_year < rhs.tm_year;
    if (lhs.tm_mon  != rhs.tm_mon)  return lhs.tm_mon  < rhs.tm_mon;
    if (lhs.tm_mday != rhs.tm_mday) return lhs.tm_mday < rhs.tm_mday;
    if (lhs.tm_hour != rhs.tm_hour) return lhs.tm_hour < rhs.tm_hour;
    if (lhs.tm_min  != rhs.tm_min)  return lhs.tm_min  < rhs.tm_min;
    return lhs.tm_sec < rhs.tm_sec;
}

#endif // DATE_UTILS_H
