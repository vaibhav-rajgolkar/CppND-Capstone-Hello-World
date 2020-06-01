# CPPND: Capstone Space War Game

<img src="Space_War.gif"/>

This project is developed from scrach as part of [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213) assesment.

This Capstone Project is the game development proejct implemented using SDL2 library features with C++. This is Space War game where player fights with space enimies. The enimies are generated randomly and have ability to fight back by firing bullet. Player can destroy enimies by firing back bullets at them. The Player has ability to move up, down, left, right to save himself from enemy bullets. Game resets when enemy bullet hits player or any of the enemy is successful to reach player base. It is responsibility of player to protect himself and base from space enimies. Bonus point : Player has unlimited storage of bullets :-). Please see section `Controls for Game Play` for information regarding controls to operate player. The score is calculated based of number of enimies destroyed. If the current game score surpasses high score then the high score is updated and stored in score card as new high score. 

Game has background animation and sound effects. Different sounds are generated when player or enemy is destroyed. There is sound effect for player bullet fire as well. Background animation and sound effect brings pleasant experience in game playing.

## Controls for Game Play
* Move player in UP direction using `UP Arrow Key`
* Move player in DOWN direction using `UP Arrow Key`
* Move player in LEFT direction using `UP Arrow Key`
* Move player in RIGHT direction using `UP Arrow Key`
* Fire bullets using `LEFT CTRL Key`

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* SDL2_image
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. command `sudo apt-get install libsdl2-image-dev` can be used for ubuntu os.
* SDL2_mixer
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. command `sudo apt-get install libsdl2-mixer-dev` can be used for ubuntu os.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SpaceWar`.

## Future Development Scope
Currently game only supports one level where player can play as long as player is alive. The High score is updated with new record score. Also player has ability fire only single strenght bullets with same speed. Below are some future developement points to further develop game
1. Update game with level based game play.
2. Update player speed, fire speed and bullet strenth based on levels.
3. Add life chances to player to survive in level.
4. Add more sound effects and background animation for more realistic view.
5. Changes game structure to support grid like movement for player and enemies.
