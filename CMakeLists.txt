cmake_minimum_required(VERSION 3.28)
project(Craps2024)

set(CMAKE_CXX_STANDARD 17)

# Add your source files here
set(SOURCES
        main.cpp
        PlayerList.cpp
        PlayerNode.cpp
        BetList.cpp
        BetNode.cpp
)

# Add your header files here (optional, but useful for IDEs)
set(HEADERS
        PlayerList.h
        PlayerNode.h
        BetLinkedList.h
        BetNode.h
)

# Include directories (if your headers are in different directories)
# include_directories(include)

add_executable(Craps2024 ${SOURCES} ${HEADERS})