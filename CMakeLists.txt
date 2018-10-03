CMAKE_MINIMUM_REQUIRED(VERSION 3.9)

PROJECT(GraphColoring)

ADD_LIBRARY(graph-coloring SHARED
    Source/coloring_algorithm.cpp
    Source/dsatur.cpp
    Source/mcs.cpp
    Source/lmxrlf.cpp
    Source/tabucol.cpp
    Source/hybrid_dsatur.cpp
    Source/hybrid.cpp
) 

ADD_EXECUTABLE(color Source/main.cpp)
TARGET_LINK_LIBRARIES(color graph-coloring)
