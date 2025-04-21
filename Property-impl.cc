module property;
import <iostream>;
using namespace std;

//Property::Property() : Square(0,""), Owner(nullptr), Price(0), PlayerFee(0)  {}

Property::Property( int posn, const string& name, bool imp) :
    Square(posn, name, imp),
    Mortgaged(false),
    Owner(nullptr),
    Cost(0),
    monopolyGroup(findMonopolyGroup(name)) {}

shared_ptr<Player> Property::getOwner() const{
    return Owner;
}

void Property::setOwner(shared_ptr<Player> p) {
    Owner = p;
}


// void Property::setFee(int f) {
//     fee = f;
// }

int Property::getCost() {
    return Cost;
}

bool Property::hasImprovements() const {
    return false;
}

bool Property::isMortgaged() const {
    return Mortgaged;
}

void Property::setMortgaged(bool mortgaged) {
    Mortgaged = mortgaged;
}

// void Property::setPrice(int price) {
//     Price = price;
// }

//std::string Property::getName() {
//    return name;
//}

// void Property::setName(string n) {
//     name = n;
// }

// int Property::getPosn() {
//     return posn;
// }

// void Property::setPosn(int p) {
//     posn = p;
// }

void Property::addProperty(shared_ptr<Player> p) { //adds property to Players owned Properties
    p->addProperty(getPosn(), getName());
}

void Property::removeProperty(shared_ptr<Player> p) { 
    p->removeProperty(getName());
}

// returns name of monopoly group
string Property::getMonopolyGroup() {
    return monopolyGroup;
}

// finds monopoly group field
string Property::findMonopolyGroup(string name) { 
    for (auto [group, academicbldgs] : monopolyGroups) {
        if (academicbldgs.contains(name)) {
            return group;
        }
    }
    throw std::runtime_error("Monopoly group not found : " + name);
}

bool Property::hasMonopoly() const {
    if (!Owner) return false; // if nullptr building doesnt have owner
    auto ownerProperties = Owner->getProperties(); // else find owners other properties

    auto groups = monopolyGroups.at(monopolyGroup); // finding list of properties in monopoly group 
    size_t numProperties = groups.size(); // num properties in groups
    size_t count = 0; 

    for (auto [name , posn] : ownerProperties) { // iterating through owners properties
        if (groups.contains(name)) count++; // owner owns member of monopoly group
        if (count == numProperties) return true; // owner owns all members of monopoly group
        }
    return false;
}

const std::map<string, unordered_set<string>> Property::monopolyGroups = {
    {"ARTS1" ,{"AL", "ML"}},
    {"ARTS2" ,{"ECH", "PAS", "HH"}},
    {"ENG" ,{ "RCH", "DWE", "CPH"}},
    {"HEALTH" ,{"LHI", "BMH", "OPT"}},
    {"ENV" ,{"EV1", "EV2", "EV3"}},
    {"SCI1" ,{"PHYS", "B1", "B2"}},
    {"SCI2" ,{ "EIT", "ESC", "C2"}},
    {"MATH" ,{ "MC", "DC"}},
    {"GYM" ,{ "PAC", "CIF"}},
    {"RESIDENCE" ,{ "MKV", "UWP", "V1", "REV"}}
};
