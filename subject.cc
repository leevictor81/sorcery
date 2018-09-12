#include <iostream>
#include <vector>
#include "subject.h"
#include "observer.h"

using namespace std;

Subject::Subject(): observers{}, window{nullptr}{}

Subject::~Subject(){
  for(unsigned int i = 0; i < this->observers.size(); i++){
    observers.pop_back();
  }
}

void Subject::attach(Observer *o) {
  this->observers.push_back(o);
}

void Subject::attach_to_front(Observer *o) {//added this method
  vector<Observer*> newObservers;
  newObservers.push_back(o);
  int oldsize = this->observers.size();
  for (int i = 0; i < oldsize; i++) {
    newObservers.push_back(this->observers[i]);
  }
  this->observers = newObservers;
}

void Subject::attach_window(Observer *o) {
  this->window = o;
}

void Subject::remove(int index) {//added this method
  this->observers.erase(observers.begin() + index);
}

void Subject::notifyObservers(TriggerType t, Owner* me, Owner* opponent, string &event) {
  int size = this->observers.size();
  if (t == TriggerType::Xwindow && this->window != nullptr) {
    this->window->notify(me, opponent, event);
  }
  for ( int i = size-1; i >= 0; i--) {
    if(this->observers[i]->getTriggerType() == t || ((t == TriggerType::YouDestroy || t == TriggerType::OpponentDestroy)  && this->observers[i]->getTriggerType() == TriggerType::AnyDestroy)){
      this->observers[i]->notify(me, opponent, event);
    }
  }
}

void Subject::notifyObservers(TriggerType t, Owner* me, Owner* opponent, int fieldIndex, int whoSummon) {
  int size = this->observers.size();
  if (t == TriggerType::YouSummon) {
    for (int i = size - 1; i >= 0; i--) {
      if (this->observers[i]->getTriggerType() == t || this->observers[i]->getTriggerType() == TriggerType::AnySummon) {
        this->observers[i]->notify(me, opponent, fieldIndex, whoSummon);
      }
    }
  } else if (t == TriggerType::OpponentSummon) {
    for (int i = size - 1; i >= 0; i--) {
      if (this->observers[i]->getTriggerType() == t || this->observers[i]->getTriggerType() == TriggerType::AnySummon) {
        this->observers[i]->notify(me, opponent, fieldIndex, whoSummon);
      }
    }
  }
}

void Subject::swapObserver(int fieldIndex, Observer* o) {
  this->observers[fieldIndex] = o;
}

