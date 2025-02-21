#include "SearchStrategies.h"
#include "CrashRecord.h"
#include <iomanip>
#include <ctime>
#include <sstream>
#include "DateUtils.h"
#include <iostream>
#include "DateTimeParser.h"
#include <omp.h>

// Search by Borough Strategy
SearchByBoroughStrategy::SearchByBoroughStrategy(const std::string& borough) : borough(borough) {}

std::vector<CrashRecord> SearchByBoroughStrategy::execute(const std::vector<CrashRecord>& records) {
    std::vector<CrashRecord> results;

    int num_threads = 5; // Set desired number of threads
    omp_set_num_threads(num_threads);
    std::cout << "Number of threads: " << omp_get_max_threads() << std::endl;
    #pragma omp parallel
    {
        std::vector<CrashRecord> localResults;
        #pragma omp for nowait
        for (size_t i = 0; i < records.size(); ++i) {
            if (records[i].getBorough() == borough) {
                localResults.push_back(records[i]);
            }
        }

        #pragma omp critical
        results.insert(results.end(), localResults.begin(), localResults.end());
    }
    return results;
}

// Search by Injury Count Strategy
SearchByInjuryCountStrategy::SearchByInjuryCountStrategy(int minInjuryCount) : minInjuryCount(minInjuryCount) {}

std::vector<CrashRecord> SearchByInjuryCountStrategy::execute(const std::vector<CrashRecord>& records) {
    std::vector<CrashRecord> results;

    #pragma omp parallel num_threads(5)
    {
        std::vector<CrashRecord> localResults;
        #pragma omp for nowait
        for (size_t i = 0; i < records.size(); ++i) {
            if (records[i].getPersonsInjured() >= minInjuryCount) {
                localResults.push_back(records[i]);
            }
        }

        #pragma omp critical
        results.insert(results.end(), localResults.begin(), localResults.end());
    }
    return results;
}

// Search by Date Range Strategy
SearchByDateRangeStrategy::SearchByDateRangeStrategy(const std::string& startDate, const std::string& endDate)
    : startDate(startDate), endDate(endDate) {}

std::vector<CrashRecord> SearchByDateRangeStrategy::execute(const std::vector<CrashRecord>& records) {
    std::vector<CrashRecord> results;

    std::tm startTm = parseDateTime(startDate, "00:00");
    std::tm endTm = parseDateTime(endDate, "23:59");

    #pragma omp parallel num_threads(5)
    {
        std::vector<CrashRecord> localResults;
        #pragma omp for nowait
        for (size_t i = 0; i < records.size(); ++i) {
            std::tm recordTm = records[i].getCrashDateTimeTm();

            if (!(recordTm < startTm) && !(endTm < recordTm)) {
                localResults.push_back(records[i]);
            }
        }

        #pragma omp critical
        results.insert(results.end(), localResults.begin(), localResults.end());
    }

    return results;
}