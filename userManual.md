<div style="text-align: justify">  

## Contents
* Introduction
* Installation 
* Compiling the project
* Testing
* Welcome Screen
* Rules 
* Feature Descriptions
* Things to Note

## Introduction

UNO Express Card Game is a fun and interesting game which is developed in  C programming  language which supports a single player competing against a computer opponent. The game has been slightly modified to suit development of a single player game and make it simple and interesting at the same time.

## Installation 

UNO Card Game can be run on Cygwin compiler or any other IDE with GNU GCC compiler. 

Cygwin : [Download Link](https://sourceforge.net/projects/mingw-w64/)

To download the project, follow the steps below,

* Install Git (The 'User' can use Git bash or any other software of choice to clone the project).

* Create a new folder for the project. Right-click inside the folder and open gitbash.

* Type the following command in the git terminal: 

git clone https://github.com/MiaYWei/Group_G_UNO-Card-Game 

OR 

Go to https://github.com/MiaYWei/Group_G_UNO-Card-Game and click on "Download" option to download the
zip folder of the project.

## Compiling the project 

* Open the folder containing the project downloaded in the previous step and copy its path.
* Open Cygwin64 Terminal, type cd (path), and enter.
* Ensure to initialize the project using `make clean` to remove all build artifacts.
* Type the command `make all` and click on enter. Screenshot below shows the expected output after executing this command.

![image](https://user-images.githubusercontent.com/42897174/102678709-26564100-4178-11eb-925d-592a30cee251.png)

* After the execution of the previous command, we see that the executable files will be created in the bin folder.
* The user can run the application by using the command `./bin/UNO-Card-Game.exe`.

## Testing

* After executing the 'make all' command, we will see a 'UNO-Card-Game_Test.exe' file created in the bin folder. To run the test files
  please use the command `./bin/UNO-Card-Game_Test.exe`.
* The output of the test file is logged to 'test_log.txt' in the same folder. This file gives the summary of the outputs
  (success/failure) for all the test cases in the test files. 
  
  
## Welcome Screen
After executing the program, the following Welcome screen is displayed with the Main menu.

![image](https://user-images.githubusercontent.com/42897174/102591053-6c12fb00-40df-11eb-97d0-2e0f627bd252.png)


## Rules 
 The rules of the game are available to the user by choosing option '1' in the Main menu. We can also take a look at the keyboard inputs required for the human player to play the game here. They are also available in depth in the readme file linked below.
 
 [UNO Express Readme file](https://github.com/MiaYWei/Group_G_UNO-Card-Game/blob/master/README.md)

## Game Initialization

![image](https://user-images.githubusercontent.com/42897174/102587463-dde84600-40d9-11eb-8086-c2406789ef05.png)

* In the image above, we see that during the start of the game each player is assigned 5 cards. The deck assigned to the human player seen on the screen( highlighted in yellow).

* Also, for the game to begin, one card is placed on the table which is displayed on the screen( highlighted in yellow).

* The player to take turn next is also displayed on the screen.

## Project Modules
The project is split into 5 modules as follows,

* Menu Display-  Displays the Welcome screen along with the Main menu during the start of the game.

* Game - This module handles the initialization of the game, assigning each player with 5 cards during the start of the game and setting up the discard and draw piles. This also has the functionality to end each player's turn as well as quit game.

* Cards Management - All card related functionalities like the declaration of cards structures, global variables, add/remove card, display card are all taken care of here.

* Computer Player - Computer player related functions is implemented here.

* Human Player- Human player functionality is supported here.


## Things to Note

This game is designed with a predefined set of rules for the human player to follow so that the computer understands the user input and carries the game forward. If the human player does not make a valid choice during his turn we display a warning message (with the error) as shown in the image below.

![image](https://user-images.githubusercontent.com/42897174/102587250-8649da80-40d9-11eb-9064-5a4de171b2ee.png)

Scenarios where the Human player will be faced with warning:

* When a invalid card is chosen. Say, for example, when the card discarded does not match   the card on table with either color/number.
* When you discard a card that doesn't belong to your deck of cards.
* When you try to draw card twice from the draw pile. Just one draw card per turn is allowed.
* When you try to end you turn before you draw card/discard card. If you don't have any   cards to match the card on the table, you are expected to draw card first and then end your turn.


</div>