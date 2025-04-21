export module tuition;
import <iostream>;
import <random>;
import <string>;
import <memory>;
import player;
import nonproperty;

export class Tuition : public NonProperty {
    public:
    Tuition(int posn, std::string name);
    int action(std::shared_ptr<Player> p);
};
