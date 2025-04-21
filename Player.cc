export module player;
import <string>;
//import <vector>;
import <map>;
import <iostream>;
import <memory>;

using namespace std;

class Property;

export class Player {
    protected:
    string name; // players name
    char character; // players character
    int money; // players balance of money
    int netWorth; // players balance of net worth
    int Position; // 0 to 39 (inclusive) representing a block on the board, where 0 is start
    int timsCups; // num of cups possessed by player
    int timsTurns; //num of turns player has been in DC Tims Line
    bool inTimsLine; // true if player is in DC Tims Line
    int doublesTurns; // number of turns player has taken
    std::map<string, int> ownedProperties;  // collection of propertys owned by player
    //int numProperties; // number of properties owned by player
    bool turnOver; // true if player has finished their turn
    bool Bankrupt;

    public:
    Player(); // Default Constructor
    
    Player(string n, char c); // Constructor

    string getName(); // returns players name
    void setName(string n); // sets players name

    char getChar(); // returns players character
    void setChar(char c); // sets players character

    int getMoney(); // returns players balance
    int getNetWorth(); // returns players balance
    void addMoney(int cash, int worth); // adds to players balance
    void setMoney(int money);

    int getDoublesTurns(); // returns number of turns player has taken
    void setDoublesTurns(int n); // sets number of turns player has taken

    int getPosition(); // returns players position
    void setPosition(int posn, bool inTims = false); // sets players position

    std::map<string, int> getProperties(); // returns properties owned by a player
    void addProperty(int posn, string name); // adds property to Players ownedProperties
    void removeProperty(string name); // removes property from Players ownedProperties

    int getNumProperties(); // returns number of properties player owns
    void setNumProperties(int n); // sets number of properties player owns

    void addTimsCup(); // adds a tims cup to player
    void removeTimsCup(); // removes a tims cup from player
    
    int getTimsCups(); // returns number of tims cups player has
    void setTimsCups(int n); // sets number of tims cups player has

    int getTimsTurns(); // returns number of turns player has been in DC Tims Line
    void setTimsTurns(int n); // sets number of turns player has been in DC Tims Line

    bool getInTimsLine(); // returns true if player is in DC Tims Line
    void setInTimsLine(bool b); // sets player to be in DC Tims Line

    bool ownsProperty(const string& name) const;

    bool getTurnOver(); // returns true if player has finished their turn
    void setTurnOver(bool b); // sets player to have finished their turn

    bool isBankrupt(); // returns true if player is bankrupt
    void setBankrupt(bool bankrupt); // sets bankruptcy of player

    string print();
}; 

