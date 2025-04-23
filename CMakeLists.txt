cmake_minimum_required(VERSION 3.28)
project(CrapsGame)

set(CMAKE_CXX_STANDARD 17)

# Add your source files here
set(SOURCES
        main.cpp
        PlayerList.cpp
        PlayerNode.cpp
        BetAVL.cpp
        BetNode.cpp

)

# Add your header files here (optional, but useful for IDEs)
set(HEADERS
        PlayerList.h
        PlayerNode.h
        BetAVL.h
        BetNode.h
)

# Include directories (if your headers are in different directories)
# include_directories(include)

add_executable(CrapsGame ${SOURCES} ${HEADERS})