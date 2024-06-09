add_library(utils INTERFACE)

if (LINUX)
  add_library(perf STATIC perf.cpp)
  target_include_directories(perf INTERFACE ${CMAKE_CURRENT_LIST_DIR})
endif()

target_include_directories(utils INTERFACE ${CMAKE_CURRENT_LIST_DIR})