module tuition;
using namespace std;

Tuition::Tuition(int posn, string name) : NonProperty(posn, name) {}

int Tuition::action(shared_ptr<Player> p) {
    cout << p->getName() << " needs to pay tuition. ";
    int count = 1;
    int tenPercent = p->getNetWorth() * 0.1;
    
    if (p->getMoney() >= 300) {
        cout << "Choose an option: " << endl;
        cout << count << ". Pay $300" << endl;
        count++;
        cout << count << ". Pay 10% of net worth ($" << tenPercent << ")." << endl;
        int choice = 0;

        while (choice != 1 && choice != 2) {
            cin >> choice;
            cin.clear(); //unsure on the order
            cin.ignore(); // clear line
        }

        if (choice == 1) {
            cout << p->getName() << " paid $300 for tuition. " << endl;
            return 300;
        } else {
            cout << p->getName() << " paid $" << tenPercent << " for tuition. " << endl;
            return tenPercent;
        }

    } else {
        cout << p->getName() << " must pay 10% of net worth ($" << tenPercent << ")." << endl;
        cout << p->getName() << " paid $" << tenPercent << " for tuition. " << endl;
        return tenPercent;
        //p->addMoney(-tenPercent, -tenPercent);
    }
} //no action for osap

