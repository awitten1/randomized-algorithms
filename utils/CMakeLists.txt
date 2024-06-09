add_library(utils STATIC perf.cpp)
target_include_directories(utils INTERFACE ${CMAKE_CURRENT_LIST_DIR})