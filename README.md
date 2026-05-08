# Word Ladder
This C++ application solves and implements the word ladder game invented by Lewis Carroll in the 19th century. A word ladder puzzle begins with two words, and to solve the puzzle one must find a chain of other words to link the two, in which two adjacent words differ by exactly one letter.

<img width="150" height="345" alt="wordladder" src="https://github.com/user-attachments/assets/626299b6-46c9-4a92-a167-e2d6f15d0cb2" />

## Description

The program provides 3 main game modes: automatic mode, playing mode and analytics mode.

### Automatic Mode

The user provides a starting word and a target word. The program finds the shortest sequence of words that links the starting word and target word according to the rules of the word ladder puzzle.

<img width="859" height="446" alt="automaticmode" src="https://github.com/user-attachments/assets/5b2912c9-40a4-44a7-97f2-34dd0d1d1e99" />

### Playing Mode

The user enters a username, a word length and starts the game. Upon starting the game, the user is given a starting word and a target word and must provide a sequence of words that links the starting word and the target word according to the rules of the word ladder puzzle. If stuck, the user may ask for a hint, in which case a letter of the current word is marked red to indicate to the user that the optimal path in that current moment requires changing the marked letter for the next word. In the end, the optimal sequence is also shown.   

<img width="859" height="769" alt="playingmode" src="https://github.com/user-attachments/assets/a9c73a27-955f-4d13-9afe-5dc7c583479c" />

### Analytics Mode

The user specifies a username. The program prints relevant information about the games played by the user with the specified username.

### Logic

The main work is done by reading words from a dictionary and creating a pattern map. A pattern map is map that consists of *pattern-words* pairs, where *pattern* is a string obtained by replacing any one letter from a word from the dictionary with the wildcard character *, and *words* is an array of words that differ by the wildcard character to the pattern (e.g. the words fall, hall, call correspond to the *all pattern). The program then builds a graph with edges between words that correspond to the same pattern and utilizes breadth-first search to find the shortest path between any two words. 

### Tools

C++14

Qt 6.9.0


