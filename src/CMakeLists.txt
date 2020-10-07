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
