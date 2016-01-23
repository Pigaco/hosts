project(host_raspberrypi_gpio)
cmake_minimum_required(VERSION 2.8)

SET(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
SET(HDR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(ARDUINO_HOST_VERSION_MAJOR "0" CACHE STRING "Major-Version")
set(ARDUINO_HOST_VERSION_MINOR "2" CACHE STRING "Minor-Version")
set(ARDUINO_HOST_VERSION_PATCH "0" CACHE STRING "Patch-Version")
set(ARDUINO_HOST_VERSION_TWEAK "0" CACHE STRING "Tweak-Version")
set(ARDUINO_HOST_VERSION ${ARDUINO_HOST_VERSION_MAJOR}.${ARDUINO_HOST_VERSION_MINOR}.${ARDUINO_HOST_VERSION_PATCH}.${ARDUINO_HOST_VERSION_TWEAK})

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

find_package(Qt5SerialPort)
add_definitions(-DQT_NO_KEYWORDS)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
target_link_libraries(host_arduino_serial Qt5::SerialPort)

add_executable(debugger ${SRC}/executable.cpp)
target_link_libraries(debugger host_arduino_serial)

include_directories(${HDR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

include(GenerateExportHeader)

generate_export_header(host_arduino_serial)

set_property(TARGET host_arduino_serial PROPERTY VESION ${ARDUINO_HOST_VERSION})
set_property(TARGET host_arduino_serial PROPERTY SOVERSION ${ARDUINO_HOST_VERSION_MAJOR})
set_property(TARGET host_arduino_serial PROPERTY
    INTERFACE_piga_MAJOR_VERSION ${ARDUINO_HOST_VERSION_MAJOR})

install(TARGETS host_arduino_serial EXPORT LibhostsArduinoTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include
    RUNTIME DESTINATION bin)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/LibhostsArduinoConfigVersion.cmake"
    VERSION ${ARDUINO_HOST_VERSION}
  COMPATIBILITY AnyNewerVersion
)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/LibhostsArduinoConfig.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/LibhostsArduinoConfig.cmake"
  COPYONLY
)

set(ConfigPackageLocation lib/cmake)

install(EXPORT LibhostsArduinoTargets
  FILE
  LibhostsArduinoTargets.cmake
  NAMESPACE
    Upstream::
  DESTINATION
    ${ConfigPackageLocation}
)
install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/LibhostsArduinoConfigVersion.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/LibhostsArduinoConfig.cmake"
    DESTINATION
        ${ConfigPackageLocation}
)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
    DESTINATION include/piga/hosts/arduino)

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A (libpiga) host for arduino communication. Supports inputs and outputs.")
set(CPACK_PACKAGE_VENDOR "Pigaco")
set(CPACK_PACKAGE_VERSION_MAJOR ${ARDUINO_HOST_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${ARDUINO_HOST_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${ARDUINO_HOST_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION_TWEAK ${ARDUINO_HOST_VERSION_TWEAK})
set(CPACK_DEBIAN_PACKAGE_HOMEPAHE "https://github.com/pigaco/hosts")
set(CPACK_DEBIAN_PACKAGE_NAME "piga-libhosts-arduino")
set(CPACK_PACKAGE_NAME "piga-libhosts-arduino")
set(CPACK_DEBIAN_PACKAGE_DEPENDS
    "libqt5serialport5 (>= 5.3.2-2)")
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Max Heisinger <mail@maximaximal.com>")
include(CPack)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -lrt ${CMAKE_CXX_FLAGS}")

