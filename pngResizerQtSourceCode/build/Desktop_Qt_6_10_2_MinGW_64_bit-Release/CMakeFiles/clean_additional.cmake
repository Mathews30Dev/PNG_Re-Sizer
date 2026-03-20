# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\pngResizer_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\pngResizer_autogen.dir\\ParseCache.txt"
  "pngResizer_autogen"
  )
endif()
