add_executable(bm-sorted_merge_3way-cmd bm_sorted_merge_3way.cpp)
target_link_libraries(bm-sorted_merge_3way-cmd libmerge benchmark::benchmark)
