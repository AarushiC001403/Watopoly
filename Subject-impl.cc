module subject;
import <algorithm>;

Subject::Subject() {}

Subject::~Subject() {}

void Subject::attach(Observer* o) {
    observers.emplace_back(o);
}

void Subject::detach(Observer* o) {
    observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end());
}

void Subject::notifyObservers() {
    for (auto it = observers.begin(); it != observers.end(); ++it) {
        (*it)->notify(this);
    }
}
