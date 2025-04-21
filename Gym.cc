export module gym;
import <unordered_set>;
import <string>;
import property;
import player;

export class Gym : public Property {

    public:
    static const std::unordered_set<std::string> Names; // list of names
    Gym(int posn, std::string name); //ctor
    int GymsOwned(Player &p) const;
    int calculateFees() const override;
    int rollDice() const; 
};
