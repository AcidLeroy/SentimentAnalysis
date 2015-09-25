CMAKE_MINIMUM_REQUIRED(VERSION 3.1.3)

SET(CMAKE_PROJECT_NAME "SentimentAnalysis")

enable_testing()
find_package(Gtest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11" )

ADD_SUBDIRECTORY(src)

