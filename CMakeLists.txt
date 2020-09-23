cmake_minimum_required(VERSION 3.13.4)

project(FanucExample LANGUAGES C VERSION 0.1)

find_library(FWLIB NAMES fwlib32 HINTS "/lib")
add_library(FWLIB SHARED IMPORTED external/fwlib/fwlib32.h)

add_executable(fanuc_example main.c)
target_link_libraries(fanuc_example m fwlib32 pthread)

if( "$ENV{ARCH}" STREQUAL "x64" )
  target_compile_options(fanuc_example PRIVATE -pthread -m32)
  set_target_properties(fanuc_example PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
else()
  target_compile_options(fanuc_example PRIVATE -pthread)
  set_target_properties(fanuc_example PROPERTIES COMPILE_FLAGS "-pthread")
endif()

set(cmake_install_rpath "${CMAKE_INSTALL_PREFIX}/fwlib")
install (TARGETS fanuc_example DESTINATION /usr/local/bin)
