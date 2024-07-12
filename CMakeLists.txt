cmake_minimum_required(VERSION 3.28)
project(Craps2024)

set(CMAKE_CXX_STANDARD 17)

# Add your source files here
set(SOURCES
        main.cpp
        Player.cpp
        BetsLinkedList.cpp
        Node.cpp
)

# Add your header files here (optional, but useful for IDEs)
set(HEADERS
        Player.h
        BetsLinkedList.h
        Node.h
        BetsLinkedList.cpp
)

# Include directories (if your headers are in different directories)
# include_directories(include)

add_executable(Craps2024 ${SOURCES} ${HEADERS})