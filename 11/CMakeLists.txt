cmake_minimum_required(VERSION 3.20)

project(day11)
find_package(Boost REQUIRED)

add_executable(${PROJECT_NAME} day11.cpp)


target_link_libraries(${PROJECT_NAME}
PRIVATE
aoc_lib
${Boost_LIBRARY_DIRS})

target_include_directories(${PROJECT_NAME}
PRIVATE
${Boost_INCLUDE_DIRS})

