#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include <string>
#include "triggerType.h"
class Subject;
class Owner;

class Observer {
 public:
  virtual void notify(Owner* me, Owner* opponent, std::string &event) = 0;
  virtual void notify(Owner* me, Owner* opponent, int fieldIndex, int whoSummon) = 0;
  virtual TriggerType getTriggerType() const = 0;
  virtual ~Observer() = default;
};
#endif

