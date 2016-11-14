project(host)
cmake_minimum_required(VERSION 2.8)

set(HOSTS_VERSION_MAJOR "0" CACHE STRING "Major-Version")
set(HOSTS_VERSION_MINOR "8" CACHE STRING "Minor-Version")
set(HOSTS_VERSION_PATCH "0" CACHE STRING "Patch-Version")
set(HOSTS_VERSION_TWEAK "0" CACHE STRING "Tweak-Version")
set(HOSTS_VERSION ${HOSTS_VERSION_MAJOR}.${HOST_VERSION_MINOR}.${HOST_VERSION_PATCH}.${HOST_VERSION_TWEAK})

set(HDRS
    ${CMAKE_CURRENT_SOURCE_DIR}/host.h
    ${CMAKE_CURRENT_SOURCE_DIR}/host_defines.h
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/host_defines.h.in
    ${CMAKE_CURRENT_SOURCE_DIR}/host_defines.h)

install(FILES 
        ${HDRS}
    DESTINATION 
        include/piga/hosts
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/LibpigaHostsConfigVersion.cmake"
    VERSION ${HOSTS_VERSION}
    COMPATIBILITY AnyNewerVersion
)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/LibpigaHostsConfig.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/LibpigaHostsConfig.cmake"
    COPYONLY
)

set(ConfigPackageLocation lib/cmake)

install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/LibpigaHostsConfigVersion.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/LibpigaHostsConfig.cmake"
  DESTINATION
    ${ConfigPackageLocation}
)

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Header files for hosts development and compilation.")
set(CPACK_PACKAGE_VENDOR "Pigaco")
set(CPACK_PACKAGE_VERSION_MAJOR ${HOSTS_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${HOSTS_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${HOSTS_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION_TWEAK ${HOSTS_VERSION_TWEAK})
set(CPACK_DEBIAN_PACKAGE_HOMEPAHE "https://github.com/pigaco/hosts")
set(CPACK_DEBIAN_PACKAGE_NAME "piga-libhosts-dev")
set(CPACK_PACKAGE_NAME "piga-libhosts-dev")
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Max Heisinger <mail@maximaximal.com>")
include(CPack)
