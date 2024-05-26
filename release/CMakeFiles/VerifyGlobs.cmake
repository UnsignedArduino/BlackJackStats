# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.29
cmake_policy(SET CMP0009 NEW)

# sources at CMakeLists.txt:9 (FILE)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "D:/Programming Projects/Number Crunching/BlackJackEvolution/BlackJackStats/src/*.cpp")
set(OLD_GLOB
  "D:/Programming Projects/Number Crunching/BlackJackEvolution/BlackJackStats/src/Blackjack/Game/BlackjackGame.cpp"
  "D:/Programming Projects/Number Crunching/BlackJackEvolution/BlackJackStats/src/Blackjack/Hand/BlackjackHand.cpp"
  "D:/Programming Projects/Number Crunching/BlackJackEvolution/BlackJackStats/src/Blackjack/Player/BlackjackPlayer.cpp"
  "D:/Programming Projects/Number Crunching/BlackJackEvolution/BlackJackStats/src/Cards/Cards.cpp"
  "D:/Programming Projects/Number Crunching/BlackJackEvolution/BlackJackStats/src/Cards/Hand/CardHand.cpp"
  "D:/Programming Projects/Number Crunching/BlackJackEvolution/BlackJackStats/src/Cards/Hand/CardHandHelpers.cpp"
  "D:/Programming Projects/Number Crunching/BlackJackEvolution/BlackJackStats/src/Cards/Hand/CardHandShuffler.cpp"
  "D:/Programming Projects/Number Crunching/BlackJackEvolution/BlackJackStats/src/algorithm.cpp"
  "D:/Programming Projects/Number Crunching/BlackJackEvolution/BlackJackStats/src/main.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "D:/Programming Projects/Number Crunching/BlackJackEvolution/BlackJackStats/release/CMakeFiles/cmake.verify_globs")
endif()

# tests at CMakeLists.txt:28 (FILE)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "D:/Programming Projects/Number Crunching/BlackJackEvolution/BlackJackStats/tests/*.cpp")
set(OLD_GLOB
  "D:/Programming Projects/Number Crunching/BlackJackEvolution/BlackJackStats/tests/test_algorithm_fitness_eval.cpp"
  "D:/Programming Projects/Number Crunching/BlackJackEvolution/BlackJackStats/tests/test_algorithm_fitness_eval_speed.cpp"
  "D:/Programming Projects/Number Crunching/BlackJackEvolution/BlackJackStats/tests/test_blackjack_game.cpp"
  "D:/Programming Projects/Number Crunching/BlackJackEvolution/BlackJackStats/tests/test_cardhand_shuffling.cpp"
  "D:/Programming Projects/Number Crunching/BlackJackEvolution/BlackJackStats/tests/test_cardhand_shuffling_speed.cpp"
  "D:/Programming Projects/Number Crunching/BlackJackEvolution/BlackJackStats/tests/test_cardhands.cpp"
  "D:/Programming Projects/Number Crunching/BlackJackEvolution/BlackJackStats/tests/test_helpers.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "D:/Programming Projects/Number Crunching/BlackJackEvolution/BlackJackStats/release/CMakeFiles/cmake.verify_globs")
endif()
