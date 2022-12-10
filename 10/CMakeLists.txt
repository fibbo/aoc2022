cmake_minimum_required(VERSION 3.20)

project(day10)
find_package(Boost REQUIRED)

add_executable(${PROJECT_NAME} day10.cpp)

add_executable(${PROJECT_NAME}_2 day10_2.cpp)

target_link_libraries(${PROJECT_NAME}
PRIVATE
aoc_lib
${Boost_LIBRARY_DIRS})

target_include_directories(${PROJECT_NAME}
PRIVATE
${Boost_INCLUDE_DIRS})


target_link_libraries(${PROJECT_NAME}_2
PRIVATE
aoc_lib
${Boost_LIBRARY_DIRS})

target_include_directories(${PROJECT_NAME}_2
PRIVATE
${Boost_INCLUDE_DIRS})


