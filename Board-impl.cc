module board;
import <iostream>;
using namespace std;

Board::Board() : Subject(), numPlayers(0), currentPlayerIndex(0), Players(vector<shared_ptr<Player>>()), GameBoard(vector<Square*>()) {}

void Board::init() {
    //key val pairs of (posn, name)
    map<int, string> squares = {
        {0, "Collect OSAP"},
        {1, "AL"},
        {2, "SLC"},
        {3, "ML"},
        {4, "Tuition"},
        {5, "MKV"},
        {6, "ECH"},
        {7, "NEEDLES HALL"},
        {8, "PAS"},
        {9, "HH"},
        {10, "DC Tims Line"},
        {11, "RCH"},
        {12, "PAC"},
        {13, "DWE"},
        {14, "CPH"},
        {15, "UWP"},
        {16, "LHI"},
        {17, "SLC"},
        {18, "BMH"},
        {19, "OPT"},
        {20, "Goose Nesting"},
        {21, "EV1"},
        {22, "NEEDLES HALL"},
        {23, "EV2"},
        {24, "EV3"},
        {25, "V1"},
        {26, "PHYS"},
        {27, "B1"},
        {28, "CIF"},
        {29, "B2"},
        {30, "GO TO TIMS"},
        {31, "EIT"},
        {32, "ESC"},
        {33, "SLC"},
        {34, "C2"},
        {35, "REV"},
        {36, "NEEDLES HALL"},
        {37, "MC"},
        {38, "COOP FEE"},
        {39, "DC"}
    }; 
    
    GameBoard.clear(); //clears existing vector of squares, if any

    for (auto [posn, name] : squares) {
        if (AcademicBldg::Names.contains(name)) { 
            GameBoard.emplace_back(new AcademicBldg(posn, name)); // square is an academic bldg
        } else if (Gym::Names.contains(name)) {
            GameBoard.emplace_back(new Gym(posn, name));   // square is a gym
        } else if (Residence::Names.contains(name)) {
            GameBoard.emplace_back(new Residence(posn,name)); // square is a residence
        } else if (name == "SLC") {
            GameBoard.emplace_back(new SLC(posn,name)); // square is SLC
        } else if (name == "NEEDLES HALL") {
            GameBoard.emplace_back(new NH(posn,name)); // square is NH
        } else if (name == "Tuition") {
            GameBoard.emplace_back(new Tuition(posn,name)); // square is NH
        } else {
            GameBoard.emplace_back(new NonProperty(posn,name)); // make non property
        }
    }
}

void Board::buy(int playerIndex, int posn){
    Property* property = dynamic_cast<Property*>(getGameBoard()[posn]);  
    //int cost = property.getCost();
    //if not enough money then not allowed
    property->setOwner(Players[playerIndex]); // sets owner of property to player

    Players[playerIndex]->addProperty(posn, property->getName());
    cout << Players[playerIndex]->getName() << " paid $" << property->getCost() << endl;
    Players[playerIndex]->addMoney(-property->getCost(), 0);
}

void Board::payFee(int player1Index, int player2Index,int posn) {
    if(Players[player2Index]->getChar() != Players[player1Index]->getChar()) {
        //check if player has enough money to send fees
        int value = (*GameBoard[posn]).calculateFees();
        if(Players[player1Index]->getMoney() < value) {
            //if not, player is bankrupt
            cout << "Player " << Players[player1Index]->getName() << " is bankrupt. They have two options" << endl;
            cout << "1. Declare bankruptcy" << endl;
            cout << "2. Raise Money" << endl;
            cout << "Enter 1 or 2" << endl;
            int choice;
            cin >> choice;
            if(choice == 1) {
                bankruptPlayer(Players[player1Index], Players[player2Index]);
            }
        } else {
            //player pays rent to owner
            cout << Players[player1Index]->getName() << " paid $" << value << " to " << Players[player2Index]->getName() << endl;
            Players[player2Index]->addMoney(value, value);
            Players[player1Index]->addMoney( 0-value, 0-value);
        }
    }
}

