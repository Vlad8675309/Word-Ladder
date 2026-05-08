# Word Ladder
This C++ application implements the word ladder game invented by Lewis Carroll in the 19th century. A word ladder puzzle begins with two words, and to solve the puzzle one must find a chain of other words to link the two, in which two adjacent words differ by exactly one letter.

## Description

The application provides 3 main game modes: automatic mode, playing mode and analytics mode.

### Automatic Mode

The user provides a starting word and a target word. The program finds the shortest sequence of words that links the starting word and target word according to the rules of the word ladder puzzle.

### Playing Mode

The user enters a username, a word length and starts the game. Upon starting the game, the user is given a starting word and a target word and must provide a sequence of words that links the starting word and the target word according to the rules of the word ladder puzzle.

### Analytics Mode

The user specifies a username. The program prints relevant information about the games played by the user with the specified username.

### Logic

The program works by reading words from a dictionary and creating a pattern map. A pattern map is map that consists of *pattern-words* pairs, where *pattern* is a word obtained by replacing any one letter from a word from the dictionary with the wildcard character *, and *words* is an array of words that differ by the wildcard character to the pattern (e.g. the words fall, hall, call correspond to the *all pattern). The program then builds a graph with edges between words that correspond to the same pattern and utilizes breadth-first search to find the shortest path between any two words. 

### Tools

The program is written in C++14 and uses Qt 6.9.0 for the user interface.


