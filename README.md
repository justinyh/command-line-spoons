# Welcome to Command Line Spoons!

## Description
This project is a rudimentary form of the card game, Spoons, that is to be played on the command line.

## Compilation
To build the executable, type the following into the command prompt:
`make all`

## Running the Program
To run the program, type the following into the command prompt and then follow the onscreen instructions.
`./game`

## Spoons Instructions
* Your ultimate goal is to get a spoon. One player will not receive a spoon and will be deemed the loser.
* In order to get a spoon, you must collect four cards of the same NUMBER.
* At any given time you will have five cards in your hand. The program draws for you.
* You will select a card that you would like to discard and then press 'Return'.
* When you get four cards of the same NUMBER, press the 's' key and then 'Return' to grab a spoon.
* If a computer grabs a spoon, press the 's' key and then 'Return' as quickly as possible to avoid becoming the loser.
* GOOD LUCK!

## Design & Rationale
### Object-Oriented Programming & Data Storage
I created several custom objects in order to create this game. At the most basic level, there was a singular Card object. Then, the Deck object held up to 52 cards in a vector while the Hand object held 5 cards in a vector. A Spoons object managed the taking of the spoons.

### Random Number Generators
I utilized several random number generators that allow the program to mimic human functions. The first one runs once the user is dealt their cards and will store a number between 30-75. This number represents the number of seconds that will elapse before the computer will take a spoon. 

After the first spoon is grabbed by a computer, another random number generator will run and store a number between 500-1000. This number represents the amount of time before the next computer will grab a spoon. This random number generator is inside a for loop that will run for each computer, mimicking the randomness of human reaction time.

### Asynchronous Functions & Multithreading
This program also utilizes multithreading and asynchronous functions in C++. Once the hand is dealt, the program will execute a asynchronous function that waits for the designated amount of time before taking a spoon. This creates a new thread that allows the player to continue searching for a matching set while the timer continues. Without using multithreading, we would not be able to both set a "wait" timer and allow the user to continue play - at least in C++. 

## Have fun!
