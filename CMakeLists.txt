cmake_minimum_required(VERSION 3.13.4)

project(FanucExample LANGUAGES C VERSION 0.1)

# for IDE
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)

set_target_properties(fanuc_example
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

install (TARGETS fanuc_example
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION bin
  ARCHIVE DESTINATION lib
  INCLUDES DESTINATION include
  DESTINATION /usr/local/bin)
