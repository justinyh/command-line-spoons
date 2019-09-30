#include <iostream>
#include "card.h"

using namespace std;

Card::Card() { }

Card::Card(char c, int n) {
    suit = c;
    number = n;
}

int Card::getNumber() {
    return number;
}

string Card::getNumberAsString() {
    if (number == 11) return "J";
    else if (number == 12) return "Q";
    else if (number == 13) return "K";
    else if (number == 1) return "A";
    else return to_string(number);
}

string Card::getSuitAsString() {
    if (suit == 'S') return "\u2664";
    else if (suit == 'C') return "\u2667";
    else if (suit == 'H') return "\u2661";
    else return "\u2662";
}