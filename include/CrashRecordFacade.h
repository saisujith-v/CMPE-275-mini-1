#ifndef CRASHRECORDFACADE_H
#define CRASHRECORDFACADE_H

#include <string>
#include <vector>
#include "CrashRecord.h"
#include "QueryStrategy.h"

class CrashRecordFacade {
public:
    // Constructor: Takes the filename of the CSV to read
    CrashRecordFacade(const std::string& filename);

    // Simple query functions using strategy pattern
    std::vector<CrashRecord> search(QueryStrategy* strategy);

private:
    std::vector<CrashRecord> records;  // List of crash records
};

#endif // CRASHRECORDFACADE_H
