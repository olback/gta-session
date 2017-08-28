cmake_minimum_required(VERSION 3.7)
project(GTAToggle2)

set(CMAKE_C_STANDARD 11)

#
# Add 'gtatoggle2.rc' to the Source files!
#

set(SOURCE_FILES main.c gtatoggle2.rc)
add_executable(GTAToggle2 ${SOURCE_FILES})