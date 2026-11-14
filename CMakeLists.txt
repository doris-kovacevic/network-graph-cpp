cmake_minimum_required(VERSION 3.10)
project(SocialNetworkGraph CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(graph
    src/main.cpp
    src/GraphPtOne.cpp
    src/GraphPtTwo.cpp
)
