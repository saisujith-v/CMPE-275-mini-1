#ifndef SEARCHSTRATEGIES_H
#define SEARCHSTRATEGIES_H

#include "QueryStrategy.h"
#include <string>

// Search by Borough Strategy
class SearchByBoroughStrategy : public QueryStrategy {
public:
    SearchByBoroughStrategy(const std::string& borough);
    std::vector<CrashRecord> execute(const std::vector<CrashRecord>& records) override;

private:
    std::string borough;
};

// Search by Injury Count Strategy
class SearchByInjuryCountStrategy : public QueryStrategy {
public:
    SearchByInjuryCountStrategy(int minInjuryCount);
    std::vector<CrashRecord> execute(const std::vector<CrashRecord>& records) override;

private:
    int minInjuryCount;
};

// Search by Date Range Strategy
class SearchByDateRangeStrategy : public QueryStrategy {
public:
    SearchByDateRangeStrategy(const std::string& startDate, const std::string& endDate);
    std::vector<CrashRecord> execute(const std::vector<CrashRecord>& records) override;

private:
    std::string startDate;
    std::string endDate;
};

#endif // SEARCHSTRATEGIES_H
