#ifndef _SUMMON_H_
#define _SUMMON_H_
#include <string>
#include "effect.h"

class Summon : public Effect {
  std::string monsterName;
  int amount;
public:
  Summon(std::string monsterName, int amount);
  ~Summon();
  Summon* copyCtor() const override;
  std::string getName() const;
  int getAmount() const;
  void activate(Owner *me, Owner *opponent) override;
  void activate(int fieldIndex, Owner *player) override;
};

#endif

