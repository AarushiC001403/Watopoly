export module gameplay;
import <iostream>;
import <string>;
import <sstream>;
import <vector>;
import <map>;
import <memory>;
import <unordered_set>;
//import <random>;
import <fstream>;

import board;
import player;
import property;
import dice;
import textdisplay;
import square;
import academicbuilding;
import gym;
import residence;
import nonproperty;
import tuition;
import needleshall;
import slc;

using namespace std;

export class GamePlay {
    private:
        Board board;
        TextDisplay* display;
        std::vector<Dice> dice;
        bool gameOver;
        bool testingMode;
        static std::map<char, string> pieces;

        // Game logic helpers
        //void loadGame(const string& filename);
        void saveGame(const string& filename);
        bool checkGameOver();
        void handlePlayerBankruptcy(shared_ptr<Player> player, shared_ptr<Player> creditor = nullptr);
        
        // Command interpreter methods
        void processCommand(const string& cmd);
        void rollCommand(int die1 = -1, int die2 = -1); // -1 means random roll
        void nextCommand();
        void tradeCommand(istringstream& cmdLine);
        void tradeItem(int nameIndex, string item1, string item2, int item1Index, int item2Index, int item1Value, int item2Value);
        void tradeItem(int nameIndex, string item, int money, int itemIndex, int itemValue);
        void tradeItem(int nameIndex, int money, string item, int itemIndex, int itemValue);
        void improveCommand(istringstream& cmdLine);
        void mortgageCommand(istringstream& cmdLine);
        void unmortgageCommand(istringstream& cmdLine);
        void bankruptCommand();
        void assetsCommand( shared_ptr<Player> currentPlayer);
        void allCommand();
        string printProperty(Property& square);
        void saveCommand(std::istringstream& cmdLine);
        //void buyCommand();
        void doubles( shared_ptr<Player> currentPlayer);
        void timsLineOptions();
            
    public:
        GamePlay(bool testing = false);
        ~GamePlay();
        void initializeGame();
        void initializeWithPlayers(const vector<shared_ptr<Player>>& players);
        //void loadBoard(const std::vector<Player>& players, const std::vector<Property>& properties);
        void loadBoard(const string& filename);
        void start();
        //void loadFromFile(const string& filename);
};
