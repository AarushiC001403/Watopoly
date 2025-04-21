export module residence;
import <unordered_set>;
import <string>;
import player;
import property;

export class Residence : public Property {
    // add any fields

    public:
    Residence(int posn, std::string name); //ctor
    int ResidencesOwned(Player &p) const; // returns num of residences owned by player, modifies p
    int calculateFees() const override; // calculates fees
    static const std::unordered_set<std::string> Names; // set of names of residences
};
