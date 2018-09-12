#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>
#include <string>
#include "triggerType.h"

class Observer;

class Owner;

class Subject {
  std::vector<Observer*> observers;
  Observer* window;
 public:
  Subject();
  void attach(Observer *o);
  void attach_window(Observer *o);
  void attach_to_front(Observer *o);//added
  void remove(int index);//added
  void notifyObservers(TriggerType t, Owner* me, Owner* opponent, std::string &event);
  void notifyObservers(TriggerType t, Owner* me, Owner* opponent, int fieldIndex, int whoSummon);
  void swapObserver(int fieldIndex, Observer *o);
  virtual ~Subject();
};

#endif

