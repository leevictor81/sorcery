#ifndef _AOE_H_
#define _AOE_H_
#include <string>
#include "effect.h"

class Aoe : public Effect {
  int attackChange;
  int defenseChange;
  int targets;
public:
  Aoe(int attackChange, int defenseChange, int targets);
  ~Aoe();
  Aoe* copyCtor() const override;
  int getAttackChange() const;
  int getDefenseChange() const;
  int getTargets() const;
  void activate(Owner *me, Owner *opponent) override;
  void activate(int fieldIndex, Owner *player) override;
};

#endif


