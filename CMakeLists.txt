CMAKE_MINIMUM_REQUIRED(VERSION 3.9)

PROJECT(graph-coloring)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)

ADD_LIBRARY(graph-coloring SHARED
    Source/coloring_algorithm.cpp
    Source/dsatur.cpp
    Source/mcs.cpp
    Source/lmxrlf.cpp
    Source/tabucol.cpp
    Source/hybrid_dsatur.cpp
    Source/hybrid_lmxrlf.cpp
) 

ADD_EXECUTABLE(color-test
    Source/test.cpp
    Tests/dsatur_tests.cpp
    Tests/lmxrlf_tests.cpp
    Tests/mcs_tests.cpp
    Tests/tabucol_tests.cpp
    Tests/hybrid_lmxrlf_tests.cpp
    Tests/hybrid_dsatur_tests.cpp
)

ADD_EXECUTABLE(color 
    Source/main.cpp
)

TARGET_LINK_LIBRARIES(color-test graph-coloring)
TARGET_LINK_LIBRARIES(color-test gtest)

TARGET_LINK_LIBRARIES(color graph-coloring)
