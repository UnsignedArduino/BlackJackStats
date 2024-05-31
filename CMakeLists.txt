CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
PROJECT("BlackJackStats")

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED True)
# SET(CMAKE_CXX_FLAGS "-static -static-libgcc -static-libstdc++")

# Main executable
FILE(GLOB_RECURSE sources CONFIGURE_DEPENDS "src/*.cpp")
ADD_EXECUTABLE(main ${sources})

LIST(LENGTH sources sources_length)
MESSAGE(STATUS "${sources_length} files in main executible")

# Tests

# Gather sources without main.cpp for testing
SET(sources_without_main "")
FOREACH (source ${sources})
  GET_FILENAME_COMPONENT(source_name ${source} NAME)
  IF (NOT ${source_name} MATCHES "main.cpp")
    LIST(APPEND sources_without_main ${source})
  ENDIF ()
ENDFOREACH (source)

# Actual tests
ENABLE_TESTING()
FILE(GLOB_RECURSE tests CONFIGURE_DEPENDS "tests/*.cpp")
FOREACH (test ${tests})
  GET_FILENAME_COMPONENT(test_name ${test} NAME_WE)
  IF (${test_name} MATCHES "test_helpers")
    CONTINUE()
  ENDIF ()
  ADD_EXECUTABLE(${test_name} ${test} ${sources_without_main} "tests/test_helpers.h" "tests/test_helpers.cpp")
  ADD_TEST(NAME ${test_name} COMMAND ${test_name})
ENDFOREACH (test)

LIST(LENGTH tests tests_length)
MESSAGE(STATUS "${tests_length} tests found")
