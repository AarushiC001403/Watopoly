module needleshall;
using namespace std;

NH::NH(int posn, string name) : NonProperty(posn, name) {}

bool NH::rimCupChance() {
    return (rand() % 100) == 0;
}

int NH::action(shared_ptr<Player> p) {
    int chance = rand() % 18 + 1;
    int totalRimCups = 0;

    if (totalRimCups <= 4 && rimCupChance()) {
        cout << p->getName() << " has found a rim cup! " << endl;
        totalRimCups++;
    } else if (totalRimCups > 4) {
        cout << " There can only be 4 rim cups in the game at a time. " << endl;
    } else {
        cout << "You have not found a Roll Up the Rim Cup this time. " << endl;
    }

    cout << p->getName() << " is at Needles Hall. " << p->getName();
    cout << " must ";
    if (chance == 1) {
        //p->addMoney(-200,-200);
        cout << "must pay $200." << endl;
        return -200;

    } else if (chance <= 3) {
        //p->addMoney(-100,-100);
        cout << "must pay $100." << endl;
        return 100;

    } else if (chance <= 6) {
        //p->addMoney(-50,-50);
        cout << "must pay $50." << endl;
        return 50;

    } else if (chance <= 12) {
        //p->addMoney(25,25);
        cout << "recieves $25!" << endl;
        return 25;

    } else if (chance <= 15) {
        //p->addMoney(50,50);
        cout << "recieves $50!" << endl;
        return 50;

    } else if (chance <= 17) {
        //p->addMoney(100,100);
        cout << "recieves $100!" << endl;
        return 100;

    } else {
        //p->addMoney(200,200);
        cout << "recieves $200!" << endl;
        return 200;
    }
}
