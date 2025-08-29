include(GoogleTest)

add_executable(run-tests test-sorted_merge_3way.cpp)
target_link_libraries(run-tests libmerge gtest_main)

# The gtest_discover_tests() function automatically finds and registers tests
# with CTest. It should be called after all test executables have been defined.
gtest_discover_tests(run-tests)
