#ifndef _FLIP_H_
#define _FLIP_H_
#include <string>
#include "effect.h"

class Flip : public Effect {
  Effect* effect;
public:
  Flip(Effect* effect);
  ~Flip();
  Flip* copyCtor() const override;
  void activate(Owner *me, Owner *opponent) override;
  void activate(int fieldIndex, Owner *player) override;
};

#endif

