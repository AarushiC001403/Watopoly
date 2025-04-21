// dice-impl.cc
module dice; // Use 'module' to refer to the previously declared module

import <random>;

int Dice::rollDice() {
    std::random_device rd; // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Initialize random number generator
    std::uniform_int_distribution<> dist(1, 6); // Distribution from 1 to 6
    return dist(gen); // Generate and return the dice roll value
}
