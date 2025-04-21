module square;
import <iostream>;

using namespace std;

Square::Square(int p, string n, bool imp) : posn(p), name(n), playersAtSquare(), numPlayers(0), improvable(imp) {}

string Square::getName() const {
    return name;
}

int Square::getPosn() const {
    return posn;
}

