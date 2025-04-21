export module property;
import <string>;
import <map>;
import <unordered_set>;
import <memory>;

import square;
import player;

using namespace std;

// property is an absract base class

export class Property : public Square {
    protected:
    bool Mortgaged;
    shared_ptr<Player> Owner; // pointer to owner, null if unowned.
    int Cost;   // price to buy property
    string monopolyGroup; // name of Properties monopoly group
    //bool inMonopoly; // if owner owns all building in monopoly
    string findMonopolyGroup(string name); // finds monopoly group of bldg

    public:
    Property(); // Default Constructor
    Property(int posn, const string& name, bool imp); // Constructor

    bool isMortgaged() const; // returns true if is mortgaged, false otherwise
    void setMortgaged(bool mortgaged); // sets mortgaged to bool 'mortgaged'
    //void buyProperty(Player &p); // assigns new owner and deducts price of property from owners balance
    //void payOwner(Player &other); // pays owner of property the rent (PlayerFee), from others balance

    virtual shared_ptr<Player> getOwner() const; // returns ptr to owner of property
    virtual void setOwner(shared_ptr<Player> p); // sets owner of property

    virtual int calculateFees() const override = 0; // returns fee to pay owner
    int getCost(); // returns price to buy property
    
    virtual bool hasImprovements() const; // returns true if has improvements


    void addProperty(shared_ptr<Player> p);
    void removeProperty(shared_ptr<Player> p);

    string getMonopolyGroup(); // returns name of monopoly group
    bool hasMonopoly() const;

    static const map<string, unordered_set<string>> monopolyGroups;
};
