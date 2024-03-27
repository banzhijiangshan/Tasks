cmake_minimum_required(VERSION 3.0)

project(MyProject)
set(CMAKE_CXX_STANDARD 17)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(MuCache ${SOURCES})
