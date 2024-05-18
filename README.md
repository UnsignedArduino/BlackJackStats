# BlackJackStats

Simulations for the gambling card game Blackjack. 

## Install

These steps assume Windows. You can also use the CMake GUI. 

1. Install MinGW and Make or Ninja.*
2. Install CMake.
3. Clone this repo.
4. `mkdir build && cd build` in project root.
5. `cmake .. -G "MinGW Makefiles"` or `cmake .. -G "Ninja"`.*
6. `cmake --build .`

\* You could probably use other generators that end up using `gcc`/`g++` or `clang`, but that is untested. 

`g++ src/*.cpp -o main.exe` seems to work without issues on Windows

## Usage

Run `main.exe`.