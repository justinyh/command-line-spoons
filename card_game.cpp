/* 

Mimicking human behavior
 - how to decide when computer will pick up spoon. Use a random number generator to choose a time between 30seconds and 1.5 minutes. Use delay function
 - card picking up. when player drops a card, next card will pop up. cards go into a discard pile (what structure?). Will be reused after getting to the end.
 - Discard using Y, U, I, O, P keys
 - Card object, char suit (C, D, S, H), string number (A, 2, 3, 4...)
    - Methods: printCard, 
 - Deck object, holds cards.
    - Methods: drawCard,




*/

#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <mutex>             
#include <condition_variable>
#include <algorithm>
#include <vector>

using namespace std;

const int NUM_CARDS = 52;
int NUM_PLAYERS;
condition_variable cv;

class Spoons {
    public:
        Spoons() {
            number = NUM_PLAYERS-1; // CHANGE
            taken = 0;
        }
        void takeSpoon() {
            number--;
            taken++;
            cout << taken << " SPOON(S) TAKEN. " << number << " LEFT." << endl;
        }

        bool takeUserSpoon() {
            if (number == 0) return false;
            number--;
            taken++;
            cout << "You got a spoon! There's " << number << " left." << endl;
            return true;
        }

        int getNumSpoons() {
            return number;
        }
        
    
    private:
        int number;
        int taken;
};

bool waitFunc (int timetowait, Spoons* middle) {
    mutex mtx;
    unique_lock<mutex> lck(mtx);
    if (cv.wait_for(lck,chrono::seconds(timetowait)) == cv_status::timeout) {
        srand(time(NULL));
        for (int i = 0; i < NUM_PLAYERS-1; i++) {
            if (middle->getNumSpoons() > 0) middle->takeSpoon();
            else return false;
            if (i != NUM_PLAYERS-2) {
                int spoontime = (rand() % 500)+500;
                cv.wait_for(lck,chrono::milliseconds(spoontime));
            }
        }
    }
    else return false;
    return true;
}

class Card {
    public:
        Card() {}
        Card(char c, int n) {
            suit = c;
            number = n;
        }
        void printCard() {
            string uni;
            string num;
            if (number == 11) num = "J";
            else if (number == 12) num = "Q";
            else if (number == 13) num = "K";
            else num = to_string(number);
            if (suit == 'S') uni = "\u2664";
            else if (suit == 'C') uni = "\u2667";
            else if (suit == 'H') uni = "\u2661";
            else if (suit == 'D') uni = "\u2662";

            cout << "   _________" << endl;
            cout << "   |    " << (num=="10"?"":" ") << num << " |" << endl;
            cout << "   |     " << uni << " |" << endl;
            cout << "   |       |" << endl;
            cout << "   | " << uni << "     |" << endl;
            cout << "   | " << num << (num=="10"?"":" ") << "    |" << endl;
            cout << "   ---------" << endl;
                        
        }
        int getNumber() {
            return number;
        }

        string getNumberAsString() {
            if (number == 11) return "J";
            else if (number == 12) return "Q";
            else if (number == 13) return "K";
            else if (number == 1) return "A";
            else return to_string(number);
        }

        string getSuitAsString() {
            if (suit == 'S') return "\u2664";
            else if (suit == 'C') return "\u2667";
            else if (suit == 'H') return "\u2661";
            else return "\u2662";

        }
    
    private:
        char suit;
        int number;
};

class Deck {
    public: 

        void populate() {
            char suits[4] = {'C', 'S', 'D', 'H'};
            for (int i = 1; i < 14; i++) {
                for (int j = 0; j < 4; j++) {
                    Card temp(suits[j], i);
                    pile.push_back(temp);
                }
            }
            shuffleDeck();
        }

        void addCard(Card c) {
            pile.push_back(c);
        }

        Card drawCard() {
            Card temp = pile[pile.size()-1];
            pile.pop_back();
            return temp;
        }
        void shuffleDeck() {
            srand(time(NULL));
            for (int i = 0; i < NUM_CARDS;i++) 
            { 
                int j = i + (rand() % (52 - i));
                swap(pile[i], pile[j]); 
            }
        } 
        bool empty() {
            return pile.size() == 0;
        }
            
    private:
        vector<Card> pile;
};

class Hand {
    public:
        void addToHand(Card c) {
            currHand.push_back(c);
        }

