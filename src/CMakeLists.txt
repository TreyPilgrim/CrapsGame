# Find all the source files recursively in the src directory
file(GLOB_RECURSE SOURCE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

# Set output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Define the executable from the source files
add_executable(CrapsGame ${SOURCE_FILES})

# Include directories for header files within the src folder
target_include_directories(CrapsGame PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# If you have headers in subdirectories, you can include them like this:
target_include_directories(CrapsGame PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/bets
    ${CMAKE_CURRENT_SOURCE_DIR}/players
    ${CMAKE_CURRENT_SOURCE_DIR}/game
    ${CMAKE_CURRENT_SOURCE_DIR}/utils
)