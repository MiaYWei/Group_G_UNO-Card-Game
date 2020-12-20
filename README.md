<div style="text-align: justify"> 

# Group G - UNO Express Card Game

* [Application Overview](#application-overview)
* [Group Information](#group-information)
* [File Structure](#file-structure)
* [How to Compile and Test](#how-to-compile-and-test)
* [Documentation](#documentation)

## Application Overview

UNO Express is a fun and interesting game, traditionally played by a group of 2 to 4 people with a deck of printed cards. We are proposing to develop this interactive game in C programming language which supports a single player competing against a computer opponent. Playing games online  with computers could speed up our responses and develop logic skills. 

And during the COVID-19  pandemic, we can use this game to keep ourselves entertained while maintaining our social circle. What’s more, this game will keep you engaged and help reduce stress. This time you neither need to  fret over saying UNO before you drop your penultimate card nor wait until the deck is shuffled.

By  this project, we intend to develop a UNO game engine that can make choices adhering to the rules of the game. 
This game is similar to the well known UNO game but following modifications are made to deliver this game efficiently as a single player game with a computer opponent.

* UNO Express card game has 56 cards, we removed the 'Reverse' action card as it doesn't make much sense in a two-player game.So,
  the total card count is 52.
* Human player always starts the game first.
* When the Wild Draw two action card is played, the next player automatically loses his turn, gets two cards added to his current set 
  set of cards and the current player can choose the color to continue the game (same as a normal UNO game).
* When the Draw one action card is played, the next player by default loses his turn and a card will be added to his set of cards.


## Group Information

**Organization:** Carleton Unviersity (SYSC 5709)

### Authors:

**1. Mia Wei**
 - GitHub: MiaYWei

**2. Krithiga Subramaniam Ravichandran**

 - GitHub: krithigasr

**3. Hongbo Pang**

 - GitHub: HongBo713

**4. Aditi Bhardwaj**

 - GitHub: aditibhardwaj98

## Brief Description
Following are the rules with which the game has been designed

1. There are 52 cards in total - 40 normal cards, 12 action cards.
2. These are 10 cards in each color - red,green,yellow and blue and action cards are - 4 Draw One cards, 4 Skip cards, 2 Wild cards,
   2 Wild Draw two cards.
3. To be declared as the winner of the game, you have to be the first player to exhaust all the cards assigned to you.
4. During the start of the game, 5 random cards are assigned to each player - human player and the computer, in this case.
5. One card is placed on the table with which you have to start matching your cards.
6. To keep things simple, the human player always starts the game first.
7. These are the keyboard inputs with which human can play the game
   * To request a card from the Draw pile, Press N or n.
   * To end turn, Press E or e.
   * To discard a normal card - Say you want to discard(RED,3), Press R3.
   * To discard action cards, 
     * Skip cards- Combine the first letter of the color with 'S', so if you want to discard(RED,SKIP), Press RS.
     * Draw one cards- Combine the first letter of the color with 'O', so if you want to discard(RED,DRAW-ONE), Press R0.
     * Wild card- Press AW.
     * Wild Draw two cards- Press AT.
     (A above stands for Action cards, W stands for Wild, T stands for draw Two)
   * To quit the game, Press Q or q. (This can happen at any point of time).


## File Structure

The following file structure is used to organize files in this repository:

* /bin - Contains the files created after executing the make file.
* /doc - Contains the designed flowchart for the application.  The main documentation can be found on the [UNO Express Card Game Documentation](https://github.com/MiaYWei/Group_G_UNO-Card-Game/wiki/User-Manual).
* /src - Contains the definition for all functions.
* /include -  All Header files are included here that are used throughout the application.
* /test
  * /data - Contains the log files generated during testing. 
  * /include - Contains the header files for the test files.       
  * /src - Contains the definitions for all unit tests.  
    * test.c - Main file that calls the test functions in other files.

## Installation

Complete instructions regarding installation of this project can be found here [UNO Express Card Game User Documentation](https://github.com/MiaYWei/Group_G_UNO-Card-Game/wiki/User-Manual).

### Compile and Build Instructions

The following make commands are available to help compile and build the application:

* `make all` (default) Will build the application and test application.

### Run Application

To run the application after installation, execute the application in the `bin` directory with  the command `UNO-Card-Game.exe`.


Additional details can be found in the [user and developer documentation](https://github.com/MiaYWei/Group_G_UNO-Card-Game/wiki).

### Test Application

To run the test files, execute the application in the `bin` directory with `UNO-Card-Game_Test`. All test results are logged to the file 'test_log' in the same directory.


## Documentation

User documentation can be found in the Github repository at [UNO Express Card Game User Documentation](https://github.com/MiaYWei/Group_G_UNO-Card-Game/wiki/User-Manual).

Additional developer documentation is found in the [UNO Express Card Game Developer Documentation](https://github.com/MiaYWei/Group_G_UNO-Card-Game/wiki/Developer-Manual).

# License 
This project is licensed under the GPL 2.0 License. 

</div>
