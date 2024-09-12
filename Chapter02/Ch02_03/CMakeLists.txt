cmake_minimum_required(VERSION 3.27)

set(PROJNAME Ch02_03)
project(${PROJNAME} CXX)
include("../../CM/settings.cmake")

set(CPPFILES ${PROJNAME}.cpp ${PROJNAME}_ex.cpp ${PROJNAME}_misc.cpp)
set(CPPFILES_EXTRA ${COMMON_DIR}/MF.cpp)

add_executable(${PROJNAME} ${CPPFILES} ${CPPFILES_EXTRA})
target_include_directories(${PROJNAME} PRIVATE ${COMMON_DIR})
