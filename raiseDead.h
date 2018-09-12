#ifndef _RAISEDEAD_H_
#define _RAISEDEAD_H_
#include <string>
#include "effect.h"

class RaiseDead : public Effect {
  int numOfRaises;
public:
  RaiseDead(int numOfRaises);
  ~RaiseDead();
  RaiseDead* copyCtor() const override;
  int getNumOfRaises() const;
  void activate(Owner *me, Owner *opponent) override;
  void activate(int fieldIndex, Owner *player) override;
};

#endif

