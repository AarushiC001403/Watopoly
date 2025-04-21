import board;
import player;
import property;
import textdisplay;
import gameplay;
import academicbuilding;

import <iostream>;
import <fstream>;
import <sstream>;
import <vector>;
import <string>;

using namespace std;


int main(int argc, char* argv[]) {
    std::cout << "Welcome to Monopoly!" << std::endl;

    bool testingMode = false;
    string loadFile;

    if (argc > 1) {
        // Process the command line arguments
        for (int i = 1; i < argc; ++i) {
            if (string(argv[i]) == "-load" && i + 1 < argc) {
                loadFile = argv[i + 1];
            }
            if (string(argv[i]) == "-testing") {
                testingMode = true;
            }
        }
    }
    
    // Initialize the game
    GamePlay game(testingMode);

    if (!loadFile.empty()) {
        // Load the game from the file
        game.loadBoard(loadFile);
    } else {
        // Start a new game
        game.initializeGame();
    }
    
    // Start the game
    game.start();
    
    return 0;
}
