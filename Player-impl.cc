module player;

using namespace std;

Player::Player() : name(""), character('?'), money(1500), netWorth(1500), Position(0), timsCups(0), timsTurns(0), inTimsLine(false), doublesTurns(0), ownedProperties(), turnOver(false), Bankrupt(false) {}

// Player(name)
Player::Player(std::string n, char c) : name(n), character(c), money(1500), netWorth(1500), Position(0), timsCups(0), timsTurns(0), inTimsLine(false), doublesTurns(0), ownedProperties(), turnOver(false), Bankrupt(false) {}

// getName()
string Player::getName() {
    return name;
}

// setName(n)
void Player::setName(string n) {
    name = n;
}

// getChar()
char Player::getChar() {
    return character;
}

// setChar(c)
void Player::setChar(char c) {
    character = c;
}

// getNetWorth()
int Player::getNetWorth() {
    // Player& currentPlayer = *this;
    // // Calculate net worth based on owned properties
    // for (const auto& property : ownedProperties) {
    //     int propertyValue = 0;
    //     netWorth += propertyValue; //Add the property value to the netWorth
    // }
    // if ()
    return netWorth;
}

// getMoney()
int Player::getMoney() {
    return money;
}

// setMoney(n)
void Player::setMoney(int cash){
    money = cash;
    netWorth = cash;
}

//addMoney(c, w)
void Player::addMoney(int cash, int worth) {
    money += cash;
    netWorth += worth;
}

// getDoublesTurns()
int Player::getDoublesTurns() {
    return doublesTurns;
}

// setDoublesTurns(n)  
void Player::setDoublesTurns(int n) {
    doublesTurns = n;
}

// getPosition()
int Player::getPosition() {
    return Position;
}

// setPosition(posn)
void Player::setPosition(int posn, bool toTims) {
    Position = posn;
    setInTimsLine(toTims);

    //Go to Tims
    if (Position == 10 && toTims) {
        //Position = 10;
        //setInTimsLine(true);
        setTimsTurns(1);
        //board.notifyObservers();
        cout << name << " is in the DC Tims Line. Wait for next turn." << endl;
    }
}

// // getNumProperties()
// int Player::getNumProperties() {
//     return ownedProperties.size();
// }

// // setNumProperties(n)
// void Player::setNumProperties(int n) {
//     numProperties = n;
// }


std::map<string, int> Player::getProperties() {
    return ownedProperties;
}

void Player::addProperty(int posn, string name) {
    ownedProperties[name] = posn;
    //numProperties++;
}

void Player::removeProperty(string name) {
    ownedProperties.erase(name);
    //numProperties--;
}

void Player::addTimsCup() {
    timsCups++;
}

void Player::removeTimsCup() {
    timsCups--; //Do we need to check if timsCups is 0 before removing?
}

int Player::getTimsCups() {
    return timsCups;
}

void Player::setTimsCups(int n) {
    timsCups = n;
}

int Player::getTimsTurns() {
    return timsTurns;
}

void Player::setTimsTurns(int n) {
    timsTurns = n;
}

bool Player::getInTimsLine() {
    return inTimsLine;
}

void Player::setInTimsLine(bool b) {
    inTimsLine = b;
}

bool Player::ownsProperty(const string& propertyName) const{
    if (ownedProperties.contains(propertyName)) return true;
    return false; // Property not found
}

bool Player::getTurnOver() {
    return turnOver;
}

void Player::setTurnOver(bool b) {
    turnOver = b;
}

bool Player::isBankrupt() {
    return Bankrupt;
}

void Player::setBankrupt(bool bankrupt) {
    Bankrupt = bankrupt;
}

string Player::print() {
    string line;
    line = name + " " + character + " " + to_string(timsCups) + " " + to_string(money) + " " + to_string(Position);
    if (Position == 10) {
        if (inTimsLine) {
            line += " 1 " + to_string(timsTurns);
        } else {
            line += " 0";
        }
    }
    return line;
}
