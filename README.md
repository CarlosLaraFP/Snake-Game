# Capstone Snake Game

The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

In this project, we build our own C++ application or extend this Snake game, following the principles we have learned throughout the C++ Nanodegree Program. This project demonstrates my ability to independently create applications using a wide range of C++ features.

## New Features Added to the Game

* Writing highest score to local file and always displaying it on a new game (done).
* Random spawning of boosts, which grant double points and reduce snake speed (done).
* Snake can fire projectiles to capture a boost by pressing the space bar (done).
* Snake can capture short-lived items to reduce its length.
* Random spawning of short-lived poisons that remove projectiles, add length, and/or remove points.
* Algorithm-driven slow moving NPC snake that fires at us (destroyable with projectiles).
* Bonus: Add HP/FP bars with random spawning of replenishing items.
* Bonus: Random initialization of static/moving obstacles (destroyable with projectiles).
* Bonus: Special phasing item that provides timed invulnerability to self-contact.

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
