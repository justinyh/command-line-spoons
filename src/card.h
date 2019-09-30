#ifndef CARD_H
#define CARD_H

#include <string>

class Card {
    public:
        Card();
        Card(char c, int n);
        int getNumber();
        std::string getNumberAsString();
        std::string getSuitAsString();
    
    private:
        char suit;
        int number;
};

#endif