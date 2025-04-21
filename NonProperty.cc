export module nonproperty;
import <unordered_set>;
import <string>;
import square;
import player;
//import board;

using namespace std;

export class NonProperty : public Square {
    protected:
    
    public:
    NonProperty(int posn, string name);
    int calculateFees() const override; // returns fee to pay owner
    static const unordered_set<string> Names;
};
