module textdisplay;
using namespace std;

TextDisplay::TextDisplay(Board* b) : board(b) {
    // Attach to the board
    board->attach(this);
}

void TextDisplay::notify(ObservableEntity* whoFrom) {
    // Redraw the entire board
    displayTopRow();
    displayMiddleRows();
    displayBottomRow();
}

void TextDisplay::displayTopRow() {
    // Display the top row of the board with current state
    cout << "_________________________________________________________________________________________ " << endl;
    for (int j = 1; j <= 5; j++) {
        for (int i = 20; i <= 30; i++) {
            cout << "|";
            printCard(i, j);
        }
        cout << "|" << endl;
    }
}

void TextDisplay::displayMiddleRows() {
    // Left side (19 down to 11)
    int diff = 31-19;
    int row = 0;

    for (int i = 19; i >= 11; i--) {
        for (int j = 1; j <= 5; j++) {
            cout << "|";
            printCard(i, j);
            if (row == 44) {
                cout << "|-----------------------------------------------------------------------|";
            } else if ((row <= 17) || (row > 25)) {
                cout << "|                                                                       |";
            } else if (row == 18) {
                cout << "|             _____________________________________________             |";
            } else if (row == 19) {
                cout << "|            |                                             |            |";
            } else if (row == 20) {
                cout << "|            | #   #  ##  #####  ###  ###   ###  #   #   # |            |";
            } else if (row == 21) {
                cout << "|            | #   # #  #   #   #   # #  # #   # #   #   # |            |";
            } else if (row == 22) {
                cout << "|            | # # # ####   #   #   # ###  #   # #    # #  |            |";
            } else if (row == 23) {
                cout << "|            | # # # #  #   #   #   # #    #   # #     #   |            |";
            } else if (row == 24) {
                cout << "|            | ##### #  #   #    ###  #     ###  ## #  #   |            |";
            } else if (row == 25) {
                cout << "|            |_____________________________________________|            |";
            }
            row++;
            printCard(i+diff, j);
            cout << "|" << endl;   
        }
        diff += 2;
    }
}

void TextDisplay::displayBottomRow() {
    // Display the bottom row of the board
    for (int j = 1; j <= 5; j++) {
        for (int i = 10; i >= 0; i--) {
            cout << "|";
            printCard(i, j);
        }
        cout << "|" << endl;
    }
    
}

void TextDisplay::printCard(int propertyNumber, int row) {
    Square* square = board->getGameBoard()[propertyNumber];
    if (typeid(*square) == typeid(AcademicBldg)) {
        AcademicBldg* academicBuilding = dynamic_cast<AcademicBldg*>(square);
        if (row == 1) { 
            int improvements = academicBuilding->getImprovements();

            for (int i = 0; i < improvements; i++) {
                cout << "I";
            } 
            for (int i = improvements; i < 7; i++) {
                cout << " ";
            }
        }
        if (row == 2) { 
            cout <<"-------";
        }
        if (row == 3) { 
            cout << academicBuilding->getName(); 
            for (int i = academicBuilding->getName().length(); i < 7; i++) {
                cout << " ";
            }
        }
    } else {
        std::stringstream ss(square->getName());
        std::string word;
        std::vector<std::string> words;

        while (ss >> word) {
            words.push_back(word);
        }

        if (row == 1) { 
            cout << words[0];
            int len = words[0].length();
            if (words.size() == 3) {
                cout << " " << words[1];
                len += words[1].length() + 1;
            }
            
            for (int i = len; i < 7; ++i) {
                cout << " ";
            }
        }
        if (row == 2) { 
            int len = 0;
            if (words.size() == 2) {
                cout << words[1];
                len = words[1].length();
            }

            if (words.size() == 3) {
                cout << words[2];
                len = words[2].length();
            }
            for (int i = len; i < 7; ++i) {
                cout << " ";
            }
        }
        if (row == 3) { 
            for (int i = 0; i < 7; ++i) {
                cout << " ";
            }
        }
    }

    if (row == 4) {
        int count = 0;
        for (int i = 0; i < board->getNumPlayers(); i++) {
            if (board->getPlayers()[i]->getPosition() == propertyNumber) {
                cout << board->getPlayers()[i]->getChar();
                count++;
            }
        }
        for(int i = count; i < 7; i++) {
            cout << " ";
        }
    }

    if (row == 5) {
        cout << "_______";
    }
}
