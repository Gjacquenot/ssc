CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(decode_unit)
FILE(GLOB SRC DecodeUnit.cpp)

IF (NOT(MSVC))
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
ENDIF()

INCLUDE_DIRECTORIES(${SSC_INCLUDE_DIRS})

ADD_DEFINITIONS(-DNDEBUG)

ADD_LIBRARY(${PROJECT_NAME}_object OBJECT ${SRC})
