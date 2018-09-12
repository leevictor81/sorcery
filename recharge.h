#ifndef _RECHARGE_H_
#define _RECHARGE_H_
#include <string>
#include "effect.h"

class Recharge : public Effect {
  int charges;
public:
  Recharge(int charges);
  ~Recharge();
  Recharge* copyCtor() const override;
  int getCharges() const;
  void activate(Owner *me, Owner *opponent) override;
  void activate(int fieldIndex, Owner *player) override;
};

#endif

