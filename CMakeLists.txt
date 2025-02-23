cmake_minimum_required(VERSION 3.10)
project(CrashDataProcessor)

set(CMAKE_CXX_STANDARD 17)

# Include the header directory (contains CrashRecord.h, CrashRecordFacade.h, QueryStrategy.h)
include_directories(include)

# Enable OpenMP
find_package(OpenMP REQUIRED)

# Add the source files for building the executable
add_executable(CrashDataProcessor 
    src/main.cpp 
    src/CrashRecord.cpp 
    src/CrashRecordFacade.cpp 
    src/SearchStrategies.cpp
)

# Link OpenMP to the target if found
if(OpenMP_CXX_FOUND)
    target_link_libraries(CrashDataProcessor PUBLIC OpenMP::OpenMP_CXX)
    target_compile_options(CrashDataProcessor PUBLIC ${OpenMP_CXX_FLAGS})
endif()

# Special handling for Apple Clang/GCC with libomp
if(APPLE)
    message(STATUS "Configuring for Apple platform with ARM64 support")
    
    # Add libomp include and library directories explicitly
    target_include_directories(CrashDataProcessor PRIVATE /opt/homebrew/Cellar/libomp/19.1.7/include)
    target_link_directories(CrashDataProcessor PRIVATE /opt/homebrew/Cellar/libomp/19.1.7/lib)
    
    # Link against libomp explicitly
    target_link_libraries(CrashDataProcessor PRIVATE omp)
    
    # Set compile and link flags for OpenMP
    target_compile_options(CrashDataProcessor PRIVATE -Xpreprocessor -fopenmp)
    target_link_libraries(CrashDataProcessor PRIVATE -lomp)
endif()
