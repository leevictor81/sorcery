#ifndef _STANDSTILL_H_
#define _STANDSTILL_H_
#include <string>
#include "effect.h"

class Standstill : public Effect {
public:
  Standstill();
  ~Standstill();
  Standstill* copyCtor() const override;
  void activate(Owner *me, Owner *opponent) override;
  void activate(int fieldIndex, Owner *player) override;
};

#endif

