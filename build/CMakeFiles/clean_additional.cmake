# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/shelf_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/shelf_autogen.dir/ParseCache.txt"
  "shelf_autogen"
  )
endif()
