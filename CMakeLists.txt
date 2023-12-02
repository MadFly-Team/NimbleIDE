# make sure the minimum cmake version is compatible with your compiler
cmake_minimum_required(VERSION 3.27.0)

# set a project name and version number
project(NimbleIDESuite VERSION 0.0.1)

# set C Make to use the C++17 Language version
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 20)

include(ExternalProject)

find_package(Git REQUIRED)

ExternalProject_Add(
    doctest
    PREFIX ${CMAKE_BINARY_DIR}/doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    TIMEOUT 10
    UPDATE_COMMAND ${GIT_EXECUTABLE} pull
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
)

#-----------------------------------------------------------------------------
# add the subdirectories for the library, IDE and testing framework being used
#-----------------------------------------------------------------------------

add_subdirectory(NimbleLIB)
add_subdirectory(NimbleIDE)
add_subdirectory(TestNimbleIDE)
add_subdirectory(TestNimbleLIB)

# install the files needed for test
#file( COPY "Tools/UnitTests/Content" DESTINATION "Tools/UnitTests/Debug" )




