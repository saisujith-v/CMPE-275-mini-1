#include "CrashRecordFacade.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Split function to handle CSV parsing with a fixed size of 29 tokens
std::vector<std::string_view> split(std::string_view line, char delimiter) {
    const size_t fixed_size = 29;  // Fixed number of columns expected
    std::vector<std::string_view> tokens(fixed_size);  // Initialize with 29 empty elements

    size_t start = 0;
    size_t token_index = 0;

    for (size_t i = 0; i < line.size() && token_index < fixed_size; ++i) {
        if (line[i] == delimiter) {
            tokens[token_index++] = line.substr(start, i - start);
            start = i + 1;
        }
    }

    // Add the last token if there's still room
    if (token_index < fixed_size) {
        tokens[token_index] = line.substr(start);
    }

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
        std::cout<< "Processing record: " << count << std::endl;
        records.emplace_back(data);  // Pass the data vector which contains string_view objects
    }
    
    std::cout << "Total records processed: " << count << std::endl;

    file.close();
    std::cout << "File closed: " << filename << std::endl;
}


// Perform the search using a given strategy
std::vector<CrashRecord> CrashRecordFacade::search(QueryStrategy* strategy) {
    return strategy->execute(records);
}