void Board::timsLineOptions() {
    cout << "You did not roll doubles." << endl;
    bool optionOne = false; //Pay $50
    bool optionTwo = false; //Use Rim Cup
    bool optionThree = false; //Stay in tims line

    if (Players[currentPlayerIndex]->getMoney() >= 50) { optionOne = true;}
    if (Players[currentPlayerIndex]->getTimsCups() > 0) { optionTwo = true;}
    if (Players[currentPlayerIndex]->getTimsTurns() != 3) { optionThree = true;}
    int totalOptions = optionOne + optionTwo + optionThree;
    int choice = 0;
    int selectedOption = 0;
    
    if (totalOptions == 0) {
        bankruptBank(Players[currentPlayerIndex]);
        cout << "No options available. Player is bankrupt." << endl;
        return;
    } else if (totalOptions == 1) {
        if (optionOne) {selectedOption = 1;}
        if (optionTwo) {selectedOption = 2;}
        if (optionThree) {selectedOption = 3;}
    } else {
        while (selectedOption == 0) {
            int count = 1;

            //Print out options
            cout << "Choose an option: " << endl;
            if (optionOne) { cout << count++ << ". Pay $50" << endl; }
            if (optionTwo) { cout << count++ << ". Use Rim cup" << endl; }
            if (optionThree) { cout << count++ << ". Stay in Tims Line" << endl; }
            
            //Get User Choice and validate
            cin >> choice;
            if (choice == 1) {
                if (optionOne) { 
                    selectedOption = 1;
                } else if (optionTwo) { 
                    selectedOption = 2;
                } else if (optionThree) { 
                    selectedOption = 3;
                }
            } else if (choice == 2) {
                if (optionOne && optionTwo) { 
                    selectedOption = 2;
                } else if (!optionOne && optionTwo && optionThree) { 
                    selectedOption = 3;
                } else if (optionOne && !optionTwo && optionThree) { 
                    selectedOption = 3;
                }
            } else if (choice == 3){
                if (optionOne && optionTwo && optionThree) { selectedOption = 3;}
            }
            cin.ignore();
        }
    }

    if (selectedOption == 1) { // Pay $50
        Players[currentPlayerIndex]->addMoney(-50, -50);
        Players[currentPlayerIndex]->setInTimsLine(false);
        Players[currentPlayerIndex]->setTimsTurns(0);
        cout << "You are out of Tims Line" << endl;
    } 

    if (selectedOption == 2) { // Use Rim cup
        Players[currentPlayerIndex]->removeTimsCup();
        totalRimCups--;
        Players[currentPlayerIndex]->setInTimsLine(false);
        Players[currentPlayerIndex]->setTimsTurns(0);
        cout << "You are out of Tims Line" << endl;
    } 

    if (selectedOption == 3) { // Stay in Tims Line
        cout << "You are still in Tims Line" << endl;
        Players[currentPlayerIndex]->setTimsTurns(Players[currentPlayerIndex]->getTimsTurns()+1);
    }
}

