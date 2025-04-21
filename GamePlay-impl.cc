module gameplay;

using namespace std;

GamePlay::GamePlay(bool testing) : gameOver(false), testingMode(testing) {
    // Initialize game components
    board.init();
    display = new TextDisplay(&board);
    dice.push_back(Dice());
    dice.push_back(Dice());
}

GamePlay::~GamePlay() {
    delete display;
}

void GamePlay::start() {    
    string command;
    //cin.clear();
    cin.ignore();
    while (!gameOver) {
        shared_ptr<Player> currentPlayer = board.getPlayers()[board.getCurrentPlayerIndex()];
        if (!currentPlayer->getTurnOver()) {
            cout << currentPlayer->getName() << "'s turn." << endl;
        }
        cout << "Enter command: ";
        //cin.ignore();
        getline(cin, command);
        if (command.empty()) continue;
        processCommand(command);
        
        // Check if game is over after each command
        if (checkGameOver()) {
            gameOver = true;
            cout << "Game over! The winner is: " << board.getPlayers()[0]->getName() << endl;
        }
    }
}

void GamePlay::initializeGame() {
    // Ask for number of players
    int numPlayers;
    cout << "Enter number of players (2-6): ";
    cin >> numPlayers;
    
    if (numPlayers < 2 || numPlayers > 6) {
        cout << "Invalid number of players. Using 2 players." << endl;
        numPlayers = 2;
    }
    
    cin.ignore(); // Clear newline

    // Initialize players
    for (int i = 0; i < numPlayers; i++) {
        string name;
        char piece;
        
        cout << "Enter name for player " << (i+1) << ": ";
        cin >> name;
        
        //cout << "Select piece (G: Goose, B: GRT Bus, D: Tim Hortons Doughnut, P: Professor, S: Student, $: Money, L: Laptop, T: Pink Tie): ";
        cout << "Select piece (";
        long unsigned int count  = 0;
        for (auto const& [key, val] : pieces) {
            cout << key << ": " << val;
            if (count < pieces.size() - 1) {
                cout << ", ";
            }
            count++;
        }
        cout << ")" << endl;
        cin >> piece;
        while (pieces.find(piece) == pieces.end()) {
            cout << "Invalid piece. Select piece (";
            count = 0;
            for (auto const& [key, val] : pieces) {
                cout << key << ": " << val;
                if (count < pieces.size() - 1) {
                    cout << ", ";
                }
                count++;
            }
            cout << ")" << endl;
            cin >> piece;
            cin.clear();
            cin.ignore();
        }
        // Create player and add to board
        auto newPlayer = make_shared<Player>(name, piece);
        pieces.erase(piece);

        // Add player to board's player list
        board.addPlayer(newPlayer);
    }
    cout << board.getPlayers().size() << " players have been added." << endl;
    // Notify observers to draw the initial board
    board.notifyObservers();
    cout << "You can use the following commands: " << endl;
    cout << "roll, next, trade, improve, mortgage, unmortgage, bankrupt, assets, all, save, quit" << endl;
}

void GamePlay::initializeWithPlayers(const vector<shared_ptr<Player>>& players) {
    // Initialize game with existing players
    // ...
}

