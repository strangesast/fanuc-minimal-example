cmake_minimum_required(VERSION 3.13.4)

project(FanucExample LANGUAGES C VERSION 0.1)

find_library(FWLIB NAMES fwlib32 HINTS "/lib")
add_library(FWLIB SHARED IMPORTED external/fwlib/fwlib32.h)
#set_target_properties(fwlib32 PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/external/fwlib/libfwlib32-linux-x64.so.1.0.5 )

#add_library(fwlib32 SHARED IMPORTED external/fwlib/fwlib32.h)
#set_target_properties(fwlib32 PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/external/fwlib/libfwlib32-linux-x64.so.1.0.5 )

add_executable(fanuc_example main.c)
set_target_properties(fanuc_example PROPERTIES COMPILE_FLAGS "-pthread")
target_link_libraries(fanuc_example m fwlib32 pthread)

set(cmake_install_rpath "${CMAKE_INSTALL_PREFIX}/fwlib")
install (TARGETS fanuc_example DESTINATION /usr/local/bin)