//Implement movePlayer
void Board::movePlayer(shared_ptr<Player> p, int posn, bool toTims) {
    //Go To Tims
    int Position = posn;
    //p->setInTimsLine(toTims);

    //Go to Tims
    if (Position == 30) {
        p->setPosition(30, false);
        notifyObservers();
        //Position = 10;
        p->setInTimsLine(true);
        p->setPosition(10, true);
        // notifyObservers();
    }

    //Can only move players not in the tims line.
    if(!p->getInTimsLine() && p->getDoublesTurns() != 2) {
        p->setPosition(posn, toTims);
        //int Position = posn;
        //int money = p->getMoney();
        //int netWorth = p->getNetWorth();

        Property* property = dynamic_cast<Property*>(getGameBoard()[posn]);  
        NonProperty* nonProperty = dynamic_cast<NonProperty*>(getGameBoard()[posn]);  

        if (nonProperty) {
            //Goose Nesting
            if (posn == 20) {
                cout << p->getName() << " is attacked by a flock of nesting geese!" << endl;
            }

            //COOP fee
            if (posn == 38) {
                cout << p->getName() << " needs to pay $150 for Coop Fee. " << endl;
                p->addMoney(-150, -150); 
            }
        
            //Tuition
            if (typeid(*nonProperty) == typeid(Tuition)) {
                Tuition* tuitionSquare = dynamic_cast<Tuition*>(nonProperty);
                int tuition =  tuitionSquare->action(p);

                if(tuition <= p->getMoney()) {
                    p->addMoney(-tuition, -tuition);
                } else{
                    cout << "Player " << p->getName() << " is bankrupt. They have two options" << endl;
                    cout << "1. Declare bankruptcy" << endl;
                    cout << "2. Raise Money" << endl;
                    cout << "Enter 1 or 2" << endl;
                    int choice;
                    cin >> choice;
                    if(choice == 1) {
                        bankruptBank(p);
                    }
                }                
            }
        
            //SLC Actions
            if (typeid(*nonProperty) == typeid(SLC)) {
                SLC* slcSquare = dynamic_cast<SLC*>(nonProperty);
                notifyObservers();
                if (slcSquare) {
                    posn = slcSquare->action(p, totalRimCups);
                    cout << GameBoard[p->getPosition()]->getName() << endl;
                    if (posn == 30) {
                        movePlayer(p, posn, true);
                    } else {
                        movePlayer(p, posn, false);
                    }
                }
            }
        
            //Needles Hall actions
            if (typeid(*nonProperty) == typeid(NH)) {
                NH* nhSquare = dynamic_cast<NH*>(nonProperty);
                notifyObservers();
                if (nhSquare) {
                    nhSquare->action(p);
                    //notifyObservers();
                }
            }
        } else {
            // if it is a property they will have to either pay a fee or can buy the property
            int playerIndex = getCurrentPlayerIndex();
            //int posn = Players[playerNum].getPosition();

            int propertyOwnerId = -1;

            if (property->getOwner() == p) { // current player owns property , do nothing
                return;
            }

            for (int i = 0; i < numPlayers; i++) {
            //check if another player owns the property   
                if (Players[i]->ownsProperty(property->getName())) {
                    propertyOwnerId = i;
                    if (!property->isMortgaged()){ // not mortgaged, so pay owner
                        payFee(playerIndex, propertyOwnerId, posn);
                    }
                    break;
                }
            }

            //if no one owns the propery
            if (propertyOwnerId == -1 && Players[playerIndex]->getMoney() >= property->getCost()) {
                int command = 0;
                // cin.ignore(1000, '\n'); //clears invalid input

                while (command != 1 && command != 2) {
                    cout << "Would " << p->getName() << " like to buy property " << property->getName() << "?" << endl;
                    cout << "(1) Yes or (2) No" << endl;

                    cin >> command;
                    if (command == 1) { 
                        buy(playerIndex, posn); 
                        cout << p->getName() << " has bought " << property->getName() << "." << endl;
                        cin.ignore();
                        break;
                    } else if (command == 2) {
                        cout << p->getName() << " hasn't bought " << property->getName() << "." << endl;
                        auctionProperty(property); // triggers auction
                        cin.ignore();
                    } else {
                        cout << "Invalid input: Please enter (1) Yes or (2) No" << endl;
                        cin.clear();
                        cin.ignore();
                    }
                }
            }
        }    
    }
}

//Implement nextTurn
void Board::nextTurn() {
    currentPlayerIndex = (currentPlayerIndex + 1) % Players.size();
}

//Implement getGameBoard
vector<Square*>& Board::getGameBoard() { return GameBoard; }

//Implement getPlayers
vector<shared_ptr<Player>>& Board::getPlayers() { return Players; }

// getProperty(string propertyName)
Property* Board::getProperty(string propertyName) {
    for (Square* square : GameBoard) {
        if (!square) continue;
        Property* property = dynamic_cast<Property*>(square);
        if (!property) continue;
        if (property->getName() == propertyName) {
            return property;
        }
    }
    return nullptr; // Property not found
}

//Implement getCurrentPlayerIndex
int Board::getCurrentPlayerIndex() { return currentPlayerIndex; }

//Implement getNumPlayers
int Board::getNumPlayers() { return numPlayers; }

