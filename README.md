# BlackJackStats

[![CMake on multiple platforms](https://github.com/UnsignedArduino/BlackJackStats/actions/workflows/cmake-multi-platform.yml/badge.svg)](https://github.com/UnsignedArduino/BlackJackStats/actions/workflows/cmake-multi-platform.yml)

Simulations for the gambling card game Blackjack.

## Install

The steps below assume Windows. You can also use the CMake GUI.

1. Install MinGW and Make or Ninja.*
2. Install CMake.
3. Clone this repo.
4. `mkdir build && cd build` in project root.
5. `cmake .. -G "MinGW Makefiles"` or `cmake .. -G "Ninja"`.* For Linux, use the `Unix Makefiles` generator.
6. `cmake --build .`

\* You could probably use other generators that end up using `gcc`/`g++` or `clang`, but that is untested.

[//]: # (`g++ src/*.cpp -o main.exe` seems to work without issues on Windows)

## Usage

Run `main.exe` in the `build` directory.

## Testing

Run a `test_*.exe` or `ctest` in the `build` directory.

### Writing tests

Check out [`/tests/test_cardhands.cpp`](tests/test_cardhands.cpp) for an example on how to use the horrible testing
macros I've created. Look in [`/tests/test_helpers.h`](tests/test_helpers.h) to see all the available macros.
