#include <iostream>
#include <chrono>
#include "CrashRecordFacade.h"
#include "SearchStrategies.h"

int main() {
    // Start timing the entire process
    auto totalStart = std::chrono::high_resolution_clock::now();

    // Facade object to manage crash records
    auto start = std::chrono::high_resolution_clock::now();
    CrashRecordFacade facade("/Users/saisujithvalluru/Desktop/class-projects/mini-1.csv");
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken to read the file: " << duration.count() << " seconds" << std::endl;

    // Query 1: Search by Borough (BROOKLYN)
    start = std::chrono::high_resolution_clock::now();
    SearchByBoroughStrategy boroughStrategy("BROOKLYN");
    std::vector<CrashRecord> boroughResults = facade.search(&boroughStrategy);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "Records in BROOKLYN: " << boroughResults.size() 
              << " (Time taken: " << duration.count() << " seconds)" << std::endl;

    // Query 2: Search by Injury Count (10 or more injuries)
    start = std::chrono::high_resolution_clock::now();
    SearchByInjuryCountStrategy injuryStrategy(10);
    std::vector<CrashRecord> injuryResults = facade.search(&injuryStrategy);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "Records with more than 10 injuries: " << injuryResults.size() 
              << " (Time taken: " << duration.count() << " seconds)" << std::endl;

    // Query 3: Search by Date Range (2023)
    start = std::chrono::high_resolution_clock::now();
    SearchByDateRangeStrategy dateRangeStrategy("01/01/2023", "12/31/2023");
    std::vector<CrashRecord> dateRangeResults = facade.search(&dateRangeStrategy);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "Records in 2023: " << dateRangeResults.size() 
              << " (Time taken: " << duration.count() << " seconds)" << std::endl;

    // End timing the entire process
    auto totalEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> totalDuration = totalEnd - totalStart;
    std::cout << "Total time taken for the entire process: " 
              << totalDuration.count() << " seconds" << std::endl;

    return 0;
}
