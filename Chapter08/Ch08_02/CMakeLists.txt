cmake_minimum_required(VERSION 3.27)

set(PROJNAME Ch08_02)
project(${PROJNAME} CXX)
include("../../CM/settings.cmake")

set(CPPFILES ${PROJNAME}.cpp ${PROJNAME}_ex.cpp ${PROJNAME}_misc.cpp)
set(CPPFILES_EXTRA ${COMMON_DIR}/HtmlColor.cpp)

add_executable(${PROJNAME} ${CPPFILES} ${CPPFILES_EXTRA})
target_include_directories(${PROJNAME} PRIVATE ${COMMON_DIR})
