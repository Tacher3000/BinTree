# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\binTree_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\binTree_autogen.dir\\ParseCache.txt"
  "binTree_autogen"
  )
endif()
