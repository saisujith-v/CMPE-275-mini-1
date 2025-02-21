#ifndef QUERYSTRATEGY_H
#define QUERYSTRATEGY_H

#include <vector>
#include "CrashRecord.h"

class QueryStrategy {
public:
    virtual std::vector<CrashRecord> execute(const std::vector<CrashRecord>& records) = 0;
    virtual ~QueryStrategy() = default;
};

#endif // QUERYSTRATEGY_H