        void printHand() {
            cout << "   _________  _________  _________  _________  _________" << endl;
            cout << "   |    " << (currHand[0].getNumberAsString() =="10"?"":" ") << currHand[0].getNumberAsString() << " |  |    " <<
            (currHand[1].getNumberAsString()=="10"?"":" ") << currHand[1].getNumberAsString() << " |  " << "|    " << (currHand[2].getNumberAsString()=="10"?"":" ") <<
            currHand[2].getNumberAsString() << " |  |    " << (currHand[3].getNumberAsString()=="10"?"":" ") << currHand[3].getNumberAsString() << " |  |    " << 
            (currHand[4].getNumberAsString()=="10"?"":" ") << currHand[4].getNumberAsString() << " |" << endl;
            cout << "   |     " << currHand[0].getSuitAsString() << " |  |     " << currHand[1].getSuitAsString() << " |  |     " <<
            currHand[2].getSuitAsString() << " |  |     " << currHand[3].getSuitAsString() << " |  |     " << currHand[4].getSuitAsString() << " |" << endl;
            cout << "   |       |  |       |  |       |  |       |  |       |" << endl;
            cout << "   | " << currHand[0].getSuitAsString() << "     |  | " << currHand[1].getSuitAsString() << "     |  | " << currHand[2].getSuitAsString() << 
            "     |  | " << currHand[3].getSuitAsString() << "     |  | " << currHand[4].getSuitAsString() << "     |" << endl;
            cout << "   | " << currHand[0].getNumberAsString() << (currHand[0].getNumberAsString() =="10"?"":" ") << "    |  | " << 
            currHand[1].getNumberAsString() << (currHand[1].getNumberAsString()=="10"?"":" ") << "    |  " << "| " << currHand[2].getNumberAsString() << (currHand[2].getNumberAsString()=="10"?"":" ") << 
            "    |  | " << currHand[3].getNumberAsString() << (currHand[3].getNumberAsString()=="10"?"":" ") << "    |  | " << currHand[4].getNumberAsString() << 
            (currHand[4].getNumberAsString()=="10"?"":" ") << "    |" << endl;
            cout << "   ---------  ---------  ---------  ---------  ---------" << endl;
            cout << "      [y]        [u]        [i]        [o]        [p]  " << endl;   
        }

        void replaceAndDiscard(int idx, Card c, Deck& discard) {
            discard.addCard(currHand[idx]);
            cout << "Drawing..." << endl;
            this_thread::sleep_for(chrono::milliseconds(750));
            currHand[idx] = c;
        }

        Card get(int idx) {
            return currHand[idx];
        }
    private:
        vector<Card>currHand;
};

int main(int argc, char* argv[]) {
    cout << "Welcome to Command Line Spoons." << endl;
    cout << "Please adjust your command line window size so you can only see these instructions and the following cards. Press any key to continue." << endl; // PLEASE ADJUST THE SIZE OF YOUR SCREEN
    Hand example;
    for (int i = 0; i < 5; i++) {
        example.addToHand(Card('S', 1));
    }
    example.printHand();
    char input;
    cin >> input;

    cout << "How many players would you like to play against? (Recommended: 3-6)" << endl;
    cin >> NUM_PLAYERS;

    cout << "Instructions: " << endl;
    cout << "- Your ultimate goal is to get a spoon. There are only " + to_string(NUM_PLAYERS-1) + " spoons available."  << endl;
    cout << "- In order to get a spoon, you must collect four cards of the same NUMBER." << endl;
    cout << "- At any given time you will have five cards in your hand." << endl;
    cout << "- Place your fingers on the y, u, i, o, and p keys. These will be used to select the card you would like to discard." << endl;
    cout << "- When you get four cards of the same NUMBER, press the 's' key and then 'Return' to grab a spoon." << endl;
    cout << "- If a computer grabs a spoon, press the 's' key and then 'Return' as quickly as you possibly can." << endl;
    cout << "GOOD LUCK. PRESS ANY KEY TO CONTINUE." << endl;

    cin >> input;
    char playAgain;
    while (playAgain != 'n') {
        playAgain = ' ';
        srand(time(NULL));
        int time = (rand() % 45) + 20; // time to computer draw of spoons

        // Initialize Starting Deck
        Deck initial, discard;
        initial.populate();
        Hand curr;
        Spoons middle;
        for (int i = 0; i < 5; i++) {
            curr.addToHand(initial.drawCard());
        }

        cout << "The game will start in..." << endl;
        for (int i = 3; i >= 0; i--) {
            this_thread::sleep_for(chrono::seconds(1));
            cout << i << endl;
        }
        cout << "GO!" << endl;

        future<bool> fut = async(launch::async,waitFunc, time, &middle);

        while (middle.getNumSpoons() > 0) {

            cout << "YOUR CURRENT HAND:" << endl;
            curr.printHand();
            char discardCard;
            cin >> discardCard;

            if (discardCard == 's') {
                int matches = curr.get(0).getNumber();
                int num = 1;
                for (int i = 1; i < 5; i++) {
                    if (curr.get(i).getNumber() == matches) num++;
                    else {
                        if (i == 1) {
                            matches = curr.get(1).getNumber();
                        }
                    }
                } 
                if (num == 4 || (middle.getNumSpoons() > 0)) {
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




    return 0;
}