#include "hand.h"
#include <iostream>
#include <thread>

using namespace std;

void Hand::addToHand(Card c) {
    currHand.push_back(c);
}

void Hand::printHand() {
    // PRINTS HAND IN ASCII ART
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

void Hand::replaceAndDiscard(int idx, Card c, Deck& discard) {
    discard.addCard(currHand[idx]);
    cout << "Drawing..." << endl;
    this_thread::sleep_for(chrono::milliseconds(750));
    currHand[idx] = c;
}

Card Hand::get(int idx) {
    return currHand[idx];
}