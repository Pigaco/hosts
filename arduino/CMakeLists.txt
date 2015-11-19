project(host_raspberrypi_gpio)
cmake_minimum_required(VERSION 2.8)

SET(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/)
SET(HDR ${CMAKE_CURRENT_SOURCE_DIR}/include/)

SET(HDR ${CMAKE_CURRENT_SOURCE_DIR}/../src/)

set(HDRS
    ${HDR}/buttons.hpp
    ${HDR}/outputs.hpp

    # INIReader class
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/INIReader.h
)
set(SRCS
    ${SRC}/host.cpp
    ${SRC}/buttons.cpp
    ${SRC}/outputs.cpp

    # INIReader class
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/INIReader.cpp
)

add_library(host_raspberrypi_gpio SHARED ${SRCS} ${HDRS})

include_directories(${HDR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../libpiga/include/)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -lrt ${CMAKE_CXX_FLAGS}")