void GamePlay::loadBoard(const string& filename) {
    // Load board with players and properties
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file " << filename << endl;
        return;
    }
    
    int numPlayers;
    file >> numPlayers;
    board.Players.clear(); // clears existing board

    // Read and initialize players' data
    for (int i = 0; i < numPlayers; ++i) {
        string playerName;
        char playerChar;
        int TimsCups, money, position;
        file >> playerName >> playerChar >> TimsCups >> money >> position;
        // Add player to the game
        auto player = make_shared<Player>(playerName, playerChar);
        player->setName(playerName);
        player->setChar(playerChar);
        player->setTimsCups(TimsCups);
        player->setMoney(money);
        player->setPosition(position);

        // If position is 10, player is in DC Tims Line
        if (position == 10) {
            bool inLine;
            file >> inLine;
            player->setInTimsLine(inLine);
            if (inLine) {
                int turns;
                file >> turns;
                player->setTimsTurns(turns);
            }
        }
        board.addPlayer(player);
    }


    string name, owner;
    int improvements;

    while (file >> name >> owner >> improvements) {
        for (Square* square : board.GameBoard) {
            if (name != square->getName()) continue;
            
            Property* property = dynamic_cast<Property*>(square); // assuming shared_ptr<Square>
            if (!property) break; //is not property

            if (owner != "BANK") {
                for (auto& player : board.getPlayers()) {
                    if (player->getName() == owner) {
                        property->setOwner(player);
                        player->addProperty(property->getPosn(), property->getName());
                        break;
                    }
                }
            } else property->setOwner(nullptr);

            if (improvements > 0) {
                AcademicBldg* ab = dynamic_cast<AcademicBldg*>(property);
                if (ab) {
                    ab->setImprovements(improvements);  // Call setImprovements if successful cast
                }
            }
        break;
        }

    }
    // Notify observers to draw the initial board
    board.notifyObservers();
}


bool GamePlay::checkGameOver() {
    return board.getPlayers().size() == 1;
}

void GamePlay::handlePlayerBankruptcy(shared_ptr<Player> player, shared_ptr<Player> creditor) {
    // Handle player bankruptcy
    // ...
}

void GamePlay::processCommand(const string& cmd) {
    istringstream cmdLine(cmd);
    string command;
    cmdLine >> command;
    
    if (command == "roll") {
        if(!board.getPlayers()[board.getCurrentPlayerIndex()]->getTurnOver()) {
            if (testingMode) {
                int die1, die2;
                if (cmdLine >> die1 >> die2) {
                    rollCommand(die1, die2);
                } else {
                    rollCommand();
                }
            } else {
                rollCommand();
            }
        } else {
            cout << "You have already rolled this turn." << endl;
        }
    } else if (command == "next") {
        if (board.getPlayers()[board.getCurrentPlayerIndex()]->getTurnOver()) { 
            nextCommand();
        } else {
            cout << board.getPlayers()[board.getCurrentPlayerIndex()]->getName() << "'s turn is not over yet. Player must roll to complete their turn." << endl;
        }
    } else if (command == "trade") {
        tradeCommand(cmdLine);
    } else if (command == "improve") {
        improveCommand(cmdLine);
    } else if (command == "mortgage") {
        mortgageCommand(cmdLine);
    } else if (command == "unmortgage") {
        unmortgageCommand(cmdLine);
    } else if (command == "bankrupt") {
        bankruptCommand();
    } else if (command == "assets") {
        shared_ptr<Player> currentPlayer = board.getPlayers()[board.getCurrentPlayerIndex()];
        assetsCommand(currentPlayer);
    } else if (command == "all") {
        allCommand();
    } else if (command == "save") {
        saveCommand(cmdLine);
    } else if (command == "quit") {
        gameOver = true;
    } else {
        cout << "Unknown command: " << command << endl;
    }
    
}

void GamePlay::doubles(shared_ptr<Player> currentPlayer){
    // If doubles were rolled, player gets another turn unless it's their third doubles or if they just got into the tims line
    if (currentPlayer->getDoublesTurns() != 2) {
        cout << "Doubles! " << currentPlayer->getName();
        //if player is not in tims line, then they get another turn
        if (!currentPlayer->getInTimsLine()) {
            cout << " gets another turn." << endl;
            currentPlayer->setDoublesTurns(currentPlayer->getDoublesTurns()+1);
        //if they didn't just get into the tims line, then they can get out
        } else if (currentPlayer->getTimsTurns() != 1) {
            cout <<  " got out of Tims Line" << endl;
            currentPlayer->setInTimsLine(false);
            currentPlayer->setDoublesTurns(0);
            currentPlayer->setTimsTurns(0);
        }
    //if third doubles, they go in tims line
    } else {
        board.movePlayer(currentPlayer, 10 , true);
        //board.notifyObservers();
        cout << "Third doubles! " << currentPlayer->getName() << " is now at DC Tims Line." << endl;
        cout << currentPlayer->getName() << " cannot roll again this turn. " << endl;
        currentPlayer->setInTimsLine(true);
        //currentPlayer->setTimsTurns(1);
        currentPlayer->setTurnOver(true);
    }
}


