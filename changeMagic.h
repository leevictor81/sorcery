#ifndef _CHANGE_MAGIC_H_
#define _CHANGE_MAGIC_H_
#include <string>
#include "effect.h"

class ChangeMagic: public Effect {
  int magicChange;
public:
  ChangeMagic(int magicChange);
  ~ChangeMagic();
  ChangeMagic* copyCtor() const override;
  int getMagicChange() const;
  void activate(Owner *me, Owner *opponent) override;
  void activate(int fieldIndex, Owner *player) override;
};

#endif

