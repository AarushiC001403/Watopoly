export module slc;
import <iostream>;
import <random>;
import <string>;
import <memory>;
import player;
import nonproperty;

export class SLC : public NonProperty {
    public:
    SLC(int posn, std::string name);
    bool rimCupChance();
    int action(std::shared_ptr<Player> p, int &totalRimCups);
};
