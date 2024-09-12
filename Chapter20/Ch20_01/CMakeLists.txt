cmake_minimum_required(VERSION 3.27)

set(PROJNAME Ch20_01)
project(${PROJNAME} CXX)
include("../../CM/settings.cmake")

set(CPPFILES ${PROJNAME}.cpp ${PROJNAME}_ex.cpp)
set(CPPFILES_EXTRA)

add_executable(${PROJNAME} ${CPPFILES} ${CPPFILES_EXTRA})
target_include_directories(${PROJNAME} PRIVATE ${COMMON_DIR})

# Intel Threading Building Blocks required for execution policy support
if ((CMAKE_CXX_COMPILER_ID MATCHES "Clang") OR (CMAKE_CXX_COMPILER_ID STREQUAL "GNU"))
    find_library(TBB_LIB tbb)
    message(STATUS "TBB_LIB = ${TBB_LIB}")
    target_link_libraries(${PROJNAME} ${TBB_LIB})
endif()
