#ifndef _UNSUMMON_H_
#define _UNSUMMON_H_
#include <string>
#include "effect.h"

class Unsummon : public Effect {
public:
  Unsummon();
  ~Unsummon();
  Unsummon* copyCtor() const override;
  void activate(Owner *me, Owner *opponent) override;
  void activate(int fieldIndex, Owner *player) override;
};

#endif

