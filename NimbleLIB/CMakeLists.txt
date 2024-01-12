project(NimbleLIB)
# set C Make to use the C++20 Language version
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 20)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "inc/*.h" "src/*.c" "src/*.cpp" )

# first we can indicate the documentation build as an option and set it to ON by default
option(BUILD_DOC "Build documentation" ON)

# tells cmake that it will be creating a library 
add_library(NimbleLIB ${SOURCE_FILES})

add_compile_definitions(NIMBLELIBRARY _CRT_SECURE_NO_WARNINGS)

# Add /NODEFAULTLIB:Library flag
if(MSVC)
    target_link_options(NimbleLIB PRIVATE "/NODEFAULTLIB:LIBCMT")
endif()

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
    add_custom_target( DocsNimbleLIB ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
