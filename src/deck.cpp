#include <iostream>
#include "deck.h"

using namespace std;

void Deck::populate() {
    char suits[4] = {'C', 'S', 'D', 'H'};
    for (int i = 1; i < 14; i++) {
        for (int j = 0; j < 4; j++) {
            Card temp(suits[j], i);
            pile.push_back(temp);
        }
    }
    shuffleDeck();
}

void Deck::addCard(Card c) {
    pile.push_back(c);
}

Card Deck::drawCard() {
    Card temp = pile[pile.size()-1];
    pile.pop_back();
    return temp;
}

void Deck::shuffleDeck() {
    srand(time(NULL));
    for (int i = 0; i < NUM_CARDS;i++) 
    { 
        int j = i + (rand() % (52 - i));
        swap(pile[i], pile[j]); 
    }
}

bool Deck::empty() {
    return pile.size() == 0;
}