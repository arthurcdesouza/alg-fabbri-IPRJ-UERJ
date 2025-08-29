add_library(libmerge sorted_merge_3way.cpp)
# export public header path for other components
target_include_directories(libmerge PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(cmd)
add_subdirectory(tests)
add_subdirectory(benchmark)

# Custom target to run benchmarks
add_custom_target(eval
  COMMAND bm-sorted_merge_3way-cmd
  DEPENDS bm-sorted_merge_3way-cmd
  COMMENT "Running merge benchmark"
)
