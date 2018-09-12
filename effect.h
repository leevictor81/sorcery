#ifndef _EFFECT_H_
#define _EFFECT_H_
#include <string>

class Owner;

//abstract class
class Effect {
public:
  Effect();
  virtual ~Effect();
  virtual Effect* copyCtor() const = 0;
  virtual void activate(Owner* me, Owner* opponent) = 0;
  virtual void activate(int fieldIndex, Owner* player) = 0;
};

#endif