//Implement addPlayer
void Board::addPlayer(shared_ptr<Player> p) {
    Players.emplace_back(p);
    numPlayers++;
    //notifyObservers();
}

//Implement bankruptPlayer
void Board::bankruptPlayer(std::shared_ptr<Player> p, std::shared_ptr<Player> creditor) {
    p->setBankrupt(true);
    int val = p->getProperties().size();
    for (int i = 0; i < val; i++) {
        creditor->addProperty(p->getProperties().begin()->second, p->getProperties().begin()->first);
        //need to add property to creditor networth
        p->removeProperty(p->getProperties().begin()->first);
    }
    creditor->addMoney(p->getNetWorth(), p->getNetWorth());
    totalRimCups -= p->getTimsCups();
    Players.erase(Players.begin() + currentPlayerIndex);
    numPlayers--;
}

void Board::bankruptBank(std::shared_ptr<Player> p) {
    p->setBankrupt(true);
    
    for (const auto& [p, val]: p->getProperties()) {
        Property* property = dynamic_cast<Property*>(GameBoard[val]); 
        auctionProperty(property);
    }

    totalRimCups -= p->getTimsCups();
    Players.erase(Players.begin() + currentPlayerIndex);
    numPlayers--;
}

// auctionProperty(Property* property)
void Board::auctionProperty(Property* property) {
    int currentBid = 0;
    int winningIndex = -1; // -1 indicates no valid bid yet
    size_t passedCount = 0;
    
    cout << "Auctioning property: " << property->getName() << endl;
    cout << "Current highest bid: $" << currentBid << endl;

    vector<bool> passed(Players.size(), false); // Track if players have passed

    // Mark bankrupt players as passed
    for (size_t i = 0; i < Players.size(); i++) {
        if (Players[i]->isBankrupt()) {
            passed[i] = true;
            passedCount++;
        }
    }

    // If only one non-bankrupt player remains, they get the property for free
    if (passedCount == Players.size() - 1) {
        for (size_t i = 0; i < Players.size(); i++) {
            if (!passed[i]) {
                cout << Players[i]->getName() << " wins the auction automatically." << endl;
                Players[i]->addProperty(property->getPosn(), property->getName());
                property->setOwner(Players[i]);
                return;
            }
        }
    }

    // Auction loop
    while (passedCount < Players.size() - 1) {
        for (size_t i = 0; i < Players.size(); i++) {
            if (passed[i]) continue; // Skip players who have passed

            Player* player = Players[i].get();
            cout << player->getName() << " enter your bid (or 'pass' to pass): ";
            string input;
            cin >> input;

            if (input == "pass") {
                cout << player->getName() << " passed on the auction." << endl;
                passed[i] = true;
                passedCount++;
            } else {
                try {
                    int bid = stoi(input);
                    if (bid <= currentBid) {
                        cout << "Bid must be higher than the current highest bid ($" << currentBid << "). Try again: ";
                        continue; // Restart this player's turn
                    }
                    if (bid > player->getMoney()) {
                        cout << "You do not have enough money to make this bid. Try again." << endl;
                        continue; // Restart this player's turn
                    }
                    currentBid = bid;
                    winningIndex = i;
                    cout << player->getName() << " bids $" << bid << endl;
                } catch (invalid_argument&) {
                    cout << "Invalid input. Enter a valid bid or 'pass'." << endl;
                    continue; // Restart this player's turn
                }
            }

            // If only one player remains, they win the auction
            if (Players.size() - passedCount == 1) break;
        }
    }

    // Finalize auction
    if (winningIndex != -1) {
        cout << property->getName() << " is sold for $" << currentBid << " to " << Players[winningIndex]->getName() << endl;
        Players[winningIndex]->addProperty(property->getPosn(), property->getName());
        Players[winningIndex]->addMoney(-currentBid, property->getCost() - currentBid);
        property->setOwner(Players[winningIndex]);
    } else {
        cout << "No one placed a bid. The property remains unsold." << endl;
    }
}


Board::~Board() {
    for (auto square : GameBoard) {
        delete square; // Clean up each dynamically allocated square
    }
}
