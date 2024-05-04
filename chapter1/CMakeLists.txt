
add_executable(quicksort_bench quicksort_main.cpp)

target_link_libraries(quicksort_bench PRIVATE benchmark::benchmark)
target_link_libraries(quicksort_bench PRIVATE rand)
