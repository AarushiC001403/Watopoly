export module textdisplay;
import <iostream>;
import <string>;
import <sstream>;
import <vector>;
//import <iomanip>;
import observer;
import square;
import board;
import subject;
import property;
import academicbuilding;

export class TextDisplay : public Observer { //concrete observer
    Board* board;
    
    // Helper methods to format different parts of the board
    void displayTopRow();
    void displayMiddleRows();
    void displayBottomRow();
    
  public:
    TextDisplay(Board* b);
    void notify(ObservableEntity* whoFrom) override;
    void printCard(int propertyNumber, int row);
};
