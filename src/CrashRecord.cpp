#include "CrashRecord.h"
#include "DateTimeParser.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <ctime>

// Function to parse a date and time string into a `std::tm` object with error handling
std::tm parseDateTime(const std::string& dateStr, const std::string& timeStr) {
    std::tm tmDateTime = {};

    try {
        // Parse Date (MM/DD/YYYY)
        std::istringstream ssDate(dateStr);
        ssDate >> std::get_time(&tmDateTime, "%m/%d/%Y");  
        if (ssDate.fail()) {
            throw std::runtime_error("Invalid date format: " + dateStr);
        }

        // Parse Time (HH:MM)
        std::istringstream ssTime(timeStr);
        ssTime >> std::get_time(&tmDateTime, "%H:%M");
        if (ssTime.fail()) {
            throw std::runtime_error("Invalid time format: " + timeStr);
        }

    } catch (const std::exception& e) {
        std::cerr << "Warning: Skipping invalid date/time (" << dateStr << " " << timeStr << "). Using default values. Error: " << e.what() << std::endl;

        // Set default values (e.g., Jan 1, 1970, 00:00)
        tmDateTime = {};
        tmDateTime.tm_mday = 1;
        tmDateTime.tm_mon = 0;   // January
        tmDateTime.tm_year = 70; // 1970 (years since 1900)
        tmDateTime.tm_hour = 0;
        tmDateTime.tm_min = 0;
        tmDateTime.tm_sec = 0;
    }

    return tmDateTime;
}


// Constructor: Initializes a CrashRecord object using CSV row data
CrashRecord::CrashRecord(const std::vector<std::string_view>& data) {
    // Convert date and time strings to std::tm
    crashDateTime = parseDateTime(std::string(data[0]), std::string(data[1]));  
    borough = data[2];
    
    // Handling latitude and longitude conversion safely
    latitude = data[4].empty() ? 0.0f : std::stof(std::string(data[4]));  // Convert string_view to string before parsing
    longitude = data[5].empty() ? 0.0f : std::stof(std::string(data[5]));

    onStreetName = data[7];  
    
    // Safe conversion for number of persons injured
    try {
        numberOfPersonsInjured = data[10].empty() ? 0 : std::stoi(std::string(data[10]));  // Convert string_view to string
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument for number of persons injured: " << data[10] << ", setting to 0." << std::endl;
        numberOfPersonsInjured = 0;
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range value for number of persons injured: " << data[10] << ", setting to 0." << std::endl;
        numberOfPersonsInjured = 0;
    }
}

// Print the crash record
void CrashRecord::printRecord() const {
    std::cout << std::left << std::setw(15) << "Crash Date"
              << std::setw(10) << "Time"
              << std::setw(18) << "Persons Injured" << std::endl;

    std::cout << std::left << std::setw(15) << getCrashDate()
              << std::setw(10) << getCrashTime()
              << std::setw(18) << (numberOfPersonsInjured == 0 ? "N/A" : std::to_string(numberOfPersonsInjured))
              << std::endl;
}

// Getter for borough
std::string CrashRecord::getBorough() const {
    return borough;
}

// Getter for persons injured
int CrashRecord::getPersonsInjured() const {
    return numberOfPersonsInjured;
}

// Getter to return the `std::tm` crash date-time
std::tm CrashRecord::getCrashDateTimeTm() const {
    return crashDateTime;
}

// Getter to return the crash date as a formatted string
std::string CrashRecord::getCrashDate() const {
    std::ostringstream oss;
    oss << std::put_time(&crashDateTime, "%m/%d/%Y");
    return oss.str();
}

// Getter to return the crash time as a formatted string
std::string CrashRecord::getCrashTime() const {
    std::ostringstream oss;
    oss << std::put_time(&crashDateTime, "%H:%M");
    return oss.str();
}
