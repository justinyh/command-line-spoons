#ifndef HAND_H
#define HAND_H

#include "card.h"
#include "deck.h"
#include <vector>

const int HAND_SIZE = 5;

class Hand {
    public:
        void addToHand(Card c);
        void printHand();
        void replaceAndDiscard(int idx, Card c, Deck& discard);
        Card get(int idx);

    private:
        std::vector<Card>currHand;
};

#endif