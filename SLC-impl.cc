module slc;
using namespace std;

SLC::SLC(int posn, string name) : NonProperty(posn, name) {}

bool SLC::rimCupChance() {
    return (rand() % 100) == 0;
}

int SLC::action(shared_ptr<Player> p, int &totalRimCups) {
    int chance = rand() % 24 + 1;

    //int totalRimCups = 0;

    if (totalRimCups <= 4 && rimCupChance()) {
        cout << p->getName() << " has found a rim cup! " << endl;
        p->addTimsCup();
        totalRimCups++;
    } else if (totalRimCups > 4) {
        cout << " There can only be 4 rim cups in the game at a time. " << endl;
    } else {
        cout << "You have not found a Roll Up the Rim Cup this time. " << endl;
    }

    cout << p->getName() << " is at SLC Square. ";
    cout << p->getName() << " must ";

    if (chance <= 3) {
        cout << "move back 3 squares to ";
        return (p->getPosition() - 3 + 40) % 40;
        //cout << p->getName() << " was at SLC. " ;
        //p->setPosition(newPos);
        //cout << "Player has now moved back 3 sqaures to " << newPos << endl;

    } else if (chance <= 7) {
        cout << "move back 2 squares to ";
        return (p->getPosition() - 2 + 40) % 40;
        //cout << p->getName() << " was at SLC. ";
        //p->setPosition(newPos);
        //cout << "Player has now moved back 2 sqaures to " << newPos << endl;

    } else if (chance <= 11) {
        cout << "move back 1 square to ";
        return (p->getPosition() - 1 + 40) % 40;
        //cout << p->getName() << " was at SLC. ";
        //p->setPosition(newPos);
        //cout << "Player has now moved back 1 sqaures to " << newPos << endl;

    } else if (chance <= 14) {
        cout << "move forward 1 square to ";
        return (p->getPosition() + 1) % 40;
        //cout << p->getName() << " was at SLC. ";
        //p->setPosition(newPos);
        //cout << "Player has now moved forward 1 sqaures to " << newPos << endl;

    } else if (chance <= 18) {
        cout << "move forward 2 squares to ";
        return (p->getPosition() + 2) % 40;
        //cout << p->getName() << " was at SLC. ";
        //p->setPosition(newPos);
        //cout << "Player has now moved forward 2 sqaures to " << newPos << endl;


    } else if (chance <= 22) {
        cout << "move forward 3 squares to ";
        return (p->getPosition() + 3) % 40;
        //cout << p->getName() << " was at SLC. ";
        //p->setPosition(newPos);
        //cout << "Player has now moved forward 3 sqaures to " << newPos << endl;

    } else if (chance == 23) {
        cout << "move to ";
        //cout << p->getName() << " was at SLC. ";
        //p->setPosition(10, true);
        return 10;
        //cout <<  "Player has now moved to DC Tims Line. " << endl;

    } else {
        cout << "advance to ";
        //cout << p->getName() << " was at SLC. ";
        return 0;
        //p->setPosition(0);
        //cout <<  "Player has now moved to Collect OSAP. " << endl;
    }
}
