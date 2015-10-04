CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_PROJECT_NAME "SentimentAnalysis")
SET(OLEANDER_INCLUDE_DIRS lib/OleanderStemmingLibrary)

include_directories(${GTEST_INCLUDE_DIRS} ${OLEANDER_INCLUDE_DIRS})
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11" )

ADD_SUBDIRECTORY(lib/gtest-1.7.0)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
ADD_SUBDIRECTORY(src)

