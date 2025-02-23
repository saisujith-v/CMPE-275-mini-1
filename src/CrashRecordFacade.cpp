#include "CrashRecordFacade.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <omp.h>

// Split function to handle CSV parsing with a fixed size of 29 tokens
std::vector<std::string_view> split(std::string_view line, char delimiter) {
    const size_t fixed_size = 30;  // Fixed number of columns expected
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
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: File not found or could not be opened: " 
                  << filename << std::endl;
        return;
    }
    std::cout << "File opened successfully: " << filename << std::endl;

    // Read lines into memory
    std::vector<std::string> lines;
    std::string line;

    // Skip header
    std::getline(file, line);

    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    std::cout << "File read completed, processing " << lines.size() << " records..." << std::endl;
    // Preallocate space for records
    auto record_size = lines.size();
    records.resize(record_size);
    omp_set_num_threads(5);
    // Parallel parse
    #pragma omp parallel for
    for (long long i = 0; i < static_cast<long long>(lines.size()); i++) {
        // Split line into tokens (string_view)
        std::vector<std::string_view> dataViews = split(lines[i], ',');
        records[i] = CrashRecord(dataViews);
    }
    std::cout << "File Processing number of threads: " << omp_get_max_threads() << std::endl;
    std::cout << "Total records processed: " << lines.size() << std::endl;
    std::cout << "File closed: " << filename << std::endl;
}



// Perform the search using a given strategy
std::vector<CrashRecord> CrashRecordFacade::search(QueryStrategy* strategy) {
    return strategy->execute(records);
}
