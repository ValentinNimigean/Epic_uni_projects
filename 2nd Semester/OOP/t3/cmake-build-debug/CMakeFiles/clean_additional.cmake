# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\oop_t3_915_Nimigean_Valentin_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\oop_t3_915_Nimigean_Valentin_autogen.dir\\ParseCache.txt"
  "oop_t3_915_Nimigean_Valentin_autogen"
  )
endif()
