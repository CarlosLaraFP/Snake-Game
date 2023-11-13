# Capstone Snake Game

The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The objective of the game is to capture as many points as possible while moving a snake using up, down, left, and right keys. 

Every time you capture a yellow item:

* Score increases by 1
* Snake length increases by 1
* Snake speed increases
* Ammunition increases by 2 (limit: 10)

Green items can only be captured by firing projectiles by pressing the space bar. Every time you capture a green item:

* Score increases by 2
* Snake speed decreases

## New Features Added to the Game

* Writing highest score to local file and always displaying it on a new game.
* Random spawning of boosts, which grant double points and reduce snake speed.
* Snake can fire projectiles to capture a boost by pressing the space bar.
* Projectiles that go off screen are destroyed.
* Game loop updates happen concurrently, where thread safety has been implemented using scoped mutexes and locks.

# Rubric

## Loops, Functions, I/O

* The project reads data from a file and processes the data, and the program writes data to a file (game.h, lines 67-68).
* The project accepts user input and processes the input (controller.cpp, lines 35-44).
* The project uses data structures and immutable variables (game.h, lines 41-43 and 54).

## Object Oriented Programming

* Classes are added to the project with appropriate access specifiers for class members (consumable.hpp, food.hpp, boost.hpp, projectile.hpp).
* Classes abstract implementation details from their interfaces (food.cpp, boost.cpp, projectile.cpp).
* Classes follow an appropriate inheritance hierarchy with virtual and override functions (food.hpp and boost.hpp inherit from abstract class consumable.hpp, where its virtual method on line 15 is overriden by each class).

## Memory Management

* The project makes use of references in function declarations (consumable.hpp, lines 15-22 and projectile.hpp, lines 15-18).
* The project uses destructors appropriately (consumable.hpp, line 14, in conjunction with game.h, line 41, as well as renderer.cpp, lines 39-45).
* The project uses scope / RAII where appropriate (all locks in snake.cpp, among other places).
* The project uses move semantics to move data instead of copying it, where possible (game.cpp, lines 22, 26, and controller.cpp, line 41).
* The project uses smart pointers instead of raw pointers (game.h, line 41, and game.cpp, lines 20 and 24).

## Concurrency

* The project uses multithreading (game.cpp, lines 42 and 71-86).
* A mutex and lock is used in the project (boost.cpp, line 18, snake.cpp lines 27, 48, 68, 84, 98, 105, 112, and game.cpp line 90).

## Dependencies for Running Locally

* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * On Windows, once you download SDL2, add its path to the CMAKE_PREFIX_PATH environment variable.
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
 
For Windows, if not using vcpkg, follow these steps:

1. Once you download SDL2, add its path to the CMAKE_PREFIX_PATH environment variable. This allows find_package(SDL2 REQUIRED) in CMakeLists.txt to find SDL2.
2. Add the location of the SDL2.dll to your system PATH environment variable (i.e. ...\lib\x64).

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

* On Windows Visual Studio Developer PowerShell, instead of "make", run "MSBuild SDL2Test.sln" followed by ".\Debug\SnakeGame.exe"

## CC Attribution-ShareAlike 4.0 International

Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
