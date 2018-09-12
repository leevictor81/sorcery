#ifndef _DRAW_H_
#define _DRAW_H_
#include <string>
#include "effect.h"

class Draw : public Effect {
  int cardsDrawn;
public:
  Draw(int cards);
  ~Draw();
  Draw* copyCtor() const override;
  int getCards() const;
  void activate(Owner *me, Owner *opponent) override;
  void activate(int fieldIndex, Owner *player) override;
};

#endif

