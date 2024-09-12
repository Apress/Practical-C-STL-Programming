cmake_minimum_required(VERSION 3.27)

set(PROJNAME Ch20_04)
project(${PROJNAME} CXX)
include("../../CM/settings.cmake")

set(CPPFILES ${PROJNAME}.cpp ${PROJNAME}_ex.cpp)
set(CPPFILES_EXTRA)

add_executable(${PROJNAME} ${CPPFILES} ${CPPFILES_EXTRA})
target_include_directories(${PROJNAME} PRIVATE ${COMMON_DIR})

# Intel Threading Building Blocks required for execution policy support
if ((CMAKE_CXX_COMPILER_ID MATCHES "Clang") OR (CMAKE_CXX_COMPILER_ID STREQUAL "GNU"))
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-command-line-argument")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,-latomic")
endif()

