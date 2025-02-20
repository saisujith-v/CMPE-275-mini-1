#include "CrashRecordFacade.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Split function to handle CSV parsing
std::vector<std::string_view> split(std::string_view line, char delimiter) {
    std::vector<std::string_view> tokens;
    size_t start = 0;
    
    for (size_t i = 0; i < line.size(); ++i) {
        if (line[i] == delimiter) {
            tokens.push_back(line.substr(start, i - start));
            start = i + 1;
        }
    }
    // Add the last token
    tokens.push_back(line.substr(start));
    return tokens;
}

// Constructor that reads the data from CSV
CrashRecordFacade::CrashRecordFacade(const std::string& filename) {
    std::cout << "Attempting to open file: " << filename << std::endl;

    std::ifstream file(filename);
    
    // Check if file exists and is open
    if (!file.is_open()) {
        std::cerr << "Error: File not found or could not be opened: " << filename << std::endl;
        return;
    } else {
        std::cout << "File opened successfully: " << filename << std::endl;
    }

    std::string line;
    // Skip the header
    std::getline(file, line);

    int count = 0;
    while (std::getline(file, line)) {
        std::vector<std::string_view> data = split(line, ',');  // Split the line by comma
        count++;
        records.emplace_back(data);  // Pass the data vector which contains string_view objects
        std::cout << "Processed record #" << count << std::endl;
    }
    
    std::cout << "Total records processed: " << count << std::endl;

    file.close();
    std::cout << "File closed: " << filename << std::endl;
}


// Perform the search using a given strategy
std::vector<CrashRecord> CrashRecordFacade::search(QueryStrategy* strategy) {
    return strategy->execute(records);
}
