cmake_minimum_required(VERSION 3.1)

option(SCOPE_EXIT_BUILD_SAMPLES "Build scope exit's samples." ON)

project(ScopeExit VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# make sure install paths work on all platforms
if(NOT CMAKE_INSTALL_INCLUDEDIR)
    include(GNUInstallDirs)
endif()

add_library(ScopeExit INTERFACE)
target_include_directories(ScopeExit 
    INTERFACE 
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

add_library(ScopeExit::ScopeExit ALIAS ScopeExit)

# workaround for stand-alone build detection under windows (as it's case insensitive)
get_filename_component(CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR} ABSOLUTE)
get_filename_component(SOURCE_DIR ${CMAKE_SOURCE_DIR} ABSOLUTE)

# check if building as a stand-alone project
if(${CURRENT_SOURCE_DIR} STREQUAL ${SOURCE_DIR} AND SCOPE_EXIT_BUILD_SAMPLES)
    # add a pseudo-project to make project headers visible in IDE
    file(GLOB_RECURSE SCOPE_EXIT_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
    add_library(ScopeExit-h STATIC ${SCOPE_EXIT_HEADERS})
    set_target_properties(ScopeExit-h PROPERTIES LINKER_LANGUAGE CXX)
    set_target_properties(ScopeExit-h PROPERTIES FOLDER Include)

    add_subdirectory(samples)
endif()

install(TARGETS ScopeExit EXPORT ScopeExitConfig)

install(
    EXPORT ScopeExitConfig
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ScopeExit
    NAMESPACE ScopeExit::
)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ScopeExit
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.h" # headers only
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/ScopeExitConfigVersion.cmake"
    COMPATIBILITY AnyNewerVersion
)

install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/ScopeExitConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ScopeExit
)