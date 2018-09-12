#ifndef BANISH_H
#define BANISH_H
#include <string>
#include "effect.h"

class Banish : public Effect {
public:
  Banish();
  ~Banish();
  Banish* copyCtor() const override;
  void activate(Owner *me, Owner *opponent) override;
  void activate(int fieldIndex, Owner *player) override;
};

#endif

