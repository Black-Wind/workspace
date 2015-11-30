PROJECT(Test)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_subdirectory(./2-3-4Tree)
add_subdirectory(./alg)

AUX_SOURCE_DIRECTORY(. DIR_TEST_SRCS)
ADD_EXECUTABLE(Test ${DIR_TEST_SRCS})
target_link_libraries(Test Tree234)