project(NimbleCalc VERSION 0.0.1)
# set C Make to use the C++20 Language version
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 20)

include(ExternalProject)
find_package(Git REQUIRED)

# Add the PDCurses include and library directories
include_directories("${CMAKE_SOURCE_DIR}/ExternalLibraries/PDcurses")
link_directories("${CMAKE_SOURCE_DIR}/ExternalLibraries/PDcurses")

# add the main executable folder
file(GLOB_RECURSE  SOURCE_FILES CONFIGURE_DEPENDS "src/*.c" "src/*.cpp" "inc/*.h" )

# tells cmake that it will be creating an executable
add_executable(NimbleCalc ${SOURCE_FILES})

# Add /NODEFAULTLIB:Library flag
if(MSVC)
    target_link_options(NimbleCalc PRIVATE "/NODEFAULTLIB:LIBCMT")
endif()

# link libraries
if (LINUX)
    target_link_libraries(NimbleCalc PRIVATE NimbleLIB ncurses)
else()
    target_link_libraries(NimbleCalc PRIVATE NimbleLIB pdcurses.dll)
endif()
# include path for libraries
target_include_directories(NimbleCalc PUBLIC NimbleLIB)


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
    add_custom_target( DocsNimbleCalc ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

if (MSVC)
    #    file( COPY "./Content/" DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )
else()
    #	file( COPY "./Content/" DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug )
endif()
