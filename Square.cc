export module square;

import <vector>;
import <unordered_set>;
import <string>;
import <memory>;

import player;

//class AcademicBldg;

using namespace std;

export class Square {
    protected:
    int posn; // Position of square on board 0-39()
    std::string name; // Name of location
    std::vector<std::shared_ptr<Player>> playersAtSquare; // vector of players at the square
    int numPlayers; // num players at square
    bool improvable; // if square is improvable

    public:
    Square(int p, std::string n, bool imp); // Creates an initialized square called n at posn p
    virtual ~Square() = default;

    std::string getName() const; // returns name of location at square
    int getPosn() const; // returns posn of square on board

    virtual int calculateFees() const = 0;
};
