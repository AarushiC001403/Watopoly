export module observer;
import <string>;

export class ObservableEntity {
  public:
    virtual ~ObservableEntity() = default;
};


export class Observer {
  public:
    // Pass in the Subject that called the notify method.
    virtual void notify( ObservableEntity* whoNotified ) = 0; 
    //virtual std::string getName() = 0;

    virtual ~Observer() = default;
};