void GamePlay::rollCommand(int die1, int die2) {
    shared_ptr<Player> currentPlayer = board.getPlayers()[board.getCurrentPlayerIndex()];
    //currentPlayer->setDoublesTurns(currentPlayer->getDoublesTurns() + 1);
    
    // Get dice values
    int dieValue1 = (die1 == -1) ? dice[0].rollDice() : die1;
    int dieValue2 = (die2 == -1) ? dice[1].rollDice() : die2;
    int total = dieValue1 + dieValue2;
    
    cout << currentPlayer->getName() << " rolled " << dieValue1 << " and " << dieValue2 << " for a total of " << total << endl;
    
    // Move player and handle square action
    int newPosition = (currentPlayer->getPosition() + total) % 40;
    
    // Check if passing OSAP
    if (newPosition < currentPlayer->getPosition()) {
        cout << currentPlayer->getName() << " passes OSAP and collects $200" << endl;
        currentPlayer->addMoney(200, 200);
    }

    //If player is in Tims Line, they cannot move. 
    board.movePlayer(currentPlayer, newPosition);
    board.notifyObservers();

    // cout << "currentPlayer->getTimsTurns(): " << currentPlayer->getTimsTurns() << endl;
    // cout << "currentPlayer->getDoublesTurns(): " << currentPlayer->getDoublesTurns() << endl;

    if (dieValue1 == dieValue2 && currentPlayer->getTimsTurns() != 1) {
        doubles(currentPlayer);
    } else {
        //if not doubles and they are in tims line they have tho option to try and get out.
        if (currentPlayer->getInTimsLine() && currentPlayer->getTimsTurns() != 1) { 
            board.timsLineOptions(); 
        }
        //if not in tims line, turn is immediately over.
        currentPlayer->setDoublesTurns(0);
        currentPlayer->setTurnOver(true);
    }
}

void GamePlay::nextCommand() {
    shared_ptr<Player> currentPlayer = board.getPlayers()[board.getCurrentPlayerIndex()];
    cout << currentPlayer->getName() << "'s turn is over." << endl;
    currentPlayer->setTurnOver(false);
    //currentPlayer.setDoublesTurns(0);
    board.nextTurn();
    //board.notifyObservers();
}

