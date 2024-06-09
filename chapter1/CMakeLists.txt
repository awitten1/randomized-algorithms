add_library(chapter1 INTERFACE)
target_link_libraries(chapter1 INTERFACE utils)
target_include_directories(chapter1 INTERFACE ${CMAKE_CURRENT_LIST_DIR})

add_executable(quicksort_bench quicksort_main.cpp)

target_link_libraries(quicksort_bench PRIVATE benchmark::benchmark)
target_link_libraries(quicksort_bench PRIVATE chapter1)

if (LINUX)
  target_link_libraries(quicksort_bench PRIVATE perf)
endif()
