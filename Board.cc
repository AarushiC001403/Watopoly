export module board;

import <vector>;
//import <iostream>;
import <map>;
import <string>;
import <memory>;
import <unordered_set>;
import <sstream>;

import square;
import property;
import player;
import nonproperty;
import residence;
import gym;
import academicbuilding;
import subject;
import needleshall;
import slc;
import tuition;

using namespace std;

// this is also a subject for the textobserver (text gameboard display)

export class Board : public Subject { //concrete subject
    private:
    int numPlayers; // this is atleast 1, when 1 player remains player is winner
    int currentPlayerIndex; // index of current player in Players vector
    
    public:
    std::vector<std::shared_ptr<Player>> Players ;   // vector of players in the game. has to be public for loadgame
    std::vector<Square*> GameBoard; // vector of 40 squares. has to be public for loadgame
    Board();
    ~Board();
    void init(); // initializes the board
    void buy(int playerIndex, int posn);
    void payFee(int player1Index, int player2Index,int posn);
    void auctionProperty(Property* property);
    void addPlayer(std::shared_ptr<Player> p);
    void bankruptPlayer(std::shared_ptr<Player> p, std::shared_ptr<Player> creditor);
    void bankruptBank(std::shared_ptr<Player> p);
    void movePlayer(std::shared_ptr<Player> p, int posn, bool inTims = false); // moves player p on board to posn
    void timsLineOptions();
    //Add methods for game state changes that should notify the observer
    void nextTurn(); // moves to next player's turn
    int totalRimCups = 0; // total number of rim cups in the game
    vector<Square*>& getGameBoard();
    vector<shared_ptr<Player>>& getPlayers();
    Property* getProperty(string propertyName);
    int getCurrentPlayerIndex();
    int getNumPlayers();
};