void GamePlay::tradeCommand(istringstream& cmdLine) {
    Player* currentPlayer = board.getPlayers()[board.getCurrentPlayerIndex()].get();
    string name, giveItem, receiveItem;
    int giveMoney = -1, receiveMoney = -1;

    // Read the name of the player to trade with
    if (!(cmdLine >> name)) {
        cout << "Error: Missing player name in trade command." << endl;
        return;
    }

    // Find the player by name
    shared_ptr<Player> otherPlayer = nullptr;
    int nameIndex = -1;

    for (int i = 0; i < board.getNumPlayers(); i++) {
        if (board.getPlayers()[i]->getName() == name) { 
            otherPlayer = board.getPlayers()[i];
            nameIndex = i;
            break;
        }
    }

    if (!otherPlayer) { 
        cout << "Error: Player '" << name << "' does not exist." << endl;
        return;
    }

    string nextToken;
    if (!(cmdLine >> nextToken)) {
        cout << "Error: Trade command is incomplete." << endl;
        return;
    }

    int item1Index = 0; // Extracts the int value
    int item2Index = 0; // Extracts the int value

    int item1Value = 0;
    int item2Value = 0;

    // Determine if first value is money or item
    if (isdigit(nextToken[0])) {
        giveMoney = stoi(nextToken);
        item1Value = giveMoney;
    } else {
        giveItem = nextToken;
        item1Index = currentPlayer->getProperties()[giveItem];
        Property* property1 = dynamic_cast<Property*>(board.getGameBoard()[item1Index]);  
        if (property1) { 
            item1Value = property1->getCost(); 
        } else {
            cout << "Property not found. Try again. " << endl;
            return;
        }

    }

    // Check what the player is receiving
    if (cmdLine >> nextToken) {
        if (isdigit(nextToken[0])) {
            receiveMoney = stoi(nextToken);
            item2Value = receiveMoney;
        } else {
            receiveItem = nextToken;
            auto it = otherPlayer->getProperties().find(receiveItem);
            if (it != otherPlayer->getProperties().end()){
                item2Index = it->second;
            } else {
                cout << "Property not found. Try again. " << endl;
                return;
            }
            Property* property2 = dynamic_cast<Property*>(board.getGameBoard()[item2Index]);  
            if (property2) { 
                item2Value = property2->getCost(); 
            } else {
                cout << "Property not found. Try again. " << endl;
                return;
            }
        }
    } else {
        cout << "Error: Trade command is incomplete. Missing receive item or money." << endl;
        return;
    }

    // Process trade logic
    if (giveMoney != -1) {  // Giving money
        Property* property2 = dynamic_cast<Property*>(board.getGameBoard()[item2Index]);  
        if (property2->hasImprovements()) {
            cout << "Error: " << otherPlayer->getName() << " cannot trade " << receiveItem << " because it has improvements." << endl;
            return;
        }
        if (receiveMoney != -1) {
            cout << "Error: Players cannot trade money for money." << endl;
            return;
        } 
        if (!otherPlayer->ownsProperty(receiveItem)) {
            cout << "Error: Player '" << name << "' does not own item '" << receiveItem << "'." << endl;
            return;
        }
        tradeItem(nameIndex, giveMoney, receiveItem, item2Index, item2Value);
    } else {  // Giving item
        if (!currentPlayer->ownsProperty(giveItem)) {
            cout << "Error: Player '" << currentPlayer->getName() << "' does not own item '" << giveItem << "'." << endl;
            return;
        }

        if (receiveMoney != -1) {
            Property* property1 = dynamic_cast<Property*>(board.getGameBoard()[item1Index]);  
            if (property1->hasImprovements()) {
                cout << "Error: " << currentPlayer->getName() << " cannot trade " << giveItem << " because it has improvements." << endl;
                return;
            }
            tradeItem(nameIndex, giveItem, receiveMoney, item1Index, item1Value);
        } else if (otherPlayer->ownsProperty(receiveItem)) {
            Property* property1 = dynamic_cast<Property*>(board.getGameBoard()[item1Index]);  
            Property* property2 = dynamic_cast<Property*>(board.getGameBoard()[item2Index]);  
            if (property1->hasImprovements()) {
                cout << "Error: " << currentPlayer->getName() << " cannot trade " << giveItem << " because it has improvements." << endl;
                return;
            } else if (property2->hasImprovements()) {
                cout << "Error: " << otherPlayer->getName() << " cannot trade " << receiveItem << " because it has improvements." << endl;
                return;
            }
            tradeItem(nameIndex, giveItem, receiveItem, item1Index, item2Index, item1Value, item2Value);
        } else {
            cout << "Error: Player '" << name << "' does not own item '" << receiveItem << "'." << endl;
        }
    }
}


