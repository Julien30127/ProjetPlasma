cmake_minimum_required(VERSION 3.10)
project(MHD_SPH CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES "src/*.cpp")
add_executable(mhd_sph ${SOURCES})
target_include_directories(mhd_sph PRIVATE "headers")