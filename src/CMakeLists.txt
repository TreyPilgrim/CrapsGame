cmake_minimum_required(VERSION 3.28)

# Find all the source files recursively in the src directory
file(GLOB_RECURSE SOURCE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

# Set output directory for the final executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Define the executable from the source files
add_executable(CrapsGame ${SOURCE_FILES})

# Include directories for header files
target_include_directories(CrapsGame PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/bets
    ${CMAKE_CURRENT_SOURCE_DIR}/players
    ${CMAKE_CURRENT_SOURCE_DIR}/game
    ${CMAKE_CURRENT_SOURCE_DIR}/utils
)