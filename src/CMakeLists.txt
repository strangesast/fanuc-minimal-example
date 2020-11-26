add_executable(fanuc_example main.c)

find_library(FWLIB NAMES fwlib32 HINTS "${CMAKE_SOURCE_DIR}/external/fwlib/" REQUIRED)
#add_library(FWLIB SHARED IMPORTED external/fwlib/fwlib32.h)
#include_directories("${CMAKE_SOURCE_DIR}/../")

if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
  set_target_properties(fanuc_example PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif()

target_link_libraries(fanuc_example m ${FWLIB} pthread)
