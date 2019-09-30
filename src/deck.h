#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <vector>

const int NUM_CARDS = 52;

class Deck {
    public: 
        void populate();
        void addCard(Card c);
        Card drawCard();
        void shuffleDeck();
        bool empty();
            
    private:
        std::vector<Card> pile;
};

#endif