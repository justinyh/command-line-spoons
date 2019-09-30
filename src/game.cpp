#include "deck.h"
#include "spoons.h"
#include "hand.h"

#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <mutex>             
#include <condition_variable>
#include <algorithm>
#include <vector>

using namespace std;

condition_variable cv;
mutex mtx;

bool waitFunc (int timetowait, Spoons* middle, int num_players) {
    unique_lock<mutex> lck(mtx);
    if (cv.wait_for(lck,chrono::seconds(timetowait)) == cv_status::timeout) {
        srand(time(NULL));
        for (int i = 0; i < num_players-1; i++) {
            if (middle->getNumSpoons() > 0) middle->takeSpoon();
            else return false;
            if (i != num_players - 2) {
                int spoontime = (rand() % 500)+500;
                cv.wait_for(lck,chrono::milliseconds(spoontime));
            }
        }
    }
    else return false;
    return true;
}

int main(int argc, char* argv[]) {
    cout << "Welcome to Command Line Spoons." << endl;
    cout << "Please adjust your command line window size so you can only see these instructions and the following cards. Press any key to continue." << endl; 
    Hand example;
    for (int i = 0; i < HAND_SIZE; i++) {
        example.addToHand(Card('S', 1));
    }
    example.printHand();
    char input;
    cin >> input;

    cout << "How many players would you like to play against? (Recommended: 3-6)" << endl;
    int num_players;
    cin >> num_players;
    num_players++;

    cout << "Instructions: " << endl;
    cout << "- Your ultimate goal is to get a spoon. There are only " + to_string(num_players-1) + " spoons available."  << endl;
    cout << "- In order to get a spoon, you must collect four cards of the same NUMBER." << endl;
    cout << "- At any given time you will have five cards in your hand." << endl;
    cout << "- Place your left fingers on the y, u, i, o, and p keys. Use these keys to select the card you would like to discard and then press 'Return'." << endl;
    cout << "- When you get four cards of the same NUMBER, press the 's' key and then 'Return' to grab a spoon." << endl;
    cout << "- If a computer grabs a spoon, press the 's' key and then 'Return' as quickly as you possibly can." << endl;
    cout << "GOOD LUCK. PRESS ANY KEY TO CONTINUE." << endl;

    cin >> input;
    char playAgain = '\0';
    while (playAgain != 'n') {
        playAgain = ' ';
        srand(time(NULL));
        int time = (rand() % 45) + 20; // time to computer draw of spoons

        // Initialize Starting Deck
        Deck initial, discard;
        initial.populate();
        Hand curr;
        Spoons middle(num_players);
        for (int i = 0; i < HAND_SIZE; i++) {
            curr.addToHand(initial.drawCard());
        }

        // Countdown
        cout << "The game will start in..." << endl;
        for (int i = 3; i >= 0; i--) {
            this_thread::sleep_for(chrono::seconds(1));
            cout << i << endl;
        }
        cout << "GO!" << endl;

        future<bool> fut = async(launch::async,waitFunc, time, &middle, num_players);

        while (middle.getNumSpoons() > 0) {
            if (initial.empty()) {
                swap(initial, discard);
            }

            cout << "YOUR CURRENT HAND:" << endl;
            curr.printHand();
            char discardCard;
            cin >> discardCard;

            if (discardCard == 's') {
                int matches = curr.get(0).getNumber();
                int num_of_matches = 1;
                for (int i = 1; i < HAND_SIZE; i++) {
                    if (curr.get(i).getNumber() == matches) num_of_matches++;
                    else {
                        if (i == 1) {
                            matches = curr.get(1).getNumber();
                        }
                    }
                } 
                if ((num_of_matches == HAND_SIZE-1 && middle.getNumSpoons() > 0) || middle.getNumSpoons() < num_players-1) {
                    bool result = middle.takeUserSpoon();
                    if (!result) break;
                    cv.notify_all();
                    break;
                }
                else if (middle.getNumSpoons() == 0) break;
                else {
                    cout << "You do not have four of a kind. Try again later." << endl;
                }
            }
            else if (discardCard == 'y') {
                curr.replaceAndDiscard(0, initial.drawCard(), discard);
            }
            else if (discardCard == 'u') {
                curr.replaceAndDiscard(1, initial.drawCard(), discard);
            }
            else if (discardCard == 'i') {
                curr.replaceAndDiscard(2, initial.drawCard(), discard);
            }
            else if (discardCard == 'o') {
                curr.replaceAndDiscard(3, initial.drawCard(), discard);
            }
            else if (discardCard == 'p') {
                curr.replaceAndDiscard(4, initial.drawCard(), discard);
            }
            else {
                cout << "Not a valid command. Please use y,u,i,o, or p to make your selection." << endl;
            }
        }

        if (fut.get() == true) {
            cout << "You lost. The computer was faster than you! Try again? (y/n)" << endl;
        }
        else {
            cout << "Congratulations! You were faster than the computer!" << endl;
        }
        
        while (playAgain != 'y' && playAgain != 'n') {
            cout << "Would you like to play again? Please respond with either y or n." << endl;
            cin >> playAgain;
        }
        
    }



    cout << "Thanks for playing! See you next time!" << endl;
    return 0;
}