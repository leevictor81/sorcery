#ifndef _SPELL_H_
#define _SPELL_H_
#include <iostream>
#include <string>
#include "card.h"
#include "effect.h"


class Spell : public Card {
  Effect* effect;
public:
  Spell(std::string name, int cost, std::string description, Effect *e);
  ~Spell();
  void play(Owner* me, Owner* opponent) override;
  void play(int fieldIndex, Owner* player) override;
  card_template_t makeTemplate() const override;
};

#endif