void GamePlay::tradeItem(int nameIndex, string item1, string item2, int item1Index, int item2Index, int item1Value, int item2Value) {
    Property* property1 = dynamic_cast<Property*>(board.getGameBoard()[item1Index]);
    Property* property2 = dynamic_cast<Property*>(board.getGameBoard()[item2Index]);  
    shared_ptr<Player> currentPlayer = board.getPlayers()[board.getCurrentPlayerIndex()];
    shared_ptr<Player> otherPlayer = board.getPlayers()[nameIndex];

    cout << currentPlayer->getName() << " would like to trade " << item1 << " for " << item2 << " with " << otherPlayer->getName() << "." << endl;
    string choice;

    while (choice != "1" && choice != "2" && choice != "accept" && choice != "reject") {
        cout << "(1) 'accept' or (2) 'reject' trade?" << endl;
        cin >> choice;
        cin.ignore();
    }

    if (choice == "1" || choice == "accept") {
        //need to change to networth of the players.
        currentPlayer->removeProperty(item1);
        otherPlayer->addProperty(item1Index, item1);
        currentPlayer->addProperty(item2Index, item2);
        otherPlayer->removeProperty(item2);
        currentPlayer->addMoney(0, item2Value - item1Value);
        otherPlayer->addMoney(0, item1Value - item2Value);
        property1->setOwner(otherPlayer);
        property2->setOwner(currentPlayer);
    } else {
        cout << "Trade rejected. Owners remain the same. " << endl;
    }
}

void GamePlay::tradeItem(int nameIndex, string item, int money, int itemIndex, int itemValue) {
    Property* property = dynamic_cast<Property*>(board.getGameBoard()[itemIndex]);  
    shared_ptr<Player> currentPlayer = board.getPlayers()[board.getCurrentPlayerIndex()];
    shared_ptr<Player> otherPlayer = board.getPlayers()[nameIndex];

    cout << currentPlayer->getName() << " would like to trade " << item << " for $" << money << " with " << otherPlayer->getName() << "." << endl;
    string choice;

    while (choice != "1" && choice != "2" && choice != "accept" && choice != "reject") {
        cout << "(1) 'accept' or (2) 'reject' trade?" << endl;
        cin >> choice;
        cin.ignore();
    }

    if (choice == "1" || choice == "accept") {
        //int itemIndex = currentPlayer->getProperties().at(item); // Extracts the int value
        //int itemValue = board.getGameBoard()[itemIndex]->getCost();
        //need to change to networth of the players.
        currentPlayer->removeProperty(item);
        otherPlayer->addProperty(itemIndex, item);
        currentPlayer->addMoney(money, money - itemValue);
        otherPlayer->addMoney(-money, itemValue - money);
        property->setOwner(otherPlayer);
    } else {
        cout << "Trade rejected. " << currentPlayer->getName() << " still owns the property. " << endl;
    }
}

void GamePlay::tradeItem(int nameIndex, int money, string item, int itemIndex, int itemValue) {
    Property* property = dynamic_cast<Property*>(board.getGameBoard()[itemIndex]);  
    shared_ptr<Player> currentPlayer = board.getPlayers()[board.getCurrentPlayerIndex()];
    shared_ptr<Player> otherPlayer = board.getPlayers()[nameIndex];

    cout << currentPlayer->getName() << " would like to trade $" << money << " for " << item << " with " << otherPlayer->getName() << "." << endl;
    string choice;

    while (choice != "1" && choice != "2" && choice != "accept" && choice != "reject") {
        cout << "(1) 'accept' or (2) 'reject' trade?" << endl;
        cin >> choice;
        cin.ignore();
    }

    if (choice == "1" || choice == "accept") {
        //int itemIndex = currentPlayer->getProperties().at(item); // Extracts the int value
        //int itemValue = board.getGameBoard()[itemIndex]->getCost();
        //need to change to networth of the players.
        currentPlayer->addProperty(itemIndex, item);
        otherPlayer->removeProperty(item);
        currentPlayer->addMoney(-money, itemValue - money);
        otherPlayer->addMoney(money, money - itemValue);
        property->setOwner(currentPlayer);
    } else {
        cout << "Trade rejected. " << otherPlayer->getName() << " still owns the property. " << endl;
    }
}

