## Contents
* Introduction
* Installation and Usage
* Testing
* Feature Description

## Introduction

UNO Card Game is a fun and interesting game, traditionally played by a group of 2 to 4 people with a deck of printed cards. And during the COVID-19 pandemic, we can use this game to keep ourselves entertained while maintaining our social circle. What’s more, this game will keep you engaged and help reduce stress. This time you neither need to fret over saying UNO before you drop your penultimate card nor wait until the deck is shuffled.

## Installation and Usage

Our project 'UNO Card Game' can be run on Cygwin compiler or any other IDE with GNU GCC compiler. 

Cygwin : [Download Link](https://sourceforge.net/projects/mingw-w64/)

To download the project game, the following are the steps:

1. Install Git (The 'User' can use Git bash or any other software of choice to clone the project).

2. Create a new folder for the project. Right-click inside the folder and open a gitbash here. Right-Click +” Git Bashhere”.

3. Type the following command in the git terminal: 

Git clone https://github.com/MiaYWei/Group_G_UNO-Card-Game 

OR 

Go to the link https://github.com/MiaYWei/Group_G_UNO-Card-Game and click on "Clone" or "Download" and download the zip folder of the software.

To Ensure that project(program) is compiled and running:

1. Compiling the project.

     a) Open the downloaded folder, open  ..\.

     b) Copy path.

     c) Open Cygwin64 Terminal, type cd (path), and enter.

     d) Type `make` and enter. (After this command is entered, object files and executable files will be created. The user can run the project from the bin folder.)

2. Ensure to initialize the project using `make clean` to remove all build artifacts

4. Compile by using `make` to build the application

5. Type `bin/./Group_G_UNO-Card-Game.exe` to run the project(or game). //Krithiga if this is needed, edit it and check the name of the executable file.
Note: DEBUG can be enabled by appending DEBUG=1 to the make command (i.e. make DEBUG=1) //Krithiga, if this is needed keep it or else delete this.

## Testing

1. Replace the makefile with the file present at path test../makefile and run the command again. 

2. Test the project using `make` to build a test application.

Note: We are using `make all` to create ... //Krithiga, if this is needed edit it or else delete this.

## Feature Description

After running the program, the following screen is displayed with the following options,

////Krithiga, screenshot.

This module handles the display functionalities on the console. 

* display_main_menu() - Displays main menu of the opening screen of the game, 4 selectable options to operate the game. 

* start_new_game()- Executes and start the main program 

* display_game_rules () - Displays the rules of UNO express 

* exit_game () - Exit the program and return to main menu 

If user choose the option of displaying game rules, the following screen is displayed,

////Krithiga, screenshot.

If user choose the option of starting the game, the following screen is displayed with human player's deck with 5 cards,

////Krithiga, screenshot.


If user wishes to quit the game, human player can enter “q” or “Q” using the keyboard.

Note: PLayer **MUST** follow the rules displayed in the game. If not followed, a warning message is displayed as shown below for one of the input cases,

////Krithiga, screenshot.














