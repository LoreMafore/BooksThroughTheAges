# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "BooksThroughTheAges_autogen"
  "CMakeFiles\\BooksThroughTheAges_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\BooksThroughTheAges_autogen.dir\\ParseCache.txt"
  )
endif()