void GamePlay::improveCommand(istringstream& cmdLine) {
    string property;
    cmdLine >> property;

    string buyOrSell;
    cmdLine >> buyOrSell;

    shared_ptr<Player> currentPlayer = board.getPlayers()[board.getCurrentPlayerIndex()];

    //can only improve properties that you own
    if (currentPlayer->getProperties()[property]) {
        Square& square = *board.getGameBoard()[currentPlayer->getProperties()[property]];
        AcademicBldg* academicBuildingSquare = dynamic_cast<AcademicBldg*>(&square);
        Property* currentProperty = dynamic_cast<Property*>(&square); 

        if(!currentProperty->hasMonopoly()) {
            cout << "You cannot improve " << property << " because you do not have a monopoly." << endl;
            return;
        }
        if (academicBuildingSquare && currentProperty->hasMonopoly()) { //can only improve AcademicBldg and only when it is a monopoly. 
            int improvements = academicBuildingSquare->getImprovements();
            int improvementCost = AcademicBldg::Costs.at(property)[1];
            if (buyOrSell == "buy") {
                if (improvements == 5) {
                    cout << academicBuildingSquare->getName() << " already has the maximum number of improvements (5). " << endl;
                } else if (currentPlayer->getMoney() < improvementCost) {
                    cout << currentPlayer->getName() << " does not have enough money to purchase an improvement. " << endl;
                    cout << currentPlayer->getName() << ": $" << currentPlayer->getMoney() << endl;
                    cout << academicBuildingSquare->getName() << ": $" << improvementCost << endl;
                } else{
                    academicBuildingSquare->setImprovements(improvements + 1);
                    cout << currentPlayer->getName() << " paid $" << improvementCost << " to improve " << academicBuildingSquare->getName() << endl;
                    currentPlayer->addMoney(-improvementCost, 0);
                    board.notifyObservers();
                }
            } else if (buyOrSell == "sell") {
                if (improvements == 0) {
                    cout << academicBuildingSquare->getName() << " currently has no improvements " << endl;
                } else {
                    academicBuildingSquare->setImprovements(improvements - 1);
                    cout << currentPlayer->getName() << " gained $" << improvementCost << " by removing the improvement on " << academicBuildingSquare->getName() << endl;
                    currentPlayer->addMoney(improvementCost, 0);
                    board.notifyObservers();
                }
            } else {
                cout << "buy or sell was not correctly specified." << endl;
            }
        }
    } else {
        cout << currentPlayer->getName() << " does not own " << property << endl;
    }
}

void GamePlay::mortgageCommand(istringstream& cmdLine) {
    shared_ptr<Player> currentPlayer = board.getPlayers()[board.getCurrentPlayerIndex()];
    string p;

    if (cmdLine >> p) {  
        auto property = board.getProperty(p); // retrieves property from board by name

        if (!property) {
            cout << "Property " << p << " not found, please re-enter." << endl;
            return;
        } else if (property->isMortgaged()) {
            cout << p << " is already mortgaged, cannot mortgage this property." << endl;
            return;
        } else if (property->getOwner().get() != currentPlayer.get()) { 
            cout << currentPlayer->getName()  << " does not own "  << p << ", player must own property to mortgage." << endl;
            return;
        } else if (property->hasImprovements()) {
            cout << p << " must have zero improvements before mortgaging, could not mortgage." << endl;
            return;
        } else {
            property->setMortgaged(true); // set property to mortgaged
            int cost = property->getCost(); // retrieve property cost
            currentPlayer->addMoney(cost/2, cost/2); // player recives half the cost
            cout << "Property "  << p << " has been mortgaged. " << currentPlayer->getName() << " has gained $" << cost/2 << endl;
        }
    } else {
        cout << "Usage: mortgage <property>" << endl;
    }
}

