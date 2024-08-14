cmake_minimum_required(VERSION 3.20)
option(TERREATEIO_BUILD_TESTS "Build tests" ON)

add_subdirectory(impls)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fsanitize=address")

if(TERREATEIO_BUILD_TESTS)
  add_subdirectory(tests)
endif()
