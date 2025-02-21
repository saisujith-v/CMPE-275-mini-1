#include "SearchStrategies.h"
#include "CrashRecord.h"
#include <iomanip>
#include <ctime>
#include <sstream>
#include "DateUtils.h"
#include <iostream>
#include "DateTimeParser.h"

// Search by Borough Strategy
SearchByBoroughStrategy::SearchByBoroughStrategy(const std::string& borough) : borough(borough) {}

std::vector<CrashRecord> SearchByBoroughStrategy::execute(const std::vector<CrashRecord>& records) {
    std::vector<CrashRecord> results;
    for (const auto& record : records) {
        if (record.getBorough() == borough) {
            results.push_back(record);
        }
    }
    return results;
}

// Search by Injury Count Strategy
SearchByInjuryCountStrategy::SearchByInjuryCountStrategy(int minInjuryCount) : minInjuryCount(minInjuryCount) {}

std::vector<CrashRecord> SearchByInjuryCountStrategy::execute(const std::vector<CrashRecord>& records) {
    std::vector<CrashRecord> results;
    for (const auto& record : records) {
        if (record.getPersonsInjured() >= minInjuryCount) {
            results.push_back(record);
        }
    }
    return results;
}

// Search by Date Range Strategy
SearchByDateRangeStrategy::SearchByDateRangeStrategy(const std::string& startDate, const std::string& endDate)
    : startDate(startDate), endDate(endDate) {}

// Function to parse a date string (MM/DD/YYYY) into a `std::tm` struct
std::tm parseDate(const std::string& dateStr) {
    std::tm tmDate = {};
    std::istringstream ss(dateStr);
    ss >> std::get_time(&tmDate, "%m/%d/%Y"); // Format: MM/DD/YYYY

    if (ss.fail()) {
        throw std::runtime_error("Invalid date format: " + dateStr);
    }
    return tmDate;
}

std::vector<CrashRecord> SearchByDateRangeStrategy::execute(const std::vector<CrashRecord>& records) {
    std::vector<CrashRecord> results;

    std::tm startTm = parseDateTime(startDate, "00:00");
    std::tm endTm = parseDateTime(endDate, "23:59");

    for (const auto& record : records) {
        std::tm recordTm = record.getCrashDateTimeTm(); // Get the std::tm object from the record

        // Directly compare std::tm objects using overloaded operators
        if (!(recordTm < startTm) && !(endTm < recordTm)) {
            results.push_back(record);
        }
    }

    return results;
}
