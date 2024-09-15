cmake_minimum_required(VERSION 3.20)
project(TIOTest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

function(CloneTerreateGraphics)
  message(STATUS "Cloning TerreateGraphics...")
  set(TERREATEGRAPHICS_BUILD_TESTS OFF)
  FetchContent_Declare(
    terreate_graphics
    GIT_REPOSITORY https://github.com/uPiscium/TerreateGraphics.git
    GIT_TAG main)
  FetchContent_MakeAvailable(terreate_graphics)
  message(STATUS "TerreateGraphics cloned.")
endfunction()

function(SetLibs)
  cloneterreategraphics()
  target_link_libraries(${PROJECT_NAME} TerreateIO)
  target_link_libraries(${PROJECT_NAME} TerreateGraphics)
endfunction()

function(SetIncludes)
  target_include_directories(${PROJECT_NAME} PRIVATE TerreateGraphics)
  target_include_directories(${PROJECT_NAME} PUBLIC ../includes)
endfunction()

function(Build)
  add_executable(${PROJECT_NAME} TIOTest.cpp)
  set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                                   ${CMAKE_BINARY_DIR}/bin)
  setlibs()
  setincludes()
endfunction()

build()
