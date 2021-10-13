cmake_minimum_required(VERSION 3.0.0)
project(HttpTimeSync VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(../HTTPRequest/include)

add_library(${PROJECT_NAME} SHARED HttpTimeSync.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
