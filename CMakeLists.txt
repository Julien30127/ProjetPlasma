cmake_minimum_required(VERSION 3.10)

project(SimulationPlasma CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(simu_plasma ${SOURCES})

target_include_directories(simu_plasma PRIVATE "${PROJECT_SOURCE_DIR}/headers")