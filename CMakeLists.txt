CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_PROJECT_NAME "SentimentAnalysis")

include_directories(${GTEST_INCLUDE_DIRS} ${OLEANDAR_STEMMING})
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11" )
message("Oleandar stemming path: " ${OLEANDAR_STEMMING})

ADD_SUBDIRECTORY(lib/gtest-1.7.0)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
ADD_SUBDIRECTORY(src)

