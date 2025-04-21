export module subject;
import <vector>;
import <algorithm>;
import observer;

export class Subject : public ObservableEntity {
    std::vector<Observer*> observers;
  
  public:
    Subject();
    void attach(Observer* o);
    void detach(Observer* o);
    void notifyObservers();
    virtual ~Subject(); //=default
};
