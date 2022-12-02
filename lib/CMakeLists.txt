cmake_minimum_required(VERSION 3.20)

include(FetchContent)
FetchContent_Declare(
  range-v3
  GIT_REPOSITORY https://github.com/ericniebler/range-v3.git
  GIT_TAG        0.12.0
  )

FetchContent_MakeAvailable(range-v3)

project(aoc_lib)
set(CMAKE_CXX_STANDARD 20)
find_package(Boost REQUIRED)
add_library(${PROJECT_NAME} STATIC src/aoc_lib.cpp)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
  ${Boost_LIBRARY_DIRS}
  PUBLIC
  range-v3
)

target_include_directories(${PROJECT_NAME}
  PRIVATE
  ${Boost_INCLUDE_DIRS}
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  range-v3/include
)

