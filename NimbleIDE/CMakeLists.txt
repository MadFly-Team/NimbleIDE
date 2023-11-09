# make sure the minimum cmake version is compatible with your compiler
cmake_minimum_required(VERSION 3.9.1)

# set a project name and version number
project(NimbleIDE VERSION 0.0.1)

# set C Make to use the C++20 Language version
set(CMAKE_CXX_STANDARD 20)

include(ExternalProject)
find_package(Git REQUIRED)

# add the main executable folder
file(GLOB_RECURSE  SOURCE_FILES CONFIGURE_DEPENDS "src/*.c" "src/*.cpp" "inc/*.h" )

# tells cmake that it will be creating an executable 
add_executable(NimbleIDE ${SOURCE_FILES})

# link libraries
target_link_libraries(NimbleIDE PRIVATE NimbleLIB)

# include path for libraries
target_include_directories(NimbleIDE PUBLIC NimbleLIB)


# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( DocsNimbleIDE ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)


