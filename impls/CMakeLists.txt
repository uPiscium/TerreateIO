cmake_minimum_required(VERSION 3.20)
project(TerreateIO)
message(STATUS "Project name : " ${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
message(STATUS "C++ standard : " ${CMAKE_CXX_STANDARD})

include(FetchContent)

function(CloneTerreateCore)
  message(STATUS "Cloning TerreateCore...")
  set(TERREATECORE_BUILD_TESTS OFF)
  FetchContent_Declare(
    terreate_core
    GIT_REPOSITORY https://github.com/uPiscium/TerreateCore.git
    GIT_TAG main)
  FetchContent_MakeAvailable(terreate_core)
  message(STATUS "TerreateCore cloned.")
endfunction()

function(SetIncludes)
  target_include_directories(${PROJECT_NAME} PUBLIC ../includes/deps)
  target_include_directories(${PROJECT_NAME} PUBLIC ../includes)
endfunction()

function(SetLibs)
  cloneterreatecore()
  target_link_libraries(${PROJECT_NAME} PUBLIC TerreateCore)
endfunction()

function(Build)
  add_library(${PROJECT_NAME} STATIC buffer.cpp parser.cpp)
  set_target_properties(
    ${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
                               LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  setincludes()
  setlibs()
endfunction()

build()
