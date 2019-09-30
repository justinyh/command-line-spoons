#include "spoons.h"
#include <iostream>

using namespace std;

Spoons::Spoons(int num_players) {
    number = num_players-1;
    taken = 0;
}

void Spoons::takeSpoon() {
    number--;
    taken++;
    cout << taken << " SPOON(S) TAKEN. " << number << " LEFT." << endl;
}

bool Spoons::takeUserSpoon() {
    if (number == 0) return false;
    number--;
    taken++;
    cout << "You got a spoon! There's " << number << " left." << endl;
    return true;
}

int Spoons::getNumSpoons() {
    return number;
}