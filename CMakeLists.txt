cmake_minimum_required(VERSION 3.22)

project(AudioAppTest)

set(CMAKE_CXX_STANDARD 23)

set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)

include(cmake/cpm.cmake)

CPMAddPackage(
    NAME JUCE
    GIT_TAG 8.0.0
    VERSION 8.0.0
    GITHUB_REPOSITORY juce-framework/JUCE
    SOURCE_DIR ${LIB_DIR}/juce
)

add_subdirectory(AudioApp)
