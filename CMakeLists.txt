# Works with 3.11 and tested through 3.21
cmake_minimum_required(VERSION 3.11...3.21)

# Project name and a few useful settings. Other commands can pick up the results
project(
  game
  VERSION 0.1
  DESCRIPTION "A game project with CMake"
  LANGUAGES CXX)

find_package(SFML 2 COMPONENTS graphics audio network REQUIRED)

add_subdirectory(src)

add_subdirectory(apps)

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING)
   AND BUILD_TESTING)
  add_subdirectory(tests)
endif()