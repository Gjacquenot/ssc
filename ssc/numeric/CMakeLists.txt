cmake_minimum_required(VERSION 2.8.8)
project(numeric)

set(SRC almost_equal.cpp
        )

include_directories(${SSC_INCLUDE_DIRS})
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
include_directories(SYSTEM ${GTEST_INCLUDE_DIRS})

ADD_LIBRARY(${PROJECT_NAME}_object OBJECT ${SRC})

add_subdirectory(unit_tests)
