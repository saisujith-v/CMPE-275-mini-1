cmake_minimum_required(VERSION 3.10)
project(CrashDataProcessor)

set(CMAKE_CXX_STANDARD 17)

# Include the header directory (contains CrashRecord.h, CrashRecordFacade.h, QueryStrategy.h)
include_directories(include)

# Add the source files for building the executable
add_executable(CrashDataProcessor 
    src/main.cpp 
    src/CrashRecord.cpp 
    src/CrashRecordFacade.cpp 
    src/SearchStrategies.cpp
)
