# Minimum version
cmake_minimum_required(VERSION 3.3.0)

# Project name
project(ppm-c C CXX)

# Configuration types
if(CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Multi configuration types" FORCE)
endif()

# Compile options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Wextra -Winline -Weffc++")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++11 -g -Wall -Wextra -Winline -Weffc++")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++11 -O3")

# Sources
set(SOURCES
	main.cpp)
	
# Executable
add_executable(ppm-c ${SOURCES})

# Additional clean files
set(CLEAN_FILES
	CMakeFiles
	cmake_install.cmake
	CMakeCache.txt
	Makefile)
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${CLEAN_FILES}")
