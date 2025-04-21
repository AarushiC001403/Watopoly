export module needleshall;
import <iostream>;
import <random>;
import <string>;
import <memory>;
import player;
import nonproperty;

export class NH : public NonProperty {
    public:
    NH(int posn, std::string name);
    bool rimCupChance();
    int action(std::shared_ptr<Player> p);
};
