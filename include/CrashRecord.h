#ifndef CRASHRECORD_H
#define CRASHRECORD_H

#include <string>
#include <vector>
#include <string_view>
#include <ctime>  // Required for std::tm

class CrashRecord {
public:
    CrashRecord() = default;  // Default constructor
    CrashRecord(const std::vector<std::string_view>& data);
    
    void printRecord() const;

    // Getters for search operations
    std::string getBorough() const;
    int getPersonsInjured() const;
    
    // Date and time related getters
    std::string getCrashDate() const;  // Returns formatted date string
    std::string getCrashTime() const;  // Returns formatted time string
    std::tm getCrashDateTimeTm() const; // Returns the full `std::tm` object with date and time

private:
    std::tm crashDateTime;  // Now using std::tm instead of std::string for date and time
    std::string borough;
    int zipCode;
    float latitude;
    float longitude;
    std::string onStreetName;
    int numberOfPersonsInjured;
};

#endif // CRASHRECORD_H
