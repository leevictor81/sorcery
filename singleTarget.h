#ifndef _SINGLE_TARGET_H_
#define _SINGLE_TARGET_H_
#include <string>
#include "effect.h"

class SingleTarget : public Effect {
  int attackChange;
  int defenseChange;
public:
  SingleTarget(int attackChange, int defenseChange);
  ~SingleTarget();
  SingleTarget* copyCtor() const override;
  int getAttackChange() const;
  int getDefenseChange() const;
  void activate(Owner *me, Owner *opponent) override;
  void activate(int fieldIndex, Owner *player) override;
};

#endif

