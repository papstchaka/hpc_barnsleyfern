# Always specify which version you need:
# - at least VERSION 3
cmake_minimum_required (VERSION 3.10)

# This defines ${PROJECT_NAME}, use it to change the name of your executable easily
project(barnsley_fern)

# Prevent compilation in-source directory
if( ${CMAKE_BINARY_DIR} STREQUAL ${PROJECT_SOURCE_DIR} )
    Message( FATAL_ERROR "Source and build directories are the same!")
endif()

# Good practice, collect all *.cpp files into a variable
set(SRC_FILES Worker.cpp Point.cpp main.cpp RealConsumer.cpp)
# linker to pthread
set(CMAKE_CXX_FLAGS -pthread)

# This creates a Makefile to produce the executables
add_executable(${PROJECT_NAME} ${SRC_FILES})

#Path of CImg.h file relative to the CMakeLists.txt
set(CIMG_H_PATH ${PROJECT_SOURCE_DIR})
# CImg uses threads -> pthread as in today's lecture
target_link_libraries(${PROJECT_NAME} pthread)

# If CImg shall use built in png (for some reason ImageMagick does not work right now)
set(YOU_NEED_PNG 1)

if(${YOU_NEED_PNG} EQUAL 1)
    message(STATUS "Looking for libpng...")

    # Flags to enable native support for PNG image files, using the PNG library.
    # ( http://www.libpng.org/ )
    set(CIMG_PNG_CCFLAGS -Dcimg_use_png)

    find_package(PNG REQUIRED)
    include_directories(${PNG_INCLUDE_DIR})
    target_link_libraries (${PROJECT_NAME} ${PNG_LIBRARY})
    target_compile_definitions(${PROJECT_NAME} PRIVATE cimg_use_png=1)
endif()
