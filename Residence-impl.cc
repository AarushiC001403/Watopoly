module residence;
using namespace std;

Residence::Residence(int posn, string name) : Property(posn, name, false) {
    Cost = 200;
}

int Residence::calculateFees() const {
    if (ResidencesOwned(*getOwner()) == 1) {
       return 25; 

    } else if (ResidencesOwned(*getOwner()) == 2) {
        return 50;

    } else if (ResidencesOwned(*getOwner()) == 3) {
        return 100;
        
    } else {
        return 200;
    }
}

int Residence::ResidencesOwned(Player &p) const {
    int count = 0;
    for (auto [name, posn] : p.getProperties()) {
        if (Residence::Names.contains(name)) {
            count++;
        }
    }
    return count;
}

const std::unordered_set<std::string> Residence::Names { "REV", "V1", "MKV", "UWP" };
