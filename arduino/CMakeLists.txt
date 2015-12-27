project(host_raspberrypi_gpio)
cmake_minimum_required(VERSION 2.8)

SET(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
SET(HDR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(HDRS
    ${HDR}/buttons.hpp
    ${HDR}/outputs.hpp
    ${HDR}/Player.hpp
    ${HDR}/PlayerManager.hpp
    ${HDR}/main.hpp
    ${HDR}/arduino.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/arduino_onboard/serial_protocol.h

    ${CMAKE_CURRENT_SOURCE_DIR}/../host.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../host_defines.h

    # INIReader class
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/INIReader.h
)
set(SRCS
    ${SRC}/main.cpp
    ${SRC}/buttons.cpp
    ${SRC}/outputs.cpp
    ${SRC}/arduino.cpp
    ${SRC}/Player.cpp
    ${SRC}/PlayerManager.cpp

    # INIReader class
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/INIReader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/ini.c
)

add_library(host_arduino_serial SHARED ${SRCS} ${HDRS})

add_executable(debugger ${SRC}/executable.cpp)
target_link_libraries(debugger host_arduino_serial)

include_directories(${HDR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../libpiga/include/)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -lrt ${CMAKE_CXX_FLAGS}")

