cmake_minimum_required(VERSION 3.14)
project(cppy VERSION 0.1 DESCRIPTION "Open-source C++ library focused on bringing Python's methods to C++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

option(CPPY_LOCAL_INSTALL "Install cppy locally (Default OFF)" OFF)

add_library(cppy INTERFACE)

target_include_directories(cppy
    INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/cppyConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion)

if (CPPY_LOCAL_INSTALL)
    message(STATUS "Installing cppy locally")
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Install prefix" FORCE)
    install(TARGETS cppy
        EXPORT cppyTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib COMPONENT Runtime
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib COMPONENT Development
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin COMPONENT Runtime
        BUNDLE DESTINATION ${CMAKE_INSTALL_PREFIX}/bin COMPONENT Runtime)

    configure_package_config_file(
        "${PROJECT_SOURCE_DIR}/cmake/cppyConfig.cmake.in"
        "${PROJECT_BINARY_DIR}/cppyConfig.cmake"
        INSTALL_DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/cmake/cppy)
        
    install(EXPORT cppyTargets DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/cmake/cppy)
    install(FILES "${PROJECT_BINARY_DIR}/cppyConfigVersion.cmake"
                "${PROJECT_BINARY_DIR}/cppyConfig.cmake"
            DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/cmake/cppy)

    install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR})
else()
    message(STATUS "Installing cppy system-wide")
    install(TARGETS cppy
    EXPORT cppyTargets
    LIBRARY DESTINATION lib COMPONENT Runtime
    ARCHIVE DESTINATION lib COMPONENT Development
    RUNTIME DESTINATION bin COMPONENT Runtime
    BUNDLE DESTINATION bin COMPONENT Runtime)

    configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/cppyConfig.cmake.in"
    "${PROJECT_BINARY_DIR}/cppyConfig.cmake"
    INSTALL_DESTINATION lib/cmake/cppy)

    install(EXPORT cppyTargets DESTINATION lib/cmake/cppy)
    install(FILES "${PROJECT_BINARY_DIR}/cppyConfigVersion.cmake"
            "${PROJECT_BINARY_DIR}/cppyConfig.cmake"
        DESTINATION lib/cmake/cppy)

    install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
endif()