void GamePlay::unmortgageCommand(istringstream& cmdLine) {
    shared_ptr<Player> currentPlayer = board.getPlayers()[board.getCurrentPlayerIndex()];
    string p;

    if (cmdLine >> p) {  
        auto property = board.getProperty(p); // retrieves property from board by name

        if (!property) {
            cout << "Property " << p << " not found, please re-enter." << endl;
            return;
        } else if (!property->isMortgaged()) {
            cout << p << " is not already mortgaged, cannot unmortgage this property." << endl;
            return;
        } else if (property->getOwner().get() != currentPlayer.get()) { 
            cout << currentPlayer->getName()  << " does not own "  << p << ", player must own property to unmortgage." << endl;
            return;
        } else {
            int fee = property->getCost() * 0.6; // retrieve property cost

            if (currentPlayer->getMoney() < fee) {
                cout << currentPlayer->getName()  << " does not have enough money to unmortgage." << endl;
                return;    
            }
            property->setMortgaged(false); // set property to unmortgaged
            currentPlayer->addMoney(-fee, -fee); // player recives half the cost
            cout << "Property "  << p << " has been unmortgaged. " << currentPlayer->getName() << " has paid $" << fee << "." << endl;

        }
    } else {
        cout << "Usage: unmortgage <property>" << endl;
    }
}

void GamePlay::bankruptCommand() {
    shared_ptr<Player> currentPlayer = board.getPlayers()[board.getCurrentPlayerIndex()];
    handlePlayerBankruptcy(currentPlayer);
}

void GamePlay::assetsCommand(shared_ptr<Player> currentPlayer) {
    // Display player assets
    // ...
    cout << "Player " << currentPlayer->getName() << " - ";
    cout << "Cash: $" << currentPlayer->getMoney() << endl;
    cout << "       Net Worth: $" << currentPlayer->getNetWorth() << endl;
    cout << "       Properties: " << endl;
    for (auto& currentProperty : currentPlayer->getProperties()) {
        //Property* propertyBuildingSquare = dynamic_cast<Property*>(board.getGameBoard()[currentPlayer->getPosition()]);
        AcademicBldg* academicBuildingSquare = dynamic_cast<AcademicBldg*>(board.getGameBoard()[currentProperty.second]);
        if(academicBuildingSquare) {
            cout << "       " << currentProperty.first << " (" << academicBuildingSquare->getImprovements() << "  improvements)" << endl;
        } else {
            cout << "       " << currentProperty.first << endl;
        }
    }
}

void GamePlay::allCommand() {
    for (auto& player : board.getPlayers()) {
        assetsCommand(player);
    }
}

string GamePlay::printProperty(Property& property) {
    string line;
    line = property.getName();

    string owner;

    int improvements = 0;
    if (auto academicbldg = dynamic_cast<AcademicBldg*>(&property)) {
        improvements = academicbldg->getImprovements();
    }
    if (property.getOwner() == nullptr) {
        owner = "BANK"; 
    } else owner = property.getOwner()->getName();

    line += " " + owner + " " + to_string(improvements);
    return line;
}

void GamePlay::saveCommand(istringstream& cmdLine) {
    string filename;
    cmdLine >> filename;
    std::ofstream file(filename); // Open a file for writing
    string line;
    if (!file) {
        std::cerr << "Error opening file!" << std::endl;
    } else {
        file << board.getNumPlayers() << std::endl; // Write to the file
        for (auto& player : board.getPlayers()) {
            line  = player->print();
            file << line << endl;
        }

        for (auto& square : board.getGameBoard()) {
            auto propertyBuildingSquare = dynamic_cast<Property*>(square);
            if (propertyBuildingSquare) {
                file << printProperty(*propertyBuildingSquare) << endl;
            }
        }
        }
        file.close(); // Close the file
        std::cout << "The current state of the game has been saved to " << filename << "."<< std::endl;
}

std::map <char, string> GamePlay::pieces {
    {'G', "Goose"},
    {'B', "GRT Bus"},
    {'D', "Tim Hortons Doughnut"},
    {'P', "Professor"},
    {'S', "Student"},
    {'$', "Money"},
    {'L', "Laptop"},
    {'T', "Pink Tie"}
};
