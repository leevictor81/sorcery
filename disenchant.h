#ifndef _DISENCHANT_H_
#define _DISENCHANT_H_
#include <string>
#include "effect.h"

class Disenchant : public Effect {
  int numOfDisenchant;
public:
  Disenchant(int numOfDisenchant);
  ~Disenchant();
  Disenchant* copyCtor() const override;
  int getNumOfDisenchant() const;
  void activate(Owner *me, Owner *opponent) override;
  void activate(int fieldIndex, Owner *player) override;
};

#endif

