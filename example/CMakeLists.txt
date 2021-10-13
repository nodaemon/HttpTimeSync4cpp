cmake_minimum_required(VERSION 3.0.0)
project(example VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(../src)
add_subdirectory(../src HttpTimeSync)

add_executable(Example Example.cpp)
target_link_libraries(Example HttpTimeSync)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)