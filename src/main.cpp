#include <iostream>
#include "CrashRecordFacade.h"
#include "SearchStrategies.h"

int main() {
    // Facade object to manage crash records
    CrashRecordFacade facade("/Users/saisujithvalluru/Desktop/class-projects/mini-1.csv");

    // Query 1: Search by Borough (BROOKLYN)
    SearchByBoroughStrategy boroughStrategy("BROOKLYN");
    std::vector<CrashRecord> boroughResults = facade.search(&boroughStrategy);
    std::cout << "Records in BROOKLYN: " << boroughResults.size() << std::endl;

    // Query 2: Search by Injury Count (10 or more injuries)
    SearchByInjuryCountStrategy injuryStrategy(10);
    std::vector<CrashRecord> injuryResults = facade.search(&injuryStrategy);
    std::cout << "Records with more than 10 injuries: " << injuryResults.size() << std::endl;

    // Query 3: Search by Date Range (2023)
    SearchByDateRangeStrategy dateRangeStrategy("01/01/2023", "12/31/2023");
    std::vector<CrashRecord> dateRangeResults = facade.search(&dateRangeStrategy);
    std::cout << "Records in 2023: " << dateRangeResults.size() << std::endl;

    return 0;
}
