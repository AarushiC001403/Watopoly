module nonproperty;
using namespace std;

const std::unordered_set<std::string> NonProperty::Names {
    "Collect OSAP", "SLC", "Tuition", "Needles Hall", "DC Tims Line",
    "Goose Nesting", "Go to Tims", "Coop Fee"
};

NonProperty::NonProperty(int posn, std::string name) : Square(posn, name, false) {}

int NonProperty::calculateFees() const {
    return 0;
}

// int NonProperty::calculateCost() const {
//     return 0;
// }
