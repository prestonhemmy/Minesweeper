# Minesweeper

## Description

Minesweeper is a classic computer game that originated in the 1960s with the objective of clearing a rectangular grid of hidden "mines" without detonating any of them, with the assistance of clues about the number of neighboring mines in each field. The player uses a mouse to click on squares, revealing either a number indicating the count of adjacent mines or an empty space, which automatically expands to adjacent squares until reaching squares containing numbers. If the player clicks on a mine, the game is lost, but if all non-mine squares are revealed, the game is won.

### Instructions

This game was implemented using Simple and Fast Multimedia Library (SFML). Hence, SFML must be installed on any device which the user wishes to run the game on.

#### SFML Installation

Use the following link for a guided set up of the latest version of SFML:

https://www.sfml-dev.org/tutorials/2.6/start-vc.php

#### How to Play?

Minesweeper is a classic puzzle game where the objective is to clear a rectangular board containing hidden mines without detonating any of them.

To start a new game, run the program. You will first see a welcome screen prompting you to enter your name using the keyboard. Your name can be up to 10 characters long and should only contain letters (no numbers or special characters). As you type, you will see the characters appear, and you can use backspace to remove the last character. Once you've entered at least one character, press 'Enter' to start the game. If you close this welcome window, the program will exit.

The game window contains a grid of tiles, each of which may or may not contain a hidden mine. For this version, the board is 16 tiles high by 25 tiles wide, and there are 50 mines randomly placed at the start of each new game.

Left-click on a tile to reveal it. If the tile contains a mine, the game ends and you lose. If it does not contain a mine, one of two things happens:

* If the revealed tile has adjacent mines, it will display the number of mines touching it (this number ranging from 1 to 8).
* If the revealed tile has no adjacent mines, it will be blank and will automatically reveal all adjacent non-mine tiles. This process repeats recursively.

The goal is to reveal all non-mine tiles without hitting a mine. Right-click on a tile to place a flag marker, indicating you believe there is a mine there. A counter displays the number of remaining mines, updating as you place and remove flags. Right-click again to remove a flag. You cannot reveal a tile that has been flagged.
A timer will track how long you take to complete the game. You can press the pause button to pause the timer and game. In paused mode, all tiles will display as unrevealed until you press the play button to resume.
There are a few other buttons on the interface:

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The smiley face will reset the game board at any time. Mines will be randomly redistributed.\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The debug button is a developer feature that will reveal the locations of all mines when toggled on. It's useful for testing but not intended for normal play.\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The leaderboard button pauses the game and displays the fastest times and names from previous games in a pop-up leaderboard window. The game will resume when this window is closed.

To win the game, reveal all non-mine tiles. The remaining mine tiles will automatically be flagged. Your winning time will be compared to the leaderboard records. If you place in the top 5, your name and time will be recorded and marked with a '*' on the leaderboard.
You lose if you reveal a mine tile. All mine locations will then be shown. No further moves can be made after winning or losing a game, but you can start a new game with the smiley face button.

Happy Minesweeping!

### References

The course COP3503C - Programming Fundamentals 2 offered at the University of Florida was responsible for the design concept and certain developmental guidelines including reccomended.

SFML tutorial webpages for *sf::Event*, *sf::RenderWindow*, *sf::Sprite*, *sf::Texture*, *sf::Text*, *sf::Font*, *sf::Color*, etc. were refered to during the development of this project:\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1Event.php\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1RenderWindow.php\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1Sprite.php\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1Texture.php\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1Text.php\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1Font.php\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Color.php

Additionally, various other research was performed to fully implement components as specified by the course. In particular, the following sources from *Cppreference*, *GeeksforGeeks*, *Stack Overflow* and others like them were instrumental in the integration and use of random mine placement on the board:\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;https://stackoverflow.com/questions/39288595/why-not-just-use-stdrandom-device\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;https://en.cppreference.com/w/cpp/algorithm/random_shuffle\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;https://www.geeksforgeeks.org/stdmt19937-class-in-cpp/\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine