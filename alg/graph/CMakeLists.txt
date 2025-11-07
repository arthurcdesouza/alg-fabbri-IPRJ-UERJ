add_executable(dynagraph dynagraph.c)

if (alg_BUILD_TESTS)
  add_subdirectory(tests)
endif()

