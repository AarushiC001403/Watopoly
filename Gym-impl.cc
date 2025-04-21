module gym;
import <iostream>;

using namespace std;

const std::unordered_set<std::string> Gym::Names { "CIF", "PAC" };

Gym::Gym(int posn, string name) : Property(posn, name, false) {
    Cost = 150;
} //150 default price all gyms

int Gym::calculateFees() const {
    cout << "Calculating fees for gym" << endl;
    if (GymsOwned(*getOwner()) == 2) {
        int dice1 = rollDice(); // 10 times dice roll if 2 gyms owned
        cout << "Dice 1: " << dice1 << endl;
        int dice2 = rollDice(); // 10 times dice roll if 2 gyms owned
        cout << "Dice 2: " << dice2 << endl;
        cout << "You have to pay 10 times the sum of the dice rolls. " << endl;
        return ((dice1 + dice2) * 10);
    }

    if (GymsOwned(*getOwner()) == 1) {
        int dice1 = rollDice(); // 4 times dice roll if 2 gyms owned
        cout << "Dice 1: " << dice1 << endl;
        int dice2 = rollDice(); // 4 times dice roll if 2 gyms owned
        cout << "Dice 2: " << dice2 << endl;
        cout << "You have to pay 4 times the sum of the dice rolls. " << endl;
        return ((dice1 + dice2) * 4); 
    }
    return 0;
}

int Gym::GymsOwned(Player &p) const {
    int count = 0;
    for (auto [name, posn] : p.getProperties()) {
        if (Names.contains(name)) {
            count++;
        }
    }
    return count;
}

int Gym::rollDice() const{
    //cout << "Rolling dice for gym" << endl;
    return rand() % 6 + 1;
}
